/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Implements the eeprom-macro functionality defined in "../eeprom-macro.h" for
 * the ATMega32U4
 *
 * Implementation notes:
 * - "block"s are 4 bytes long, aligned on the 4 byte boundary
 * - blocks are pointed to by `uint8_t`s
 *     - the EEPROM contains 1024 bytes = 256 blocks
 *       (i.e. 2^10 bytes, 2^8 blocks)
 *     - the beginning of a block is pointed to by
 *       `eeprom_address = block_address<<2`
 */


#include <stdint.h>
#include <avr/eeprom.h>

// ----------------------------------------------------------------------------

// for convenience
#define  ROWS     OPT__KB__ROWS
#define  COLUMNS  OPT__KB__COLUMNS

// ----------------------------------------------------------------------------

/**                                                   macros/HEADER/description
 * The beginning of the `HEADER` section (the lowest block of the EEPROM that
 * we're allowed to use)
 *
 * Size (in blocks): 1
 *
 * Format:
 * - byte 0: the version of this layout
 *     - `0x00`, `0xFF` => uninitialized
 * - byte 1: the number of rows in the table
 * - byte 2: the number of columns in the table
 * - byte 3: the first free block not yet used by `MACROS`
 *
 * Notes:
 * - The number of rows and columns is significant to the offsets of some of
 *   the sections, and so is important to keep track of here, along with the
 *   version number.
 */
#define  HEADER  0x00

/**                                                    macros/TABLE/description
 * The beginning of the `TABLE` section
 *
 * Size (in blocks): `ceil( (ROWS * COLUMNS) / 4 )`
 * - This is conveniently calculated by taking `(ROWS * COLUMNS + 0b11) >> 2`
 *
 * Notes:
 * - Each entry is a block pointer to the first macro with the corresponding
 *   `row` and `column` in its unique ID
 *
 * Format:
 * - A `[ROWS][COLUMNS]` table, where the `[row][column]` entry can be accessed
 *   by taking  the `[ (row * COLUMNS) + column ]` entry (as is normal with
 *   arrays in C).
 */
#define  TABLE  (HEADER + 1)

/**                                                    macros/TABLE/description
 * The beginning of the `MACROS` section
 *
 * Size (in blocks): `END - MACROS + 1` (since `END` is included)
 *
 * Format: macro header:
 * - byte 0: a block pointer to the next macro with the same `row` and `column`
 *           in its unique ID
 *     - `0x00` => this macro is the last in the linked list for this `row`,
 *                 `column` pair
 *     - `0xFF` => this macro has been deleted
 * - byte 1: the run length of the macro, in number of key actions
 * - byte 2..3: the unique ID of this macro (its `index`)
 *
 * Format: key action
 * - The same as the format of `eeprom_macro__index_t` (which is the format of
 *   the unique IDs), except that `layer` will be ignored
 */
#define  MACROS  (TABLE + ((ROWS * COLUMNS + 0b11) >> 2))

/**                                                      macros/END/description
 * The end of the `MACROS` section (the highest block of the EEPROM that we're
 * allowed to use)
 */
#define  END  0xFF

// ----------------------------------------------------------------------------

// TODO: functions

