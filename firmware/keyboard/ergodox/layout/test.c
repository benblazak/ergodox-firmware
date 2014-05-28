/* ----------------------------------------------------------------------------
 * Copyright (c) 2014 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * A layout for testing newly build boards
 *
 * Implements the "layout" section of '.../firmware/keyboard.h'
 */


#include <avr/pgmspace.h>
#include "../../../../firmware/keyboard.h"
#include "../../../../firmware/lib/layout/key-functions.h"


// ----------------------------------------------------------------------------
// LED control
// ----------------------------------------------------------------------------

#include "./fragments/led-control.part.h"


// ----------------------------------------------------------------------------
// matrix control
// ----------------------------------------------------------------------------

/**                                  functions/kb__layout__exec_key/description
 * Implementation notes:
 * - TODO
 */
void kb__layout__exec_key(bool pressed, uint8_t row, uint8_t column) {
    key_functions__type_string   ( PSTR( "test: " ) );

    key_functions__type_string   ( PSTR( " pressed: " ) );
    key_functions__type_byte_hex ( pressed );

    key_functions__type_string   ( PSTR( "  row: " ) );
    key_functions__type_byte_hex ( row );

    key_functions__type_string   ( PSTR( "  column: " ) );
    key_functions__type_byte_hex ( column );

    key_functions__type_string   ( PSTR( "\n" ) );

    // handle jumping to the bootloader if the three keys that cause this in
    // the templates/kinesis-mod layout are pressed (in any order)

    static uint8_t count;  // set to 0 by the compiler

    if ( ( row == 0x2 && column == 0x6 ) ||
         ( row == 0x2 && column == 0x7 ) ||
         ( row == 0x5 && column == 0x0 ) ) {
        if (pressed) {
            count++;
        } else {
            count--;
        }
    }

    if (count >=3) {
        key_functions__jump_to_bootloader();
    }
}

