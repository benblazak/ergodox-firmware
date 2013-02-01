/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Things kept track of by `main()` that need to be accessible to other parts
 * of the program.
 *
 * Prefix: `main__`
 */


#ifndef ERGODOX_FIRMWARE__FIRMWARE__MAIN__H
#define ERGODOX_FIRMWARE__FIRMWARE__MAIN__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


uint8_t main__layer_stack__peek   (uint8_t offset);
uint8_t main__layer_stack__push   (uint8_t layer_id, uint8_t layer_number);
uint8_t main__layer_stack__pop_id (uint8_t layer_id);


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__FIRMWARE__MAIN__H



// ============================================================================
// === documentation ==========================================================
// ============================================================================

// TODO

