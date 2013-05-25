/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * The `main()` interface for the rest of the program
 *
 * Prefix: `main__`
 *
 * Certain variables are declared here so that other functions can see (and
 * perhaps modify) them, to accomplish things that may be difficult otherwise.
 */


#ifndef ERGODOX_FIRMWARE__FIRMWARE__MAIN__H
#define ERGODOX_FIRMWARE__FIRMWARE__MAIN__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


#include <stdbool.h>
#include <stdint.h>

// ----------------------------------------------------------------------------

struct main__flags_t {
    bool update_leds : 1;
};

// ----------------------------------------------------------------------------

extern bool (* main__is_pressed) [OPT__KB__ROWS][OPT__KB__COLUMNS];
extern bool (* main__was_pressed) [OPT__KB__ROWS][OPT__KB__COLUMNS];

extern uint8_t main__row;
extern uint8_t main__col;

extern struct main__flags_t main__flags;


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__FIRMWARE__MAIN__H



// ============================================================================
// === documentation ==========================================================
// ============================================================================


// ----------------------------------------------------------------------------
// types ----------------------------------------------------------------------
// ----------------------------------------------------------------------------

// === main__flags_t ===
/**                                      types/struct main__flags_t/description
 * See the documentation for `main__flags`
 */


// ----------------------------------------------------------------------------
// variables ------------------------------------------------------------------
// ----------------------------------------------------------------------------

// === main__is_pressed ===
/**                                      variables/main__is_pressed/description
 * A matrix of `bool`s indicating whether the key at a given position is
 * currently pressed
 */

// === main__was_pressed ===
/**                                     variables/main__was_pressed/description
 * A matrix of `bool`s indicating whether the key at a given position was
 * pressed on the previous scan
 */

// === main__row ===
/**                                             variables/main__row/description
 * Indicates which row is currently being tested for changes of key state
 */

// === main__col ===
/**                                             variables/main__col/description
 * Indicates which column is currently being tested for changes of key state
 */

// === main__flags ===
/**                                           variables/main__flags/description
 * A collection of flags pertaining to the operation of `main()`
 *
 * Struct members:
 * - `update_leds`: A predicate indicating whether to update the keyboard LED
 *   state based on the USB LED state.
 *     - This is for taking over control the LEDs temporarily, as one may want
 *       to do when in a special mode, etc.  If you want to change the meaning
 *       of the LEDs under normal use, the correct place to do that is in the
 *       layout file, where the `kb__led__logical_...()` functions are defined
 *       (see the documentation in that and related files for more
 *       information).
 */

