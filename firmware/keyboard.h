/* ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/license.md")
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
void kb__led__all_set (float n);
// -------
void kb__led__state__power_on (void);
void kb__led__state__ready    (void);
void kb__led__delay__usb_init (void);

// layout
void kb__led__logical_on  (char led);
void kb__led__logical_off (char led);
// -------
void kb__layout__exec_key ( bool    pressed,
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
/*                                                  macros/KB__ROWS/description
 * The number of rows in a given keyboard's matrix
 */

// === KB__COLUMNS ===
/*                                               macros/KB__COLUMNS/description
 * The number of columns in a given keyboard's matrix
 */

// ----------------------------------------------------------------------------
// functions ------------------------------------------------------------------
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// controller -----------------------------------------------------------------

// === kb__init() ===
/*                                               functions/kb__init/description
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
/*                                      functions/kb__update_matrix/description
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

// ----------------------------------------------------------------------------
// layout ---------------------------------------------------------------------


// TODO: rewrite, coz of changes
/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  # documentation ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-
  # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  
  # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  # functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  # controller ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-

  # LED ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~--

   - .ignore:
     
     - &kb__led___int8_t__led
       type: '`int8_t`'
       name: '`led`'
       description:
         The number of the LED to set.  Should an integer between 1 and 5
         inclusive; behavior is undefined otherwise.
       notes:
         - For US keyboards, likely only LEDs 1 through 3 will be present.  But
           the function should handle 4 through 5 gracefully anyway.
  
     - &kb__led___float__n
       type: '`float`'
       name: '`n`'
       description:
         The percent of the highest possible brightness at which to set the
         LED.  Should be a float between 0 and 1 inclusive; behavior is
         undefined otherwise.

  # ~~~~~~~

   - function:
       name: '`kb__led__on`'
       description: Set the given LED 'on'.
       arguments:
         - *kb__led___int8_t__led
  
   - function:
       name: '`kb__led__off`'
       description: Set the given LED 'off'.
       arguments:
         - *kb__led___int8_t__led
  
   - function:
       name: '`kb__led__set`'
       description: Set the given LED's brightness (by percent).
       arguments:
         - *kb__led___int8_t__led
         - *kb__led___float__n

  # ~~~~~~~

   - function:
       name: '`kb__led__all_on`'
       description: Set all the LEDs 'on'.
  
   - function:
       name: '`kb__led__all_off`'
       description: Set all the LEDs 'off'.
  
   - function:
       name: '`kb__led__all_set`'
       description: Set all the LEDs brightness (by percent).
       arguments:
         - *kb__led___float__n

  # ~~~~~~~

   - function:
       name: '`kb__led__state__power_on`'
       description:
         Set the LEDs to the state that indicates the keyboard just powered on.
  
   - function:
       name: '`kb__led__state__ready`'
       description:
         Set the LEDs to the state that indicates the keyboard is ready to
         receive keystrokes.
  
   - function:
       name: '`kb__led__delay__usb_init`'
       description:
         Delay for a total of ~1 second, to allow the host to load drivers and
         such.

  # layout ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~--

   - .ignore:
  
     - &kb__led__logical___arguments
         - type: '`char`'
           name: '`led`'
           values:
             - { name: '`N`', description: numlock }
             - { name: '`C`', description: capslock }
             - { name: '`S`', description: scroll lock }
             - { name: '`O`', description: compose }
             - { name: '`K`', description: kana }

  # ~~~~~~~

   - function:
       name: '`kb__led__logical_on`'
       description:
         Set LEDs on based on their meaning (e.g. 'numlock', 'capslock').
       arguments: *kb__led__logical___arguments
  
   - function:
       name: '`kb__led__logical_off`'
       description:
         Set LEDs off based on their meaning (e.g. 'numlock', 'capslock').
       arguments: *kb__led__logical___arguments

  # ~~~~~~~

   - function:
       name: '`kb__layout__get_key`'
       description:
         Look up and return the contents of the layout matrix at the given
         point.
       arguments:
         - { type: '`uint8_t`', name: '`layer`' }
         - { type: '`uint8_t`', name: '`row`' }
         - { type: '`uint8_t`', name: '`column`' }
       return value:
         type: '`kb__key_t`'

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ **/

