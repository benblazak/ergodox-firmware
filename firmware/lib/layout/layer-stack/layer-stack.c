/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Implements the layer-stack defined in "../layer-stack.h"
 *
 * TODO:
 * - see the '.h' for interface TODOs
 * - should we split most of this functionality into a general 'flex_array' or
 *   something?  we probably should...  think about how to do that.
 */


#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

// ----------------------------------------------------------------------------

/**                                               macros/BLOCK_SIZE/description
 * The number of positions to allocate or deallocate at once
 */
#define  BLOCK_SIZE  5

/**                                                   macros/MARGIN/description
 * The number of positions to keep unused when deallocating
 */
#define  MARGIN  3

// ----------------------------------------------------------------------------

typedef struct {
    uint8_t id;      // layer-id
    uint8_t number;  // layer-number
}  element_t;

uint8_t     _allocated = 0;     // the number of positions allocated
uint8_t     _filled    = 0;     // the number of positions filled
element_t * _stack     = NULL;  // (to be used as an array)

// ----------------------------------------------------------------------------

/**                                         functions/_resize_stack/description
 * Resize the stack (in increments of `BLOCK_SIZE` positions) so that at least
 * 1 and no more than `MARGIN + BLOCK_SIZE - 1` positions are unused.
 *
 * Returns:
 * - success: `0`
 * - failure: [other]
 */
static uint8_t _resize_stack(void) {
    uint8_t margin = _allocated - _filled;
    if (margin == 0 || margin >= MARGIN + BLOCK_SIZE) {
        uint8_t change = (margin == 0) ? BLOCK_SIZE : -BLOCK_SIZE;
        uint8_t new_size = sizeof(element_t) * (_allocated + change);
        element_t * temp = (element_t *) realloc(_stack, new_size);
        if (temp) {
            _stack = temp;
            _allocated += change;
            return 0;  // success
        } else {
            return 1;  // error
        }
    }
}

/**                                       functions/_shift_elements/description
 * Shift the elements above the given location either up or down by one.
 *
 * Arguments:
 * - `offset`: The offset of the element above which to operate (with the top
 *   element being `offset = 0`)
 * - `up` : Whether to shift the elements "up" or "down" the stack
 *
 * Returns:
 * - success: `0`
 * - failure: [other]
 *
 * Notes:
 * - This function *only* copies elements.  It does not zero or otherwise
 *   modify locations that logically should no longer have any element in them.
 *   It also does not modify the stack's counter for how many elements are
 *   filled.
 *
 * - We must have at least one element free (at the top of the stack) in order
 *   to copy up.
 *
 * - Copying down will do nothing if `offset` is `0`.
 *
 *
 * Illustration:
 *
 * ```
 *                    ,- top = 4 = filled-1
 *                   |
 * +---+---+---+---+---+---+---+
 * | 0 | 1 | 2 | 3 | 4 | 5 | 6 |       allocated = 7   filled = 5
 * +---+---+---+---+---+---+---+
 *       ^
 *       ` offset = 3
 *
 *
 * copy up: start = 4 = top = filled-1
 *          increment: i-- (start at the top and work down)
 *          end = 1 = top-offset = filled-1-offset
 *
 * copy down: start = 2 = top-offset+1 = filled-1-offset+1 = filled-offset
 *            increment: i++ (start just above the given element and work up)
 *            end = 4 = top = filled-1
 * ```
 */
static uint8_t _shift_elements(uint8_t offset, bool up) {
    uint8_t margin = _allocated - _filled;
    if ( offset < 0 || offset > _filled-1 || (up && (margin==0)) )
        return 1;  // failure

    uint8_t start     = (up) ? _filled-1        : _filled-offset ;
    uint8_t increment = (up) ? -1               : 1              ;
    uint8_t end       = (up) ? _filled-1-offset : _filled-1      ;

    for(uint8_t i=start; i!=(end+increment); i+=increment) {
        _stack[i-increment].id     = _stack[i].id;
        _stack[i-increment].number = _stack[i].number;
    }

    return 0;  // success
}

// ----------------------------------------------------------------------------

uint8_t layer_stack__peek   (uint8_t offset) {
    if ( offset < 0 || offset > _filled-1 )
        return 0;  // default

    return _stack[filled-1-offset].number;
}

// note: must resize before shifting up, otherwise there may not be enough room
// for the new element
uint8_t layer_stack__push   (uint8_t layer_id, uint8_t layer_number) {
    // need to add `offset` as an argument; see '.h'
}

// note: should resize after shifting down, so as to only leave `MARGIN`
// elements free in the stack
uint8_t layer_stack__pop_id (uint8_t layer_id) {
    // will use find_id(), which isn't written yet; see '.h'
}

uint8_t layer_stack__size   (void) {
    return _filled;
}

