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
 * implemenmtation.
 */


#ifndef ERGODOX_FIRMWARE__LIB__LAYOUT__LAYER_STACK__H
#define ERGODOX_FIRMWARE__LIB__LAYOUT__LAYER_STACK__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


uint8_t layer_stack__peek   (uint8_t offset);
uint8_t layer_stack__push   (uint8_t layer_id, uint8_t layer_number);
uint8_t layer_stack__pop_id (uint8_t layer_id);
uint8_t layer_stack__size   (void);


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__LIB__LAYOUT__LAYER_STACK__H



// ============================================================================
// === documentation ==========================================================
// ============================================================================

// === layer_stack__peek() ===
/**                                     functions/layer_stack__peek/description
 * Return the `offset`th element of the layer stack
 *
 * Arguments:
 * - `offset`: the offset of the element to return (with the top being
 *   `offset = 0`)
 *
 * Returns:
 * - success: the layer-number of the `offset`th element, or `0` if `offset`
 *   was out of bounds
 */

// === layer_stack__push() ===
/**                                     functions/layer_stack__push/description
 * Push the given element onto the top of the layer stack (or update the
 * element if it already exists)
 *
 * Arguments:
 * - `layer_id`: the ID of the layer to push
 * - `layer_number`: the layer-number of the layer to push
 *
 * Returns:
 * - success: the offset of the element that was pushed (or pudated)
 *
 * Notes:
 * - If the given layer-id is not present in the stack, a new element is
 *   created and placed on the top of the stack (as expected)
 * - If the given layer-id is present in the stack, the element with that ID is
 *   updated
 */

// === layer_stack__pop_id() ===
/**                                   functions/layer_stack__pop_id/description
 * Pop the given element (by ID) out from the layer stack
 *
 * Arguments:
 * - `layer_id`: the ID of the layer to push
 *
 * Returns:
 * - success: the offset of the element that was pushed (or pudated)
 */

// === layer_stack__size ===
/**                                     functions/layer_stack__size/description
 * Return the current size (height) of the layer stack
 *
 * Returns:
 * - success: the current size (height) of the layer stack (`0` if empty)
 */

