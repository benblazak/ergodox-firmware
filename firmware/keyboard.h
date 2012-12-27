/* ----------------------------------------------------------------------------
 * keyboard interface
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef ERGODOX_FIRMWARE__FIRMWARE__KEYBOARD__H
#define ERGODOX_FIRMWARE__FIRMWARE__KEYBOARD__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

#include <stdbool.h>
#include <stdint.h>

// ----------------------------------------------------------------------------

// controller
int8_t kb__init          (void);
int8_t kb__update_matrix (bool matrix[MAKE__KB_ROWS][MAKE__KB_COLUMNS]);

// LED
void kb__led__on          (int8_t led);
void kb__led__off         (int8_t led);
void kb__led__set         (int8_t led, uint8_t n);
void kb__led__set_percent (int8_t led, float n);
// -------
void kb__led__all_on          (void);
void kb__led__all_off         (void);
void kb__led__all_set         (uint8_t n);
void kb__led__all_set_percent (float n);
// -------
void kb__led_state__power_on (void);
void kb__led_state__ready    (void);
void kb__led_delay__usb_init (void);
// -------
void kb__led__set_logical(char led, bool on);

// layout
// TODO


// ----------------------------------------------------------------------------
// documentation
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// controller -----------------------------------------------------------------

/**
 * name: kb__init
 * description: Initialize the keyboard
 * notes:
 *   - Should be called exactly once by `main()` before entering the run loop.
 */
/**
 * name: kb__update_matrix
 * description: Update the given matrix to the current state of the keyboard
 * arguments:
 *   bool matrix[MAKE__KB_ROWS][MAKE__KB_COLUMNS]:
 *     a pointer to the matrix to update
 */

// ----------------------------------------------------------------------------
// LED ------------------------------------------------------------------------

/**
 * &led__int8_t_led:
 *   The number of the LED to set.  Should an integer between 1 and 5
 *   inclusive; behavior is undefined otherwise.
 *
 *   notes:
 *   - For US keyboards, likely only LEDs 1 through 3 will be present.  But the
 *     function should handle 4 through 5 gracefully anyway.
 *
 * &led__uint8_t_n:
 *   The brightness at which to set the LED.  All values are legal.  Larger
 *   values mean a brighter LED.
 *
 * &led__float_n:
 *   The percent of the highest possible brightness at which to set the LED.
 *   Should be a float between 0 and 1 inclusive; behavior is undefined
 *   otherwise.
 */

/**
 * name: kb__led__on
 * description: Set the given LED 'on'.
 * arguments:
 *   int8_t led: *led__int8_t_led
 */
/**
 * name: kb__led__off
 * description: Set the given LED 'off'.
 * arguments:
 *   int8_t led: *led__int8_t_led
 */
/**
 * name: kb__led__set
 * description: Set the given LED's brightness (to an absolute value).
 * arguments:
 *   int8_t led: *led__int8_t_led
 *   uint8_t n: *led__uint8_t_n
 */
/**
 * name: kb__led__set_percent
 * description: Set the given LED's brightness (by percent).
 * arguments:
 *   int8_t led: *led__int8_t_led
 *   float n: *led__float_n
 */

/**
 * name: kb__led__all_on
 * description: Set all the LEDs 'on'
 */
/**
 * name: kb__led__all_off
 * description: Set all the LEDs 'off'
 */
/**
 * name: kb__led__all_set
 * description: Set all the LEDs brightness (to an absolute value).
 * arguments:
 *   uint8_t n: *led__uint8_t_n
 */
/**
 * name: kb__led__all_set_percent
 * description: Set all the LEDs brightness (by percent).
 * arguments:
 *   float n: *led__float_n
 */

/**
 * name: kb__led_state__power_on
 * description:
 *   Set the LEDs to the state that indicates the keyboard just powered on.
 */
/**
 * name: kb__led_state__ready
 * description:
 *   Set the LEDs to the state that indicates the keyboard is ready to receive
 *   keystrokes.
 */
/**
 * name: kb__led_delay__usb_init
 * description:
 *   Delay for a total of ~1 second, to allow the host to load drivers and
 *   such.
 */

/**
 * name: kb__led__set_logical
 * description:
 *   Set LEDs on or off based on their meaning (e.g. 'numlock', 'capslock').
 * arguments:
 *   char led:
 *     N: numlock
 *     C: capslock
 *     S: scroll lock
 *     O: compose
 *     K: kana
 *   bool on:
 *     1: set the LED on
 *     0: set the LED off
 */

// ----------------------------------------------------------------------------
// layout ---------------------------------------------------------------------


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__FIRMWARE__KEYBOARD__H
