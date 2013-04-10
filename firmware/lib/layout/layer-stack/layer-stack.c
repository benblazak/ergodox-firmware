/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Implements the layer-stack defined in "../layer-stack.h"
 *
 * TODO:
 * - reorganize (if necessary) / check everything
 * - properly document (with script-readable comment blocks...)
 * - see the '.h' for interface TODOs
 */


#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

// ----------------------------------------------------------------------------

#define  BLOCK_SIZE  5  // the number of elements to (de)allocate at once
#define  MARGIN      3  // the number of elements keep open (when deallocating)

// ----------------------------------------------------------------------------

typedef struct {
    uint8_t id;
    uint8_t number;
}  element_t;

uint8_t     _allocated = 0;
uint8_t     _filled    = 0;
element_t * _stack     = NULL;

// ----------------------------------------------------------------------------

// TODO: is this the cleanest implemenetation?
// TODO: should this be split out into a separate "lib/data-types/flex-array"
// or something?
static uint8_t _resize_stack(void) {
    uint8_t margin = _allocated - _filled;
    if (margin == 0 || margin > MARGIN + BLOCK_SIZE) {
        uint8_t change = (margin == 0) ? BLOCK_SIZE : -BLOCK_SIZE;
        uint8_t new_size = sizeof(element_t) * (_allocated + change);
        element_t * temp = (element_t *) realloc(_data, new_size);
        if (temp) {
            _data = temp;
            _allocated += change;
            return 0;  // success
        } else {
            return 1;  // error
        }
    }
}

static uint8_t _shift_elements(uint8_t offset, bool up) {
    // TODO: maybe we want this function to be the one that calls
    // _resize_stack()?

    // TODO: arguments:
    // - offset: the element we want open, or the element we want to cover by
    //   shifting down
    // - up: whether to shift the elements up or down

    // TODO: should we be able to shift by more than one element at a time?
    // probably not, but should consider it

}

// ----------------------------------------------------------------------------

uint8_t layer_stack__peek   (uint8_t offset) {
}

uint8_t layer_stack__push   (uint8_t layer_id, uint8_t layer_number) {
    // TODO: resize first, push after
}

uint8_t layer_stack__pop_id (uint8_t layer_id) {
    // TODO: remove first, resize after
}

uint8_t layer_stack__size   (void) {
    return _filled;
}

