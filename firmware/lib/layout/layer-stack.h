/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Layer-stack interface
 *
 * Prefix: `layer_stack__`
 *
 * This file is meant to be included and used by the keyboard layout
 * implementation.
 */


#ifndef ERGODOX_FIRMWARE__LIB__LAYOUT__LAYER_STACK__H
#define ERGODOX_FIRMWARE__LIB__LAYOUT__LAYER_STACK__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


#include <stdint.h>

// ----------------------------------------------------------------------------

uint8_t layer_stack__peek    (uint8_t offset);
uint8_t layer_stack__push    ( uint8_t offset,
                               uint8_t layer_id,
                               uint8_t layer_number );
uint8_t layer_stack__pop_id  (uint8_t layer_id);
uint8_t layer_stack__find_id (uint8_t layer_id);
uint8_t layer_stack__size    (void);


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__LIB__LAYOUT__LAYER_STACK__H



// ============================================================================
// === documentation ==========================================================
// ============================================================================

// === layer_stack__peek() ===
/**                                     functions/layer_stack__peek/description
 * Return the layer-number of the `offset`th element of the layer-stack
 *
 * Arguments:
 * - `offset`: the `offset` of the element to return (with the top element
 *   being `offset = 0`)
 *
 * Returns:
 * - success: the layer-number of the `offset`th element (which may be `0`), or
 *   `0` if `offset` was out of bounds
 */

// === layer_stack__push() ===
/**                                     functions/layer_stack__push/description
 * Push the given element into the layer-stack on top of the element with the
 * given `offset` (or update the element with the given layer-id, if it already
 * exists)
 *
 * Arguments:
 * - `offset`: the `offset` of the element on top of which to push the given
 *   element (with the top element being `offset = 0`)
 * - `layer_id`: the layer-id of the layer to push
 * - `layer_number`: the layer-number of the layer to push (ignored if not
 *   pushing a new element)
 *
 * Returns:
 * - success: the `offset` of the element that was pushed (or updated)
 * - failure: `UINT8_MAX`
 *
 * Notes:
 * - If the given layer-id is not present in the stack, and a new element is
 *   created and pushed on top of the element with the given `offset`, the new
 *   element will now be at position `offset`, since `offset` is the distance
 *   from the top of the stack
 * - If the given layer-id is present in the stack, the element with that
 *   layer-id is updated; this preserves the expectation that all layer-id's in
 *   the stack will be unique
 */

// === layer_stack__pop_id() ===
/**                                   functions/layer_stack__pop_id/description
 * Pop the given element (by ID) out from the layer-stack
 *
 * Arguments:
 * - `layer_id`: the layer-id of the layer to pop (remove)
 *
 * Returns:
 * - success: the `offset` of the element that was popped (removed)
 * - failure: `UINT8_MAX`
 */

// === layer_stack__find_id() ===
/**                                  functions/layer_stack__find_id/description
 * Find an element element by ID
 *
 * Arguments:
 * - `layer_id`: the layer-id of the layer to find
 *
 * Returns:
 * - success: the `offset` of the element that was found
 * - failure: `UINT8_MAX`
 */

// === layer_stack__size ===
/**                                     functions/layer_stack__size/description
 * Return the current size (height) of the layer-stack
 *
 * Returns:
 * - success: the current size (height) of the layer-stack (`0` if empty)
 */

