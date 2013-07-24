/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Implements the layer-stack defined in "../layer-stack.h"
 *
 * Notes:
 * - This would be relatively trivial to implement using linked lists; but
 *   while I'm sure it takes more PROGMEM to do it this way, it uses less SRAM,
 *   and is also probably faster on average.  I also think it's a nice example
 *   of how to resize arrays in C based on demand.  I tried to generalize the
 *   functionality a little into a "flex-array" for "lib/data-types", in order
 *   to make the same technique easier to use elsewhere.  It turns out though
 *   that doing this in a type-agnostic way leads to passing an inordinate
 *   amount of information on the call stack for each function call (array
 *   size, element size, ..., ...), which for small stacks defeats the purpose
 *   (of saving SRAM), and is kind of inefficient and ugly anyway.  But
 *   sacrificing a bit of PROGMEM (and programmer time) to reimplement this
 *   everywhere it's used seems worth it, since the amount of core code that
 *   would be able to be generalized out anyway is relatively small and
 *   straightforward.
 */


#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "../layer-stack.h"

// ----------------------------------------------------------------------------

/**                                               macros/MIN_UNUSED/description
 * The minimum number of elements to have unused after a resize
 */
#define  MIN_UNUSED  0

/**                                               macros/MAX_UNUSED/description
 * The maximum number of elements to have unused after a resize
 */
#define  MAX_UNUSED  4

// ----------------------------------------------------------------------------

/**                                                 types/element_t/description
 * The type of one layer-element in our layer-stack
 *
 * Struct members:
 * - `id`: The layer-id of this element
 * - `number`: The layer-number of this element
 */
typedef struct {
    uint8_t id;
    uint8_t number;
}  element_t;

// ----------------------------------------------------------------------------

/**                                                 variables/stack/description
 * To hold the layer-stack and directly related metadata
 *
 * Struct members:
 * - `allocated`:  The number of positions allocated
 * - `filled`: The number of positions filled
 * - `data`: A pointer to the array of layer-elements
 *
 * Notes:
 * - The maximum value of `uint8_t filled` is `UINT8_MAX` indicating a stack
 *   with `UINT8_MAX` elements.  This means that any valid offset or index will
 *   be between `0` and `UINT8_MAX-1` inclusive, and that `UINT8_MAX` will
 *   therefore always be an invalid value for an offset or index.
 */
static struct {
    uint8_t allocated;
    uint8_t filled;
    element_t * data;
} stack;

// ----------------------------------------------------------------------------

/**                                          functions/resize_stack/description
 * Resize the stack, so that the number of unused elements is between
 * `MIN_UNUSED` and `MAX_UNUSED`, inclusive
 *
 * Returns:
 * - success: `0`
 * - failure: [other]
 *
 * Implementation notes:
 * - We use a signed type for `unused` in case `filled` is greater than
 *   `allocated`, as may happen when pushing a new element onto the stack.
 *   This number should normally be much smaller than either `filled` or
 *   `allocated`, so we don't need to worry about the maximum value being 2^7-1
 *   instead of 2^8-1.
 * - The only time `realloc()` should fail is if we are trying to grow the
 *   stack.  See [the documentation]
 *   (http://www.nongnu.org/avr-libc/user-manual/malloc.html)
 *   for `malloc()` in avr-libc.
 */
static uint8_t resize_stack(void) {
    int8_t unused = stack.allocated - stack.filled;

    if (MIN_UNUSED <= unused && unused <= MAX_UNUSED)
        return 0;  // nothing to do

    uint8_t new_allocated;
    if (UINT8_MAX >= stack.filled + (MIN_UNUSED+MAX_UNUSED)/2)
        new_allocated = stack.filled + (MIN_UNUSED+MAX_UNUSED)/2;
    else if (UINT8_MAX >= stack.filled + MIN_UNUSED)
        new_allocated = UINT8_MAX;
    else
        return 1;  // unable to count the required number of elements

    void * new_data = realloc( stack.data, sizeof(element_t) * new_allocated );
    if (!new_data)
        return 1;  // error: `realloc()` failed (unable to grow stack)

    stack.allocated = new_allocated;
    stack.data = new_data;

    return 0;  // success
}

// ----------------------------------------------------------------------------

uint8_t layer_stack__peek(uint8_t offset) {
    if (offset > stack.filled-1)
        return 0;  // default

    return stack.data[stack.filled-1-offset].number;
}

uint8_t layer_stack__push( uint8_t offset,
                           uint8_t layer_id,
                           uint8_t layer_number ) {

    // if an element with the given layer-id already exists
    {
        uint8_t old_offset = layer_stack__find_id(layer_id);
        if (old_offset != UINT8_MAX) {
            stack.data[stack.filled-1-old_offset].number = layer_number;
            return old_offset;
        }
    }

    // add an element
    if (stack.filled == UINT8_MAX)
        return UINT8_MAX;  // error: stack already full
    stack.filled++;
    uint8_t index = stack.filled-1-offset;
    if (index > stack.filled-1 || resize_stack()) {
        stack.filled--;
        return UINT8_MAX;  // error: index out of bounds, or resize failed
    }

    // shift up
    // - start with the top element (which is currently uninitialized), and
    //   copy the element below it up
    // - continue until we copy the element currently at `index` (which will
    //   then be duplicated at `index` and `index-1`)
    // - if the top element is currently at `index`, this will do nothing
    for (uint8_t i = stack.filled-1; i > index; i--)
        stack.data[i] = stack.data[i-1];

    // set values
    stack.data[index].id = layer_id;
    stack.data[index].number = layer_number;

    return offset;  // success
}

uint8_t layer_stack__pop_id(uint8_t layer_id) {
    uint8_t offset = layer_stack__find_id(layer_id);

    if (offset == UINT8_MAX)
        return UINT8_MAX;  // error: no element with given layer-id

    uint8_t index = stack.filled-1-offset;

    // shift down
    // - start with the element at `index`, and copy the element above it down
    // - continue until we copy the top element (which will then be duplicated
    //   at indices `stack.filled-2` and `stack.filled-1`)
    // - if the top element is at `index`, this will do nothing
    for (uint8_t i = index; i < stack.filled-1; i++)
        stack.data[i] = stack.data[i+1];

    // remove an element
    stack.filled--;
    resize_stack();  // we're shrinking the stack, so this should never fail

    return offset;  // success
}

uint8_t layer_stack__find_id(uint8_t layer_id) {
    for (uint8_t i = 0; i < stack.filled; i++)
        if (stack.data[i].id == layer_id)
            return stack.filled-1-i;  // offset
    return UINT8_MAX;  // error: no element with given layer-id
}

uint8_t layer_stack__size(void) {
    return stack.filled;
}

