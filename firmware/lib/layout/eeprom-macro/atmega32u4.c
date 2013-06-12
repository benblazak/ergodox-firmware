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
 * - One cannot trust the binary layout of bit-fields.  Bit-fields are great,
 *   but the order of the fields (among other things) is implementation
 *   defined, and [can change][1], even between different versions of the same
 *   compiler.
 *
 *
 * [1]: http://avr.2057.n7.nabble.com/Bit-field-packing-order-changed-between-avrgcc-implementations-td19193.html
 */


#include <stdint.h>
#include <avr/eeprom.h>
#include "../../../../firmware/keyboard.h"
#include "../../../../firmware/lib/eeprom.h"
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
 * TODO: update
 * Struct members:
 * - `meta`: For keeping track of layout metadata (`[3]` for fault tolerance)
 *     - `version`: The version of this layout
 *         - `0x00`, `0xFF` => EEPROM is uninitialized
 *     - `status`: (see `enum eeprom_status`)
 *
 * - `table`: To help in quickly failing if there is no macro for a given UID
 *     - `rows`: The number of rows this table has
 *     - `columns`: The number of columns this table has
 *     - `data`: Each entry contains a `uint8_t`, with
 *       `(bool)( (data[row][column] >> layer) & 0x1 )`
 *       indicating whether there is a macro defined for that (layer, row,
 *       column) tuple.  This limits the layers we can deal with to those
 *       between 0 and 7, inclusive.
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
 *
 * TODO: implement putting a log at the end :)
 * - how to describe shifting data down?
 * - max space to leave for compression?
 */

/**                                              types/macro_header/description
 * The header for a macro living in `macros.data`
 *
 * Struct members:
 * - `flag`:
 *     - `true` => `macro_header`
 *     - `false` => `macro_action`
 * - `status`: (see `enum macro_header_status` for explicitly defined values)
 *     - [other]: to be moved `status - MH_S_TO_MOVE_1 + 1` indices towards
 *       `macros.data[0]`
 * - `run_length`: The number of `macro_action`s following this header
 *     - `0x00` => this header marks the beginning of unused space
 * - `uid`: The Unique IDentifier (UID) of this macro
 */

/**                                              types/macro_action/description
 * A single action belonging to a macro living in `macros.data`
 *
 * Struct members:
 * - `flag`:
 *     - `true` => `macro_header`
 *     - `false` => `macro_action`
 * - The key state (`pressed` or unpressed), `row`, and `column` of the action
 *   recorded
 *
 * Notes:
 * - To be "executed" by calling `kb__layout__exec_key()` with the appropriate
 *   arguments.
 */

// ----------------------------------------------------------------------------
// TODO: redesign

struct eeprom {
    struct meta {
        uint8_t version[3];
    } meta;

    struct table {
        uint8_t rows;
        uint8_t columns;
        uint8_t data[OPT__KB__ROWS][OPT__KB__COLUMNS];
    } table;

    struct macros {
        uint16_t length;
        uint8_t  data[ OPT__EEPROM_MACRO__EEPROM_SIZE
                       - 2  // for `length`
                       - sizeof(struct meta)
                       - sizeof(struct table) ];
    } macros;

} __attribute__((packed, aligned(1)));

struct macro_header {
    uint8_t type;
    uint8_t run_length;
    uint16_t uid;
};

struct log_header {
    uint8_t type;
    uint8_t run_length;
};

enum {
    MACRO,
    LOG_ATOMIC_WRITE,
    LOG_ATOMIC_COPY,
    HEADER_NULL = 0xFF
};

struct macro_action {
    uint8_t pressed  : 1;
    uint8_t row      : 7;
    uint8_t reserved : 1;
    uint8_t column   : 7;
};

struct log_action_copy {
    uint16_t to;
    uint16_t from;
    uint8_t length;
};

struct log_action_write {
    uint16_t to;
    uint8_t data;
};

// ----------------------------------------------------------------------------

struct eeprom eeprom EEMEM;

// ----------------------------------------------------------------------------

/**                                          functions/atomic_write/description
 * TODO
 */
static void atomic_write(uint8_t length, uint8_t * address[], uint8_t data[]) {
}

/**                                           functions/atomic_copy/description
 * TODO
 */
static void atomic_copy(uint8_t * to, uint8_t * from, uint8_t length) {
}

/**                                              functions/compress/description
 * Compress `macros.data`
 *
 * Shift all macros towards index `0`, overwriting the areas previously
 * occupied by deleted macros.
 */
static void compress(void) {
}

// ----------------------------------------------------------------------------

uint8_t eeprom_macro__init(void) {
    return 0;
}

uint8_t eeprom_macro__record__start(uint8_t skip) {
    return 0;
}

uint8_t eeprom_macro__record__stop(uint8_t skip, eeprom_macro__uid_t index) {
    return 0;
}

uint8_t eeprom_macro__play(eeprom_macro__uid_t index) {
    return 0;
}

void eeprom_macro__clear(eeprom_macro__uid_t index) {
}

void eeprom_macro__clear_all(void) {
}

