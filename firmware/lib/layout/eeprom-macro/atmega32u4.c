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
 * - "block"s are 4 bytes long, aligned on the 4 byte boundary
 *
 * - Blocks are pointed to by `uint8_t`s
 *     - the EEPROM contains 1024 bytes = 256 blocks
 *       (i.e. 2^10 bytes, 2^8 blocks)
 *     - the beginning of a block is pointed to by
 *       `eeprom_address = block_address << 2`
 *
 * - A "UID" (Unique ID) in this file is a `eeprom_macro__index_t`
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
 *
 *     struct {
 *         uint8_t version;  // the version of this layout
 *                           //   `0x00`,`0xFF` => uninitialized
 *         uint8_t rows;     // the number of rows in the table
 *         uint8_t columns;  // the number of columns in the table
 *         uint8_t free;     // the first free block not yet used for macros
 *     };
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
 *   `row` and `column` in its UID
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
#define  MACROS  (TABLE + ((ROWS * COLUMNS + 0b11) >> 2))

/**                                                      macros/END/description
 * The end of the `MACROS` section (the highest block of the EEPROM that we're
 * allowed to use)
 */
#define  END  0xFF

// ----------------------------------------------------------------------------

// sanity check
#if MACROS+10 >= END
    #error "Insufficient EEPROM allocated to \".../firmware/lib/eeprom-macro\""
#endif

// ----------------------------------------------------------------------------

// TODO: if we do it this way, this belongs in the options file
#define  OPT__EEPROM_MACRO__SIZE  1024

#define  VERSION      1

struct {
    uint8_t version;  // the version of this layout
                      //   `0x00`,`0xFF` => uninitialized
    uint8_t rows;     // the number of rows in the table
    uint8_t columns;  // the number of columns in the table
    uint8_t free;     // the first free block not yet used for macros
} header EEMEM;

uint8_t table[OPT__KB__ROWS][OPT__KB__COLUMNS] EEMEM;

uint8_t macros[ OPT__EEPROM_MACRO__SIZE-sizeof(header)-sizeof(table) ] EEMEM;

// ----------------------------------------------------------------------------

void f(void) {
    uint8_t version1 = eeprom_read_byte( (HEADER<<2) + 0 );
    uint8_t version2 = eeprom_read_byte( &header.version );

    uint8_t ptr1 = eeprom_read_byte( TABLE + 5*COLUMNS + 3 );
    uint8_t ptr2 = eeprom_read_byte( &table[5][3] );


    // to suppress warnings about unused variables...
    uint8_t version3 = version1+version2;
    version3++;
}

// ----------------------------------------------------------------------------

// TODO: functions

