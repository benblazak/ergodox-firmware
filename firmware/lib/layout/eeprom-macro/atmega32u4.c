/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Implements the eeprom-macro functionality defined in "../eeprom-macro.h" for
 * the ATMega32U4
 *
 *
 * Implementation notes:
 *
 * - Do not trust the binary layout of bit-fields.  Bit-fields are great, but
 *   the order of the fields (among other things) is implementation defined,
 *   and [can change][1], even between different versions of the same compiler.
 *
 *     - We use bit-fields in this file quite happily, but when they're read
 *       from or written to the EEPROM, it should be handled explicitly, field
 *       by field, so as to not potentially bite users who upgrade their
 *       compiler, then compile and install a new firmware with the same EEPROM
 *       layout, expecting their macros to still work :) .
 *
 *
 * [1]: http://avr.2057.n7.nabble.com/Bit-field-packing-order-changed-between-avrgcc-implementations-td19193.html
 */


#include <stdint.h>
#include <avr/eeprom.h>
#include "../../../../firmware/keyboard.h"
#include "../eeprom-macro.h"

// ----------------------------------------------------------------------------

// TODO: consider moving this, and all similar things in other files, into the
// '.h' files instead (and *always* including the '.h' files in implementing
// '.c' files)
#ifndef OPT__EEPROM_MACRO__EEPROM_SIZE
    #error "OPT__EEPROM_MACRO__EEPROM_SIZE not defined"
#endif
/**                           macros/OPT__EEPROM_MACRO__EEPROM_SIZE/description
 * The total size (in bytes) of the EEPROM memory to be allocated by this file
 *
 * Notes:
 * - The ATMega32U4 has 1024 bytes of internal EEPROM total
 */

// ----------------------------------------------------------------------------

/**                                                  macros/VERSION/description
 * The version number of `struct eeprom`
 */
#define  VERSION  1

// ----------------------------------------------------------------------------

/**                                                    types/eeprom/description
 * The layout of this library's data in the EEPROM
 *
 *
 * Struct members:
 * - `meta`: For keeping track of layout metadata (`[3]` for redundancy and
 *   fault tolerance)
 *     - `version`: The version of this layout
 *         - `0x00`, `0xFF` => EEPROM is uninitialized
 *     - `first_free`: The index of the first free element in `macros.data`
 *       (`[5]` for write balancing a little)
 *         - When `compress_offset` is `0x00`, this value will be the index of
 *           the beginning of the current `compress_offset` sized block that is
 *           being updated
 *         - When `compress_offset` is `0xFE`, this value will be the index of
 *           the current macro header who's `next` might need to be updated
 *     - `compress_offset`: The offset (in `macros.data` indices) between what
 *       we're currently copying, and where we're copying it.  This will be
 *       equal to the amount of `macros.data` elements worth of space that
 *       belonged to all deleted macros found so far.
 *         - `0x00` => `compress()` is running, but not copying data yet
 *         - `0xFE` => `compress()` is updating `next` pointers
 *         - `0xFF` => `compress()` is not running
 *
 * - `table`: To help in quickly finding macros based on UID
 *     - `rows`: The number of rows this table has
 *     - `columns`: The number of columns this table has
 *     - `data`: Each entry contains the index of the beginning of the first
 *        macro with the corresponding row and column in its UID
 *
 * - `macros`: A block of memory for storing macros
 *     - `length`: The number of elements in `macros.data`
 *     - `data`: A collection of `macro_header`s followed by the defined number
 *       of `macro_action`s.  Essentially, a collection of (not necessarily
 *       contiguous) linked lists of macros, with one list for every row,
 *       column pair that has a remapping.
 *
 *
 * Notes:
 *
 * - We keep track of `table.rows`, `table.columns`, and `macros.length`, in
 *   addition to `header.version`, because they all effect the precise layout
 *   of the persistent data; if any of them is different, special handling is
 *   required at the least, and usually the stored data will be unusable.
 *
 * - The struct must be `packed` and `aligned(1)`, or we risk allocating more
 *   than `OPT__EEPROM_MACRO__EEPROM_SIZE` bytes.  This should be the default
 *   when compiling with `avr-gcc`, but it's important to emphasize that we
 *   depend on it.
 */
struct eeprom {
    struct meta {
        uint8_t version;
        uint8_t first_free[5];
        uint8_t compress_offset;
    } meta[3];

    struct table {
        uint8_t rows;
        uint8_t columns;
        uint8_t data[OPT__KB__ROWS][OPT__KB__COLUMNS];
    } table;

    struct macros {
        uint8_t  length;
        uint32_t data[ ( OPT__EEPROM_MACRO__EEPROM_SIZE
                         - sizeof(uint8_t)  // for `macros.length`
                         - sizeof(struct meta) * 3
                         - sizeof(struct table)         ) >> 2 ];
    } macros;
} __attribute__((packed, aligned(1)));

/**                                              types/macro_header/description
 * The header for a macro living in `macros.data`
 *
 * Struct members:
 * - `next`: The index (in `macros.data`) of the next macro with the same row
 *   and column in its UID
 *     - `0x00` => This macro is (currently) the last in its linked list
 *     - `0xFF` => This macro has been deleted
 * - `length`: The number of `macro_action`s following this header
 * - `uid`: The Unique IDentifier (UID) of this macro
 */
struct macro_header {
    uint8_t next;
    uint8_t length;
    eeprom_macro__index_t uid;
};

/**                                              types/macro_action/description
 * A single action belonging to a macro living in `eeprom.macros.data`
 *
 * Struct members:
 * - The key state (`pressed` or unpressed), `row`, and `column` of the action
 *   recorded
 *
 * Notes:
 * - To be "executed" by calling `kb__layout__exec_key()` with the appropriate
 *   arguments.
 */
struct macro_action {
    bool    pressed   : 1;
    uint8_t row       : 7;
    uint8_t column    : 7;
    uint8_t padding_0 : 1;
};

// ----------------------------------------------------------------------------

struct eeprom eeprom EEMEM;

uint8_t test[ sizeof(eeprom.macros.data) ];

// ----------------------------------------------------------------------------

/**                                              functions/compress/description
 * Compress `macros.data`
 *
 * Shift all macros towards index `0`, overwriting the areas previously
 * occupied by deleted macros.
 */
static void compress(void) {
    // - when we move macros, we need to update the `next` pointers
    //   appropriately
}

// ----------------------------------------------------------------------------

uint8_t eeprom_macro__init(void) {
    // - check for invalid `next` pointers?
    return 0;
}

uint8_t eeprom_macro__record__start(uint8_t skip) {
    return 0;
}

uint8_t eeprom_macro__record__stop(uint8_t skip, eeprom_macro__index_t index) {
    // - write macro_header     : safe, before updating `first_free`
    // - update previous `next` : safeish: will have been 0x00 before update
    //                                     will be invalid (probably) after
    //                                     update, until `first_free` is
    //                                     updated
    // - update `first_free`    : unsafe
    return 0;
}

uint8_t eeprom_macro__play(eeprom_macro__index_t index) {
    return 0;
}

void eeprom_macro__clear(eeprom_macro__index_t index) {
}

void eeprom_macro__clear_all(void) {
}

