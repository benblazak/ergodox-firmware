/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Implements the eeprom-macro functionality defined in "../eeprom-macro.h" for
 * the ATMega32U4
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
 * Struct members:
 * - `meta0`: For keeping track of layout metadata
 *     - `version`: The version of this layout
 *         - `0x00`, `0xFF` => uninitialized
 *     - `free`: The first free element in `macros.data`
 *
 * - `table`: To help in quickly finding macros based on UID
 *     - `rows`: The number of rows this table has
 *     - `columns`: The number of columns this table has
 *     - `data`: Each entry contains the index of the beginning of the first
 *        macro with the corresponding row and column in its UID
 *
 * - `meta1`: For redundancy and write balancing (see `meta0`)
 *
 * - `macros`: A block of memory for storing macros
 *     - `size`: The number of elements in `macros.data`
 *     - `data`: A collection of `macro_header`s followed by the defined number
 *       of `macro_action`s.  Essentially, a collection of (not necessarily
 *       contiguous) linked lists of macros, with one list for every row,
 *       column pair that has a remapping.
 *
 * - `meta2`: For redundancy and write balancing (see `meta0`)
 *
 * Notes:
 * - We keep track of `table.rows`, `table.columns`, and `macros.size`, in
 *   addition to `header.version`, because they all effect the precise layout
 *   of the persistent data; if any of them is different, special handling is
 *   required at the least, and usually the stored data will be unusable.
 */
struct eeprom {
    struct meta0 {
        uint8_t version;
        uint8_t free;
    } meta0;

    struct table {
        uint8_t rows;
        uint8_t columns;
        uint8_t data[OPT__KB__ROWS][OPT__KB__COLUMNS];
    } table;

    struct meta1 {
        uint8_t version;
        uint8_t free;
    } meta1;

    struct macros {
        uint8_t  size;
        uint32_t data[ ( OPT__EEPROM_MACRO__EEPROM_SIZE
                         - sizeof(struct meta0) * 3
                         - sizeof(struct table)         ) >> 2 ];
    } macros;

    struct meta2 {
        uint8_t version;
        uint8_t free;
    } meta2;
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
} __attribute__((packed, aligned(1)));

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
 *
 * TODO: binary format is important: use explicit bit shifting/masking instead
 * of bitfields
 */
struct macro_action {
    uint8_t padding : 1;
    bool    pressed : 1;
    uint8_t row     : 7;
    uint8_t column  : 7;
} __attribute__((packed, aligned(1)));

// ----------------------------------------------------------------------------

struct eeprom eeprom EEMEM;

uint8_t test[ sizeof(eeprom.macros.data) ];

// ----------------------------------------------------------------------------

uint8_t eeprom_macro__init(void) {
    return 0;
}

uint8_t eeprom_macro__record__start(uint8_t skip) {
    return 0;
}

uint8_t eeprom_macro__record__stop(uint8_t skip, eeprom_macro__index_t index) {
    return 0;
}

uint8_t eeprom_macro__play(eeprom_macro__index_t index) {
    return 0;
}

void eeprom_macro__clear(eeprom_macro__index_t index) {
}

void eeprom_macro__clear_all(void) {
}

