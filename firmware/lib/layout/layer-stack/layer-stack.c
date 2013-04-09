/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Implements the layer-stack defined in "../layer-stack.h"
 *
 * TODO: implement, document, everything
 * - this needs to be reorganized
 * - much of this should probably be split out into a generic flexable_array
 *   type of some sort (unless the grow and shrink functions are really small)
 */


#include <stdint.h>
#include <stdlib.h>

// ----------------------------------------------------------------------------

#define  BLOCK_SIZE  5
#define  TYPE_SIZE   sizeof(element_t)
#define  MARGIN      3

// ----------------------------------------------------------------------------

typedef struct {
    uint8_t id;
    uint8_t number;
}  element_t;

typedef struct {
    uint8_t     allocated;
    uint8_t     filled;
    element_t * data;
} stack_t;

// ----------------------------------------------------------------------------

stack_t _stack = {
    .allocated = BLOCK_SIZE,
    .filled    = 0,
    .data      = (element_t *) malloc( TYPE_SIZE * BLOCK_SIZE ),
};

// todo: this should not be the final function
static uint8_t _resize_stack(stack_t stack) {
    uint8_t margin = stack.allocated - stack.filled;
    if (margin == 0 || margin > MARGIN) {
        uint8_t new_size = stack.allocated + TYPE_SIZE * (margin == 0)
                                                         ?  BLOCK_SIZE
                                                         : -BLOCK_SIZE;
        element_t * temp = (element_t *) realloc(stack.data, new_size);
        if (temp) {
            stack.data = temp;
            stack.allocated += (margin == 0) ? BLOCK_SIZE : -BLOCK_SIZE;
            return 0;  // success
        } else {
            return 1;  // error
        }
}

// ----------------------------------------------------------------------------

uint8_t layer_stack__peek   (uint8_t offset) {
}

uint8_t layer_stack__push   (uint8_t layer_id, uint8_t layer_number) {
}

uint8_t layer_stack__pop_id (uint8_t layer_id) {
}

uint8_t layer_stack__size   (void) {
}

