/* ----------------------------------------------------------------------------
 * Copyright (c) 2012, 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Implements the "special" section of "../key-functions.h"
 */


#include <stdbool.h>
#include <stddef.h>
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

void key_functions__send_unicode_sequence ( uint8_t         wrapper_length,
                                            const uint8_t * wrapper,
                                            const wchar_t * string ) {
    struct _modifier_state_t state = _read_modifier_state();
    _set_modifier_state( (struct _modifier_state_t){} );

    typedef union {
        wchar_t all;
        struct {
            uint8_t p3 : 4;  //
            uint8_t p2 : 4;  // upside-down
            uint8_t p1 : 4;  // must be little endian, in this case
            uint8_t p0 : 4;  //
        };
    } char_t;

    // send string
    for ( char_t c = { .all = pgm_read_word(string) };
          c.all; c.all = pgm_read_word(++string) ) {

        // send start sequence
        for (uint8_t i=0; i<wrapper_length; i++) {
            usb__kb__set_key(true, pgm_read_byte(wrapper++));
            usb__kb__send_report();
        }

        // send character
        _send_hex_digit(c.p0);
        _send_hex_digit(c.p1);
        _send_hex_digit(c.p2);
        _send_hex_digit(c.p3);

        // send end sequence (reverse of start sequence)
        for (uint8_t i=0; i<wrapper_length; i++) {
            usb__kb__set_key(false, pgm_read_byte(--wrapper));
            usb__kb__send_report();
        }
    }

    _set_modifier_state(state);
}

