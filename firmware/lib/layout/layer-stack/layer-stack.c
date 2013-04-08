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
 *   type of some sort
 */


#include <stdint.h>
#include <stdlib.h>

// ----------------------------------------------------------------------------

#define  BLOCK_SIZE  5

// ----------------------------------------------------------------------------

typedef struct {
    uint8_t id;
    uint8_t number;
}  element_t;

typedef struct {
    uint8_t     size_allocated;
    uint8_t     size_filled;
    element_t * data;
} stack_t;

stack_t stack = { .size_allocated = BLOCK_SIZE;
                  .size_filled    = 0,
                  .data           = malloc( sizeof(element *) * BLOCK_SIZE ); };

uint8_t grow_stack(stack_t stack) {
    element_t * temp = realloc( stack.data, stack.size_allocated + BLOCK_SIZE );
    if (temp) {
        stack.data = temp;
        stack.size_allocated += BLOCK_SIZE;
        return 0;
    } else {
        return 1;
    }
}

uint8_t shrink_stack(stack_t stack) {
    if (stack.size_allocated == BLOCK_SIZE)
        return 0;

    element_t * temp = realloc( stack.data, stack.size_allocated - BLOCK_SIZE );
    if (temp) {
        stack.data = temp;
        stack.size_allocated -= BLOCK_SIZE;
        return 0;
    } else {
        return 1;
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

