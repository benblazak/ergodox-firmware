/* ----------------------------------------------------------------------------
 * Copyright (c) 2012, 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * The TWI (aka I&sup2;C) interface
 *
 * Prefix: `twi__`
 *
 * Functions are named after the basic TWI actions; see general documentation
 * on TWI for more information.
 */


#ifndef ERGODOX_FIRMWARE__FIRMWARE__LIB__TWI__H
#define ERGODOX_FIRMWARE__FIRMWARE__LIB__TWI__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


#include <stdint.h>

// ----------------------------------------------------------------------------

#ifndef OPT__TWI__FREQUENCY
    #error "OPT__TWI__FREQUENCY not defined"
#endif

// ----------------------------------------------------------------------------

void    twi__init  (void);
uint8_t twi__start (void);
void    twi__stop  (void);
uint8_t twi__send  (uint8_t data);
uint8_t twi__read  (uint8_t * data);


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__FIRMWARE__LIB__TWI__H



// ============================================================================
// === documentation ==========================================================
// ============================================================================


// ----------------------------------------------------------------------------
// macros ---------------------------------------------------------------------
// ----------------------------------------------------------------------------

// === OPT__TWI__FREQUENCY ===
/**                                      macros/OPT__TWI__FREQUENCY/description
 * The TWI Frequency, in Hz.
 */


// ----------------------------------------------------------------------------
// functions ------------------------------------------------------------------
// ----------------------------------------------------------------------------

// === twi__init() ===
/**                                             functions/twi__init/description
 * Initialize TWI
 *
 * Notes:
 * - Should be called exactly once during keyboard startup
 */

// === twi__start() ===
/**                                            functions/twi__start/description
 * Send a TWI Start signal
 *
 * Returns:
 * - success: `0`
 * - failure: The TWI status code
 */

// === twi__stop() ===
/**                                             functions/twi__stop/description
 * Send a TWI Stop signal
 */

// === twi__send() ===
/**                                             functions/twi__send/description
 * Send `data` (which may actually be an instruction or a device or register
 * address) over the bus
 *
 * Arguments:
 * - `data`: The data to send
 *
 * Returns:
 * - success: `0`
 * - failure: The TWI status code
 */

// === twi__read() ===
/**                                             functions/twi__read/description
 * Read incoming data
 *
 * Arguments:
 * - `data`: A pointer to the location to read data to
 *
 * Returns:
 * - success: `0`
 * - failure: The TWI status code
 */

