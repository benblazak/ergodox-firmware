/* ----------------------------------------------------------------------------
 * Copyright (c) 2012, 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Implements the "special" section of "../key-functions.h"
 */


#include <stdbool.h>
#include <stdint.h>
#include <avr/pgmspace.h>
#include "../../../../firmware/lib/usb.h"
#include "../../../../firmware/lib/usb/usage-page/keyboard.h"

// ----------------------------------------------------------------------------

// TODO: documentation?
struct _modifier_state_t {
    bool left_control  : 1;
    bool left_shift    : 1;
    bool left_alt      : 1;
    bool left_gui      : 1;
    bool right_control : 1;
    bool right_shift   : 1;
    bool right_alt     : 1;
    bool right_gui     : 1;
};

// ----------------------------------------------------------------------------

// TODO: documentation?
static struct _modifier_state_t _read_modifier_state(void) {
    return (struct _modifier_state_t) {
        .left_control  = usb__kb__read_key( KEYBOARD__LeftControl  ),
        .left_shift    = usb__kb__read_key( KEYBOARD__LeftShift    ),
        .left_alt      = usb__kb__read_key( KEYBOARD__LeftAlt      ),
        .left_gui      = usb__kb__read_key( KEYBOARD__LeftGUI      ),
        .right_control = usb__kb__read_key( KEYBOARD__RightControl ),
        .right_shift   = usb__kb__read_key( KEYBOARD__RightShift   ),
        .right_alt     = usb__kb__read_key( KEYBOARD__RightAlt     ),
        .right_gui     = usb__kb__read_key( KEYBOARD__RightGUI     ),
    };
}

// TODO: documentation?
static void _set_modifier_state(struct _modifier_state_t state) {
    usb__kb__set_key( state.left_control  , KEYBOARD__LeftControl  );
    usb__kb__set_key( state.left_shift    , KEYBOARD__LeftShift    );
    usb__kb__set_key( state.left_alt      , KEYBOARD__LeftAlt      );
    usb__kb__set_key( state.left_gui      , KEYBOARD__LeftGUI      );
    usb__kb__set_key( state.right_control , KEYBOARD__RightControl );
    usb__kb__set_key( state.right_shift   , KEYBOARD__RightShift   );
    usb__kb__set_key( state.right_alt     , KEYBOARD__RightAlt     );
    usb__kb__set_key( state.right_gui     , KEYBOARD__RightGUI     );

    usb__kb__send_report();
}

// TODO: documentation?
static void _send_hex_digit(uint8_t digit) {
    digit &= 0x0F;

    if      (digit == 0) digit  = KEYBOARD__0_RightParenthesis;
    else if (digit < 10) digit += KEYBOARD__1_Exclamation-1;
    else                 digit += KEYBOARD__a_A-10;

    usb__kb__set_key(true, digit);
    usb__kb__send_report();
    usb__kb__set_key(false, digit);
    usb__kb__send_report();
}

// ----------------------------------------------------------------------------

void key_functions__toggle_capslock (uint16_t ignore) {
    struct _modifier_state_t state = _read_modifier_state();
    _set_modifier_state( (struct _modifier_state_t){} );

    // toggle capslock
    usb__kb__set_key(true,  KEYBOARD__CapsLock);
    usb__kb__send_report();
    usb__kb__set_key(false, KEYBOARD__CapsLock);
    usb__kb__send_report();

    _set_modifier_state(state);
}

/** TODO
 *     --------------------------------------------------------
 *      UTF-8
 *     --------------------------------------------------------
 *      available bits  byte 1    byte 2    byte 3    byte 4
 *      --------------  --------  --------  --------  --------
 *                  7   0xxxxxxx
 *                 11   110xxxxx  10xxxxxx
 *                 16   1110xxxx  10xxxxxx  10xxxxxx
 *                 21   11110xxx  10xxxxxx  10xxxxxx  10xxxxxx
 *     --------------------------------------------------------
 *
 * - bit shifting (`>>` and `<<`) and then testing for equality (`==`) is
 *   weird.  need to write a note about it.
 */
// TODO: switch to using a `const char *` and interpreting the utf-8
// - this way we can use the `PSTR()` macro
// TODO: stop using a manually defined wrapper... not worth it, i think
void key_functions__send_unicode_sequence (const char * string) {
    struct _modifier_state_t state = _read_modifier_state();
    _set_modifier_state( (struct _modifier_state_t){} );

    // send string
    for (char c = pgm_read_byte(string); c; c = pgm_read_byte(++string)) {

        // send start sequence
//         usb__kb__set_key(true,  KEYBOARD__LeftAlt   ); usb__kb__send_report();
//         usb__kb__set_key(true,  KEYBOARD__Equal_Plus); usb__kb__send_report();
//         usb__kb__set_key(false, KEYBOARD__Equal_Plus); usb__kb__send_report();

        // --------------------------------------------------------------------
//         uint8_t d = (c >> 4);
// 
//         _send_hex_digit( c >> 4 );  // e
//         _send_hex_digit( d >> 4 );  // f
//         _send_hex_digit( d & 0xF ); // e
// 
//         _send_hex_digit( d == 0xFE );               // 1
//         _send_hex_digit( (c >> 4) == 0xFE );        // 0
//         _send_hex_digit( ((c >> 4) & 0xF) == 0xE ); // 1
        // --------------------------------------------------------------------
//         uint8_t d = (c << 4);
//         _send_hex_digit( d >> 4 );  // 2
//         _send_hex_digit( d & 0xF ); // 0
        // --------------------------------------------------------------------
        // so, '>>' fills with 'f's ? or with junk?
        //     '<<' fills with '0's ?
        // and '==' only works if you haven't bit shifted the variable?
        //
        // i think i need to use '&' for testing anyway, now that i think about
        // it... it's a much more common way to go about things
        // --------------------------------------------------------------------

        // send character
//         uint16_t c_full = 0;
//         if ((c >> 7) == 0b0) {
//             _send_hex_digit(0xA);
//             c_full = c & 0x7F;
//         } else if ((c >> 5) == 0b110) {
//             _send_hex_digit(0xB);
//             c_full  = (uint16_t)(c <<  6) & 0x1F; c = pgm_read_byte(++string);
//             c_full |= (uint16_t)(c <<  0) & 0x3F;
//         } else if ((c >> 4) == 0b1110) {
//             _send_hex_digit(0xC);
//             c_full  = (uint16_t)(c << 12) & 0x0F; c = pgm_read_byte(++string);
//             c_full |= (uint16_t)(c <<  6) & 0x3F; c = pgm_read_byte(++string);
//             c_full |= (uint16_t)(c <<  0) & 0x3F;
//         } else if ((c >> 3) == 0b11110) {
//             _send_hex_digit(0xD);
//             // this character is too long, we can't send it
//             // skip this byte, and the next 3
//             string += 3;
//             continue;
//         } else {
//             // invalid utf-8
//             continue;
//         }
//         _send_hex_digit(  c_full >> 12        );
//         _send_hex_digit( (c_full >>  8) & 0xF );
//         _send_hex_digit( (c_full >>  4) & 0xF );
//         _send_hex_digit( (c_full >>  0) & 0xF );

        // send end sequence
//         usb__kb__set_key(false, KEYBOARD__LeftAlt); usb__kb__send_report();
    }

    _set_modifier_state(state);
}

