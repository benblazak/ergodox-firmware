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
 * Warnings:
 *
 * - This library's functionality is meant to be used for recording and playing
 *   back *temporary* macros.  Permanent macros should be assigned to a key in
 *   the layout directly.  Macros created using this library may be difficult
 *   (or practically impossible) to retrieve and back up, and may be
 *   invalidated by changes to this library in future versions of the firmware.
 *   They may also become corrupted if the keyboard looses power at an
 *   inopportune time.  If invalidated or corrupted, macros will (probably) be
 *   erased without warning.
 *
 *
 * Implementation notes:
 *
 * - One cannot trust the binary layout of bit-fields.  Bit-fields are great,
 *   but the order of the fields (among other things) is implementation
 *   defined, and [can change]
 *   (http://avr.2057.n7.nabble.com/Bit-field-packing-order-changed-between-avrgcc-implementations-td19193.html),
 *   even between different versions of the same compiler.
 *
 * - The default state (the "erased" state) of this EEPROM is all `1`s, which
 *   makes setting a byte to `0xFF` easier and faster in hardware than zeroing
 *   it.  This is reflected in some of our choices for default values, and
 *   such.
 *
 * - For a long time, I was going to try to make this library robust in the
 *   event of power loss, but in the end I decided not to.  This feature is
 *   meant to be used for *temporary* macros - permanent macros really should
 *   be assigned to a key in the layout directly, instead of using this
 *   library's functionality after the firmware has already been loaded - so,
 *   with the risk of power loss being fairly low, and the consequence of
 *   (detected) eeprom-macro corruption hopefully more of an annoyance than
 *   anything else, I decided the effort (and extra EEMEM usage) wasn't worth
 *   it.
 */


#include <stdint.h>
#include <avr/eeprom.h>
#include "../../../../firmware/keyboard.h"
#include "../../../../firmware/lib/eeprom.h"
#include "../eeprom-macro.h"

// ----------------------------------------------------------------------------

/**                           macros/OPT__EEPROM_MACRO__EEPROM_SIZE/description
 * Implementation notes:
 * - The ATMega32U4 has 1024 bytes of internal EEPROM total
 */
#if OPT__EEPROM_MACRO__EEPROM_SIZE > 1024
    #error "OPT__EEPROM_MACRO__EEPROM_SIZE must be <= 1024"
#endif

// ----------------------------------------------------------------------------

/**                                                  macros/VERSION/description
 * The version number of `struct eeprom`
 *
 * History:
 * - 0x00: Reserved: EEPROM in inconsistent state
 * - 0x01: First version
 * - ... : (not yet assigned)
 * - 0xFF: Reserved: EEPROM not yet initialized
 */
#define  VERSION  0x01

// ----------------------------------------------------------------------------

/**                                                variables/eeprom/description
 * The layout of this library's data in the EEPROM
 *
 * Struct members:
 * - `meta`: For keeping track of layout metadata
 *     - `version`: The version of this layout (`[10]` for fault tolerance and
 *       write balancing)
 * - `table`: To help in quickly returning if the UID we're searching for does
 *   not exist
 *     - `rows`: The number of rows this table has
 *     - `columns`: The number of columns this table has
 *     - `data`:
 *         - For any `eeprom_macro__uid_t uid`
 *             - If `uid.layer > 7`, this table doesn't tell whether a macro
 *               exists for the UID or not
 *             - Otherwise, `! (bool)( (eeprom.table.data[uid.row][uid.column]
 *               >> uid.layer) & 0x1 )` indicates whether a macro exists with
 *               the given UID (`true`) or not (`false`)
 *             - Note that the expression above will return `true` if
 *               `uid.layer > 7`
 * - `macros`: To hold a block of memory for storing macros
 *     - `length`: The number of elements in `macros.data` (which is *not* the
 *       same as the number of macros it can contain)
 *     - `data`: A collection of "macro"s, where
 *         - a "macro" is a "header" followed by zero or more "action"s
 *         - a "header" is
 *             - 4 bytes, aligned on an index boundary
 *
 *               LSB - lowest address
 *               .---------------------------------------.
 *               |     0 | 1 | 2 | 3 | 4 | 5 | 6 | 7     |
 *               |---------------------------------------|
 *               |                 type                  |
 *               '---------------------------------------'
 *               .---------------------------------------.
 *               |     0 | 1 | 2 | 3 | 4 | 5 | 6 | 7     |
 *               |---------------------------------------|
 *               |              run length               |
 *               '---------------------------------------'
 *               .---------------------------------------.
 *               |    0    | 1 | 2 | 3 | 4 | 5 |  6 | 7  |
 *               |---------------------------------------|   UID ...
 *               | pressed |       layer       | row ... |
 *               '---------------------------------------'
 *               .---------------------------------------.
 *               |   0 | 1 | 2   |   3 | 4 | 5 | 6 | 7   |
 *               |---------------------------------------|   ... UID
 *               |    ... row    |        column         |
 *               '---------------------------------------'
 *               MSB - highest address
 *
 *             - type:
 *                 - `0x00`: deleted macro (run length is valid)
 *                 - `0x01`: valid macro
 *                 - ...   : (not yet assigned)
 *                 - `0xFF`: macro does not exist
 *             - run length: the number of "actions" that follow
 *             - UID: an `eeprom_macro__uid_t`, laid out in EEPROM memory as
 *               shown
 *
 *         - an "action" is
 *             - 2 bytes, aligned on an index or half index boundary
 *
 *               LSB - lowest address
 *               .---------------------------------------.
 *               |    0    | 1 | 2 | 3 | 4 | 5 |  6 | 7  |
 *               |---------------------------------------|   UID ...
 *               | pressed |       layer       | row ... |
 *               '---------------------------------------'
 *               .---------------------------------------.
 *               |   0 | 1 | 2   |   3 | 4 | 5 | 6 | 7   |
 *               |---------------------------------------|   ... UID
 *               |    ... row    |        column         |
 *               '---------------------------------------'
 *               MSB - highest address
 *
 *             - UID: an `eeprom_macro__uid_t`, laid out in EEMEM as shown
 *                 - Only "pressed", "row", and "column" are relevant, since
 *                   these are what will be passed to `kb__layout__exec_key()`
 *                   when playing back the macro.  "layer" will be ignored.
 *
 * Notes:
 *
 * - We depict bytes as little endian (which is the opposite of the way they're
 *   normally portrayed) to be consistent with the byte-order, which we define
 *   to be little endian to be consistent with the way that avr-gcc allocates
 *   datatypes larger than 1 byte (see [this discussion]
 *   (http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&p=337747)
 *   on <http://www.avrfreaks.net/>).
 *   Keep in mind that shifting "right" (with `>>`) still shifts towards the
 *   0th bit.
 *
 * - The struct must be `packed` and `aligned(1)`, or we risk allocating more
 *   than `OPT__EEPROM_MACRO__EEPROM_SIZE` bytes.  This should be the default
 *   when compiling with `avr-gcc`, but it's important to emphasize that we
 *   depend on it.
 *
 * - We keep track of `table.rows`, `table.columns`, and `macros.length`, in
 *   addition to `header.version`, because they all effect the precise layout
 *   of the persistent data; if any of them is different, special handling is
 *   required at the least, and usually the stored data will be unusable.
 *
 *
 * Implementation notes:
 *
 * - `macros.length` only needs to be 8 bits wide since we're using 4 bytes per
 *   index, and the EEPROM has a maximum of 1024 = 2^10 bytes addressable.
 *   2^10/4 = 2^8.
 */
struct eeprom {
    struct meta {
        uint8_t version[10];
    } meta;

    struct table {
        uint8_t rows;
        uint8_t columns;
        uint8_t data[OPT__KB__ROWS][OPT__KB__COLUMNS];
    } table;

    struct macros {
        uint8_t length;
        uint32_t data[ ( OPT__EEPROM_MACRO__EEPROM_SIZE
                          - 1  // for `length`
                          - sizeof(struct meta)
                          - sizeof(struct table) ) / 4 ];
    } macros;

} __attribute__((packed, aligned(1))) eeprom EEMEM;

// ----------------------------------------------------------------------------

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

uint8_t eeprom_macro__record_init(void) {
    return 0;
}

uint8_t eeprom_macro__record_keystroke( bool    pressed,
                                        uint8_t row,
                                        uint8_t column ) {
    return 0;
}

uint8_t eeprom_macro__record_finalize(eeprom_macro__uid_t index) {
    return 0;
}

uint8_t eeprom_macro__exists(eeprom_macro__uid_t index) {
    // TODO
    return 0;
}

uint8_t eeprom_macro__play(eeprom_macro__uid_t index) {
    return 0;
}

void eeprom_macro__clear(eeprom_macro__uid_t index) {
}

void eeprom_macro__clear_all(void) {
}

