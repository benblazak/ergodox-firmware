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
void key_functions__dump_sram_ihex     (void * from, void * last);
void key_functions__dump_progmem_ihex  (void * from, void * last);
void key_functions__dump_eeprom_ihex   (void * from, void * last);

// special
void key_functions__toggle_capslock (void);
void key_functions__type_byte_hex   (uint8_t byte);
void key_functions__type_string     (const char * string);


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

// === (group) dump...ihex() ===
/**                                   functions/(group) dump...ihex/description
 * Type, in ihex format, the specified data from the appropriate memory space.
 *
 * Members:
 * - `key_functions__dump_sram_ihex`: Types data from the SRAM
 * - `key_functions__dump_progmem_ihex`: Types data from the PROGMEM
 * - `key_functions__dump_eeprom_ihex`: Types data from the EEPROM
 *
 * Arguments:
 * - `from`: A pointer to the location from which to start reading
 * - `last`: A pointer to the last location from which to read
 *
 * Usage notes:
 * - To print the entire contents of, e.g., SRAM, write
 *
 *       key_functions__dump_sram_ihex( (void *)0, (void *)-1 );
 *
 *   See "Implementation notes" below.
 *
 * Warnings:
 * - These functions may take a long time to complete, and there is no way to
 *   stop them aside from resetting the controller.
 * - It may occur to you that one could read out the contents of PROGMEM using
 *   the appropriate function, and then use the resulting ihex file to reflash
 *   a Teensy.  I would *not* recommend doing this however, unless you really
 *   know what you're doing, or you're prepared for the chance that you might
 *   mess something up.
 *
 * Implementation notes:
 * - If `last` is greater than the maximum addressable location of the
 *   appropriate memory space, `last` should be set to the maximum addressable
 *   location.  This will allow users to use `(void *)-1` (or `(void
 *   *)UINT16_MAX`) as the `last` location when they wish to read until the end
 *   of addressable memory.
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

// === key_functions__type_string() ===
/**                            functions/key_functions__type_string/description
 * Type the keycode (or "unicode sequence") for each character in `string`
 *
 * Arguments:
 * - `string`: A pointer to a valid UTF-8 string in PROGMEM
 *
 *
 * Notes:
 *
 * - A "unicode sequence" is holding down "alt", typing "+", typing the 4
 *   character hexadecimal unicode code for the specified character, then
 *   releasing "alt".  This is done for every character in `string` for which a
 *   dedicated USB keycode has not been specified.
 *
 * - This function is, relative to the rest of life, extremely unportable.
 *   Sorry about that: I looked for a better way to do things, but I couldn't
 *   find one.  It may be very convenient under certain circumstances though,
 *   if one is willing to take a little time to understand what it's actually
 *   doing, so I'm including it in the hope that it will be.  Please see the
 *   implementation (in the '.c' file) for which keycodes are being sent for a
 *   given character.
 *
 *
 * Operating system considerations (for typing "unicode sequences"):
 *
 * - "Unicode sequences", as implemented, should work on OS X and Windows
 *   (after enabling "hexidecimal code input" in the OS), but probably will not
 *   work on Linux (2 out of 3 of the major OSs is better than nothing...).  If
 *   you're using Linux and you want to flip that around :) please modify the
 *   function to send Linux friendly start and end sequences.  See [this
 *   Wikipedia article]
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
 * - Characters (and strings) sent with this function do not automatically
 *   repeat (as normal keys do).
 *
 * - Please pay very special attention to what this function is actually typing
 *   if you are using any language besides English as the default in your OS,
 *   or if you have characters that aren't 7-bit ASCII in your string and have
 *   not enabled "hexidecimal code input" in your OS.
 *
 * - This function does not disable modifier keys, or any other keys, on entry:
 *   keys are pressed and released as they would be if one was typing them
 *   starting with no keys pressed.  If you are holding down any keys when this
 *   function is called, it *may* not do what you expect, depending on which
 *   keys are being held down and which keys this function is trying to press
 *   and release.
 *
 * - An easy way to pass a PROGMEM string to this function is to use the
 *   `PSTR()` macro in `<avr/pgmspace.h>`, as in
 *
 *       key_functions__type_string( PSTR( "❄" ) );
 *
 *   or
 *
 *       key_functions__type_string( PSTR(
 *               "こんにちは世界 γειά σου κόσμε hello world ^_^" ) );
 */

