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
#include "../../../../firmware/lib/usb.h"
#include "../../../../firmware/lib/layout/layer-stack.h"
#include "../key-functions.h"

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

// TODO: write documentation for this function
// TODO: this is a mistakenly written function; i'm going to change it.  what
//       we really want is a way to generate a "press" above a certain
//       threshold, and "release" going back the other way; this function would
//       make that possible, since it's quite general, but difficult and
//       space-consuming.
static void _chord__progmem(bool pressed, uint16_t pointer) {  // TODO: test
    #define  funptr  kf__function_pointer_t
    uint8_t * count                 = (uint8_t *) pgm_read_word( pointer   );
    uint16_t  threshold             = (uint16_t)  pgm_read_word( pointer+2 );
    funptr    function              = (funptr)    pgm_read_word( pointer+4 );
    uint16_t  argument              = (uint16_t)  pgm_read_word( pointer+6 );
    uint16_t  direction__comparison = (uint16_t)  pgm_read_word( pointer+8 );
    #undef  funptr

    char direction  = ((char)(behavior >> 8));
    char comparison = ((char)(behavior & 0xff));

    if (pressed) *count++;
    else         *count--;

    if ( (pressed  && direction == 'p') ||
         (!pressed && direction == 'r') )
        if ( (comparison == '=' && *count == threshold) ||
             (comparison == '<' && *count <  threshold) ||
             (comparison == '>' && *count >  threshold) )
            if (function)
                (*function)();
}

void kf__chord__press__progmem(uint16_t pointer) {
    _chord__progmem(true, pointer);
}

void kf__chord__release__progmem(uint16_t pointer) {
    _chord__progmem(false, pointer);
}

