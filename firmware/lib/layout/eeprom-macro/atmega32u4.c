/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Implements the eeprom-macro functionality defined in "../eeprom-macro.h" for
 * the ATMega32U4
 *
 * Terms (for the purposes of this file):
 * - A "UID" (Unique IDentifier) is an `eeprom_macro__index_t`
 */


#include <stdint.h>
#include <avr/eeprom.h>
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
 * The version number of this EEPROM layout
 */
#define  VERSION  1

// ----------------------------------------------------------------------------

/**                                                    types/eeprom/description
 * The layout of this library's data in the EEPROM
 *
 * Struct members:
 * - `header`: For keeping track of layout metadata
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
 * - `macros`: A block of memory for storing macros
 *     - `size`: `sizeof(struct macros) >> 2`;
 *     - `data`: TODO
 */
struct eeprom {
    struct header {
        uint8_t version;
        uint8_t free;
    } header;

    struct table {
        uint8_t rows;
        uint8_t columns;
        uint8_t data[OPT__KB__ROWS][OPT__KB__COLUMNS];
    } table;

    struct macros {
        uint8_t  size;
        uint32_t data[ ( OPT__EEPROM_MACRO__EEPROM_SIZE
                         - sizeof(struct header)
                         - sizeof(struct table)         ) >> 2 ];
    } macros;

};

/**                                              types/macro_header/description
 * TODO
 */
struct macro_header {
    uint8_t next;
    uint8_t length;
    eeprom_macro__index_t index;
};

/**                                              types/macro_action/description
 * TODO
 */
struct macro_action {
    bool    pressed : 1;
    uint8_t row     : 7;
    uint8_t column  : 7;
};

// ----------------------------------------------------------------------------

// TODO: functions


/*
 * Format: macro header:
 *
 *     struct {
 *         uint8_t next;    // a block pointer to the next macro with the same
 *                          //   `row` and `column` in its UID
 *                          //   `0x00` => this macro is the last in the linked
 *                          //             list for this `row`, `column` pair
 *                          //   `0xFF` => this macro has been deleted
 *         uint8_t length;  // the run length of the macro, in number of
 *                          //   key actions
 *         eeprom_macro__index_t index;  // the UID of this macro
 *     };
 *
 * Format: key action:
 *
 *     struct {
 *         eeprom_macro__index_t index;  // `layer` will be ignored
 *     };
 */

