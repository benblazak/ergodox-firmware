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
 *
 * The `main__timer__` functions implement a sort of pseudo-timer, counting the
 * number of scan cycles instead of a set amount of real time.  They are here
 * because there isn't really a better place than `main()` to do that.  If you
 * need a real timer, take a look in ".../firmware/lib/timer".  If not, this is
 * probably a better set of functions to work with, since lower timer
 * resolution and not having to deal with an interrupt vector means lower
 * overhead and less overall to worry about.
 *
 * See ".../firmware/lib/timer.h" for more information on using timers in
 * general.
 */


#ifndef ERGODOX_FIRMWARE__FIRMWARE__MAIN__H
#define ERGODOX_FIRMWARE__FIRMWARE__MAIN__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


#include <stdbool.h>
#include <stdint.h>

// ----------------------------------------------------------------------------

extern bool (* main__is_pressed) [OPT__KB__ROWS][OPT__KB__COLUMNS];
extern bool (* main__was_pressed) [OPT__KB__ROWS][OPT__KB__COLUMNS];

extern uint8_t main__row;
extern uint8_t main__col;

extern bool main__update_leds;

// ----------------------------------------------------------------------------

uint8_t  main__timer__init     (void);
uint16_t main__timer__cycles   (void);
uint8_t  main__timer__schedule (uint16_t cycles, void(*function)(void));


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__FIRMWARE__MAIN__H



// ============================================================================
// === documentation ==========================================================
// ============================================================================


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

// === main__update_leds ===
/**                                     variables/main__update_leds/description
 * A predicate indicating whether to update the keyboard LED state based on the
 * USB LED state
 *
 * This is for taking over control the LEDs temporarily, as one may want to
 * do when in a special mode, etc.  If you want to change the meaning of the
 * LEDs under normal use, the correct place to do that is in the layout file,
 * where the `kb__led__logical_*()` functions are defined (see the
 * documentation in that and related files for more information).
 */


// ----------------------------------------------------------------------------
// functions ------------------------------------------------------------------
// ----------------------------------------------------------------------------

// === main__timer__init() ===
/**                                     functions/main__timer__init/description
 * Initialize the "timer"
 *
 * Returns:
 * - success: `0`
 * - failure: [other]
 *
 * Notes:
 * - Should be called by `main()` exactly once before entering the run loop.
 */

// === main__timer__cycles() ===
/**                                   functions/main__timer__cycles/description
 * Return the number of cycles since the timer was initialized (mod 2^16)
 *
 * Returns:
 * - success: The number of cycles since the timer was initialized (mod 2^16)
 */

// === main__timer__schedule() ===
/**                                 functions/main__timer__schedule/description
 * Schedule `function` to run in the given number of cycles
 *
 * Arguments:
 * - `cycles`: The number of cycles to wait
 * - `function`: A pointer to the function to run
 *
 * Returns:
 * - success: `0`
 * - failure: [other]
 *
 * Notes:
 * - If possible, prefer scheduling using this function over scheduling using
 *   `timer__schedule()`.  Functions run by this scheduler don't have to be
 *   quite as careful about finishing quickly, repeating too soon, or modifying
 *   shared variables, since they will be executing inside the `main()` loop
 *   instead of inside an interrupt vector.
 */

