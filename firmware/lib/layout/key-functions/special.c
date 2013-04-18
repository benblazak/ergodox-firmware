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
#include "../../../../firmware/lib/usb.h"
#include "../../../../firmware/lib/usb/usage-page/keyboard.h"

// ----------------------------------------------------------------------------

void kf__toggle_capslock (uint16_t ignore) {

    // save the state of left and right shift
    bool lshift_pressed = usb__kb__read_key(KEYBOARD__LeftShift);
    bool rshift_pressed = usb__kb__read_key(KEYBOARD__RightShift);

    // disable both shifts
    usb__kb__set_key(false, KEYBOARD__LeftShift);
    usb__kb__set_key(false, KEYBOARD__RightShift);

    // toggle capslock
    usb__kb__set_key(true,  KEYBOARD__CapsLock);
    usb_keyboard_send();
    usb__kb__set_key(false, KEYBOARD__CapsLock);
    usb_keyboard_send();

    // restore the state of both shifts
    if (lshift_pressed) usb__kb__set_key(true, KEYBOARD__LeftShift);
    if (rshift_pressed) usb__kb__set_key(true, KEYBOARD__RightShift);
}

