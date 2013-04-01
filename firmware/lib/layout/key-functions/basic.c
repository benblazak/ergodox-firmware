/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Implements the "basic" section of
 * ".../firmware/lib/layout/key-functions.h"
 */

#include <stdbool.h>
#include <stdint.h>
#include <avr/pgmspace.h>
#include "../../../../firmware/keyboard.h"
#include "../../../../firmware/lib/usb.h"
#include "../../../../firmware/lib/layout/layer-stack.h"
#include "../key-functions.h"

// ----------------------------------------------------------------------------

static void _chord__progmem(bool pressed, void * pointer) {  // TODO: test
    uint8_t * count       = (uint8_t *) pgm_read_word( pointer   );
    uint16_t  threshold   = (uint16_t)  pgm_read_word( pointer+2 );
    void *    key_pointer = (void *)    pgm_read_word( pointer+4 );

    if (pressed)
        *count++;

    if (*count == threshold)
        kb__layout__exec_key_pointer(key_pointer);

    if (!pressed)
        *count--;
}

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

void kf__macro__progmem(uint16_t pointer) {  // TODO: test
    uint16_t last_element = pointer + 4 * (uint16_t) pgm_read_word(pointer);

    kf__function_pointer_t function;
    uint16_t               argument;

    for(pointer += 2; pointer <= last_element; pointer += 4) {
        function = (kf__function_pointer_t) pgm_read_word( pointer   );
        argument = (uint16_t)               pgm_read_word( pointer+2 );

        if (function)
            (*function)(argument);
    }
}

void kf__chord__press__progmem(uint16_t pointer) {
    _chord__progmem(true, pointer);
}

void kf__chord__release__progmem(uint16_t pointer) {
    _chord__progmem(false, pointer);
}

