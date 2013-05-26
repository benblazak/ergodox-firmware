/* ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Some generally useful functions to aid in creating keys
 *
 * Prefix: `key_functions__`
 */


#ifndef ERGODOX_FIRMWARE__FIRMWARE__LIB__LAYOUT__KEY_FUNCTIONS__H
#define ERGODOX_FIRMWARE__FIRMWARE__LIB__LAYOUT__KEY_FUNCTIONS__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

#include <stddef.h>
#include <stdint.h>

// ----------------------------------------------------------------------------

// basic
void key_functions__press   (uint8_t keycode);
void key_functions__release (uint8_t keycode);
void key_functions__toggle  (uint8_t keycode);

// device
void key_functions__jump_to_bootloader (void);

// special
void key_functions__toggle_capslock       (void);
// --- TODO ---
void key_functions__send_unicode_sequence ( uint8_t          wrapper_length,
                                            const uint8_t *  wrapper,
                                            const wchar_t * string );


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__FIRMWARE__LIB__LAYOUT__KEY_FUNCTIONS__H



// ============================================================================
// === documentation ==========================================================
// ============================================================================

// ----------------------------------------------------------------------------
// functions ------------------------------------------------------------------
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// basic ----------------------------------------------------------------------

// === key_functions__press() ===
/**                                  functions/key_functions__press/description
 * Generate a normal keypress (and send the USB report).
 *
 * Arguments:
 * - `keycode`: The keycode to "press"
 */

// === key_functions__release() ===
/**                                functions/key_functions__release/description
 * Generate a normal keyrelease (and send the USB report).
 *
 * Arguments:
 * - `keycode`: The keycode to "release"
 */

// === key_functions__toggle() ===
/**                                 functions/key_functions__toggle/description
 * Toggle the key pressed or unpressed.
 *
 * Arguments:
 * - `keycode`: The keycode to "toggle"
 */

// ----------------------------------------------------------------------------
// device ---------------------------------------------------------------------

// === key_functions__jump_to_bootloader() ===
/**                     functions/key_functions__jump_to_bootloader/description
 * For reflashing the controller.
 */

// ----------------------------------------------------------------------------
// special --------------------------------------------------------------------

// === key_functions__toggle_capslock() ===
/**                        functions/key_functions__toggle_capslock/description
 * Toggle the state of 'capslock'
 *
 * Notes:
 * - This requires special handling because neither of the shift keys may be
 *   active when 'capslock' is pressed, or it will not register properly.  This
 *   function disables both shift keys, toggles 'capslock', and then restores
 *   the state of both shift keys.
 */

