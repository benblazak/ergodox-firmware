/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Implements the "basic" section of
 * ".../firmware/lib/layout/key-functions.h"
 */

#include <stdint.h>
#include <avr/pgmspace.h>
#include "../../../../firmware/lib/usb.h"
#include "../../../../firmware/lib/layout/layer-stack.h"

// ----------------------------------------------------------------------------

void kf__press(uint16_t keycode) {
    usb__kb__set_key(true, keycode);
    usb__kb__send_report();
}

void kf__release(uint16_t keycode) {
    usb__kb__set_key(false, keycode);
    usb__kb__send_report();
}

void kf__toggle(uint16_t keycode) {
    if (usb__kb__read_key(keycode))
        usb__kb__set_key(false, keycode);
    else
        usb__kb__set_key(true, keycode):
}

void kf__layer__push(uint16_t id__layer) {
    layer_stack__push( ((uint8_t)(id__layer >> 8)),
                       ((uint8_t)(id__layer & 0xff)) );
}

void kf__layer__pop(uint16_t id__ignore) {
    layer_stack__pop_id( ((uint8_t)(id__ignore >> 8)) );
}

void kf__macro__sram(uint16_t pointer) {  // TODO
}

void kf__macro__progmem(uint16_t pointer) {  // TODO
}

void kf__macro__eeprom(uint16_t pointer) {  // TODO
}

