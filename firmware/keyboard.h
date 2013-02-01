/* ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * The keyboard interface, and related definitions.
 *
 * Keyboard implementations must conditionally define their dimensions in this
 * file, and implement all prototyped functions.
 *
 * Prefix: `kb__`
 */


#ifndef ERGODOX_FIRMWARE__FIRMWARE__KEYBOARD__H
#define ERGODOX_FIRMWARE__FIRMWARE__KEYBOARD__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


#include <stdbool.h>
#include <stdint.h>

// ----------------------------------------------------------------------------

#if MAKE__KEYBOARD == 'ergodox'

    #define  KB__ROWS      6
    #define  KB__COLUMNS  14

#else

    #error "Keyboard dimensions must be defined"

#endif

// ----------------------------------------------------------------------------

// controller
uint8_t kb__init          (void);
uint8_t kb__update_matrix (bool matrix[KB__ROWS][KB__COLUMNS]);

// LED
void kb__led__on  (uint8_t led);
void kb__led__off (uint8_t led);
void kb__led__set (uint8_t led, float n);
// -------
void kb__led__all_on  (void);
void kb__led__all_off (void);
void kb__led__all_set (float percent);
// -------
void kb__led__state__power_on (void);
void kb__led__state__ready    (void);
void kb__led__delay__usb_init (void);

// layout
void kb__led__logical_on  (char led);
void kb__led__logical_off (char led);
// -------
uint8_t kb__layout__exec_key ( bool    pressed,
                               uint8_t layer,
                               uint8_t row,
                               uint8_t column );


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__FIRMWARE__KEYBOARD__H



// ============================================================================
// === documentation ==========================================================
// ============================================================================


// ----------------------------------------------------------------------------
// macros ---------------------------------------------------------------------
// ----------------------------------------------------------------------------

// === KB__ROWS ===
/**                                                 macros/KB__ROWS/description
 * The number of rows in a given keyboard's matrix
 */

// === KB__COLUMNS ===
/**                                              macros/KB__COLUMNS/description
 * The number of columns in a given keyboard's matrix
 */


// ----------------------------------------------------------------------------
// functions ------------------------------------------------------------------
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// controller -----------------------------------------------------------------

// === kb__init() ===
/**                                              functions/kb__init/description
 * Initialize the keyboard.
 *
 * Returns:
 * - success: `0`
 * - failure: [other]
 *
 * Notes:
 * - Should be called exactly once by `main()` before entering the run loop.
 */

// === kb__update_matrix() ===
/**                                     functions/kb__update_matrix/description
 * Update the given matrix to the current state of the keyboard.
 *
 * Arguments:
 * - `matrix`: The keyboard matrix to update.
 *
 * Returns:
 * - success: `0`
 * - failure: [other]
 */


// ----------------------------------------------------------------------------
// LED ------------------------------------------------------------------------

// === kb__led__on() ===
/**                                           functions/kb__led__on/description
 * Set the given LED 'on'.
 *
 * Arguments:
 * - `led`: The number of the LED to set.  Should be an integer between 1 and 5
 *   inclusive; behavior is undefined otherwise.
 *
 * Notes:
 * - For US keyboards, likely only LEDs 1 through 3 will be physically present;
 *   but the function should handle 4 through 5 gracefully anyway.
 */

// === kb__led__off() ===
/**                                          functions/kb__led__off/description
 * Set the given LED 'off'.
 *
 * Arguments:
 * - `led`: The number of the LED to set.  Should be an integer between 1 and 5
 *   inclusive; behavior is undefined otherwise.
 *
 * Notes:
 * - For US keyboards, likely only LEDs 1 through 3 will be physically present;
 *   but the function should handle 4 through 5 gracefully anyway.
 */

// === kb__led__set() ===
/**                                          functions/kb__led__set/description
 * Set the given LED's brightness (by percent).
 *
 * Arguments:
 * - `led`: The number of the LED to set.  Should be an integer between 1 and 5
 *   inclusive; behavior is undefined otherwise.
 * - `percent`: The percent of the highest possible brightness at which to set
 *   the LED.  Should be a float between 0 and 1 inclusive; behavior is
 *   undefined otherwise.
 *
 * Notes:
 * - For US keyboards, likely only LEDs 1 through 3 will be physically present;
 *   but the function should handle 4 through 5 gracefully anyway.
 */

// ----------------------------------------------------------------------------

// === kb__led__all_on() ===
/**                                       functions/kb__led__all_on/description
 * Set all the LEDs 'on'.
 */

// === kb__led__all_off() ===
/**                                      functions/kb__led__all_off/description
 * Set all the LEDs 'off'.
 */

// === kb__led__all_set() ===
/**                                      functions/kb__led__all_set/description
 * Set all the LEDs' brightness (by percent).
 *
 * Arguments:
 * - `percent`: The percent of the highest possible brightness at which to set
 *   the LED.  Should be a float between 0 and 1 inclusive; behavior is
 *   undefined otherwise.
 */

// ----------------------------------------------------------------------------

// === kb__led__state__power_on() ===
/**                              functions/kb__led__state__power_on/description
 * Set the LEDs to the state that indicates the keyboard just powered on.
 */

// === kb__led__state__ready() ===
/**                                 functions/kb__led__state__ready/description
 * Set the LEDs to the state that indicates the keyboard is ready to receive
 * keystrokes.
 */

// === kb__led__delay__usb_init() ===
/**                              functions/kb__led__delay__usb_init/description
 * Delay for a total of ~1 second, to allow the host to load drivers and such.
 */


// ----------------------------------------------------------------------------
// layout ---------------------------------------------------------------------

// === kb__led__logical_on ===
/**                                   functions/kb__led__logical_on/description
 * Set LEDs 'on' based ontheir meaning (e.g. 'numlock', 'capslock').
 *
 * Arguments:
 * - `led`:
 *     - `N`: numlock
 *     - `C`: capslock
 *     - `S`: scroll lock
 *     - `O`: compose
 *     - `K`: kana
 */

// === kb__led__logical_off ===
/**                                  functions/kb__led__logical_off/description
 * Set LEDs 'off' based ontheir meaning (e.g. 'numlock', 'capslock').
 *
 * Arguments:
 * - `led`:
 *     - `N`: numlock
 *     - `C`: capslock
 *     - `S`: scroll lock
 *     - `O`: compose
 *     - `K`: kana
 */

// ----------------------------------------------------------------------------

// === kb__layout__exec_key ===
/**                                  functions/kb__layout__exec_key/description
 * Perform the appropriate actions for a "press" or "release" of the key at the
 * given position.
 *
 * Arguments:
 * - `pressed`:
 *     - `true`: Indicates that the key to be "executed" has been pressed
 *     - `false`: Indicates that the key to be "executed" has been released
 * - `layer`: The layer of the key to be "executed"
 * - `row`: The row of the key to be "executed"
 * - `column`: The column of the key to be "executed"
 *
 * Returns:
 * - success: The layer of the key that was "executed"; this should be passed
 *   back by `main()` as `layer` when the key at the same `[row][column]` is
 *   released.
 *
 * Notes:
 * - This function is responsible for quite a bit of a keyboard's apparent
 *   functionality.  It needs to be implemented at this level in order to hide
 *   the actual representation of keys, where they are stored, etc. from
 *   `main()`.
 */

