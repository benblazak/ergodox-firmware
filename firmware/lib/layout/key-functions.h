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
void key_functions__type_byte_hex         (uint8_t byte);
void key_functions__send_unicode_sequence (const char * string);


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

// === key_functions__type_byte_hex() ===
/**                          functions/key_functions__type_byte_hex/description
 * Send the characters (2 of `[0-9A-F]`) corresponding to `byte` in base 16
 *
 * Arguments:
 * - `byte`: The byte to send a representation of
 */

// === key_functions__send_unicode_sequence() ===
/**                  functions/key_functions__send_unicode_sequence/description
 * Send the "unicode sequence" for each character in `string`
 *
 * This function is, relative to the rest of life, extremely unportable. Sorry
 * about that: I looked, but I couldn't find a better way to do it.  I'm
 * including it in the hope that it will be useful anyway.
 *
 * Arguments:
 * - `string`: A pointer to a valid UTF-8 string in PROGMEM
 *
 *
 * Operating system considerations:
 *
 * - This function should work on OS X and Windows (after enabling "hexidecimal
 *   code input" in the OS), but probably will not work on Linux (2 out of 3 of
 *   the major OSs is better than nothing...).  If you're using Linux and you
 *   want to flip that around :) please modify the function to send Linux
 *   friendly start and end sequences.  See [this Wikipedia article]
 *   (http://en.wikipedia.org/wiki/Unicode_input#Hexadecimal_code_input) for
 *   more information.
 *
 * - On Windows (per the Wikipedia article above): Make sure the registry key
 *   `HKEY_CURRENT_USER\Control Panel\Input Method\EnableHexNumpad` has a
 *   string value of `1`.  If it does not, fix it, then reboot (or log off/on,
 *   in Windows 7+)
 *
 * - On OS X: open "System Preferences", navigate to "Language & Text", select
 *   the "Input Sources" tab (if it isn't selected already), and check the box
 *   next to "Unicode Hex Input".  Make sure this input method is active
 *   whenever you use this function.
 *     - I recommend disabling the default (in the US at least) "U.S." input
 *       method, and just leaving this one active all the time.  Note though
 *       that this will render all the normal "Alt" special characters
 *       unavailable.
 *
 *
 * Usage notes:
 *
 * - This function disables all modifier keys on entry, and restores their
 *   state on exit.
 *
 * - A "unicode sequence" is holding down "alt", typing "+", typing the 4
 *   character unicode code for the specified character, then releasing "alt".
 *   This is done for every character in `string`, even the ones with a
 *   dedicated USB keycode.
 *
 * - Characters (and strings) sent with this function do not automatically
 *   repeat (as normal keys do).
 *
 * - If you're holding down any of `[0-9A-F]` when this function is called, it
 *   may not do what you want.
 *
 * - An easy way to pass a PROGMEM string to this function is to use the
 *   `PSTR()` macro in `<avr/pgmspace.h>`, as in
 *
 *       key_functions__send_unicode_sequence( PSTR ( "❄" ) );
 *
 *   or
 *
 *       key_functions__send_unicode_sequence( PSTR (
 *               "こんにちは世界 γειά σου κόσμε hello world ^_^" ) );
 *
 * - It's probably better to define a proper macro key than to use this
 *   function for sending sequences of "normal" characters, despite the
 *   relative inconvenience.  But... if you're not concerned about portability,
 *   or other factors that might arise because of what this function is
 *   *actually* typing... it's possible to do it this way to... :) lol
 */

