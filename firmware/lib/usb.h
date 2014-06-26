/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * The USB interface
 *
 * Prefixes: `usb__` `usb__kb__`
 */


#ifndef ERGODOX_FIRMWARE__FIRMWARE__LIB__USB__H
#define ERGODOX_FIRMWARE__FIRMWARE__LIB__USB__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


#include <stdbool.h>
#include <stdint.h>

// ----------------------------------------------------------------------------

// --- general ---

uint8_t usb__init          (void);
bool    usb__is_configured (void);

// --- keyboard ---

uint8_t usb__kb__set_key     (bool pressed, uint8_t keycode);
bool    usb__kb__read_key    (uint8_t keycode);
bool    usb__kb__read_led    (char led);
uint8_t usb__kb__send_report (void);


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__FIRMWARE__LIB__USB__H



// ============================================================================
// === documentation ==========================================================
// ============================================================================


// ----------------------------------------------------------------------------
// general --------------------------------------------------------------------

// === usb__init() ===
/**                                             functions/usb__init/description
 * Initialize USB for this device
 *
 * Returns:
 * - success: `0`
 * - failure: [other]
 *
 * Notes:
 * - Should be called exactly once by `main()`, and nothing else USB related
 *   should be done until `usb__configured` is `true`
 */

// === usb__is_configured ===
/**                                    functions/usb__is_configured/description
 * Check whether this device has been configured by the host
 *
 * Returns:
 * - `true`: if the device has been configured
 * - `false`: if the device has not been configured
 *
 * Notes:
 * - Should return `true` before calling any function other than `usb__init()`
 */


// ----------------------------------------------------------------------------
// keyboard -------------------------------------------------------------------

// === usb__kb__set_key() ===
/**                                      functions/usb__kb__set_key/description
 * Set the given keycode as 'pressed' ('on') or 'released' ('off') (device
 * side)
 *
 * Arguments:
 * - `pressed`: whether to set the keycode 'on' (`true`) or 'off' (`false`)
 * - `keycode`: the keycode to set
 *
 * Returns:
 * - success: `0`
 * - failure: status code (unspecified, nonzero)
 *
 * Notes:
 * - Setting a keycode 'on' or 'off' does not send the report, and the host
 *   will not know the state of the keycode until the report is sent.  If a key
 *   is set 'on' then 'off' without sending the report in between, the host
 *   will know nothing about it.
 */

// === usb__kb__read_key() ===
/**                                     functions/usb__kb__read_key/description
 * Check whether the given keycode is set to 'on' (device side)
 *
 * Arguments:
 * - `keycode`: the keycode to check
 *
 * Returns:
 * - `false`: if the state of the given keycode is set to 'off'
 * - `true`: if the state of the given keycode is set to 'on'
 *
 * Notes:
 * - The fact that a given keycode is set to some value here does not mean that
 *   the host knows about it.  The host will only know the current state of the
 *   keycodes if the report has been sent since the last change.
 */

// === usb__kb__read_led() ===
/**                                     functions/usb__kb__read_led/description
 * Check whether the given (logical) LED is set to 'on' (host side)
 *
 * Arguments:
 * - `led`:
 *     - `N`: numlock
 *     - `C`: capslock
 *     - `S`: scroll lock
 *     - `O`: compose
 *     - `K`: kana
 *
 * Returns:
 * - `false`: if the state of the given (logical) LED is set to 'off'
 * - `true`: if the state of the given (logical) LED is set to 'on'
 *
 * Notes:
 * - No data is actually exchanged with the host by this function, but
 *   maintaining the state of these (logical) LEDs (and informing the device
 *   when they change) is the host's responsibility.  The device only keeps
 *   track of what the host tells it.
 */

// === usb__kb__send_report() ===
/**                                  functions/usb__kb__send_report/description
 * Send the USB report to the host (update the host on the state of the
 * keycodes)
 *
 * Returns:
 * - success: `0`
 * - failure: status code (unspecified, nonzero)
 */

