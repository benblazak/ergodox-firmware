/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Gyuri Horak <dyuri@horak.hu>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Implements the "keyboard" section of '.../firmware/lib/usb.h'
 */

#include <stdbool.h>
#include "./keyboard/from-pjrc/usb.h"
#include "../../usb.h"

// ----------------------------------------------------------------------------

void usb__m__send(int8_t x, int8_t y, int8_t wheel_v, int8_t wheel_h, uint8_t buttons) {
#ifdef MOUSE_ENABLE
    usb_mouse_send(x, y, wheel_v, wheel_h, buttons);
#endif
}

void usb__m__buttons(uint8_t buttons) {
#ifdef MOUSE_ENABLE
    usb_mouse_buttons(buttons);
#endif
}

