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

void    twi__init  (void);
uint8_t twi__start (void);
void    twi__stop  (void);
uint8_t twi__send  (uint8_t data);
uint8_t twi__read  (uint8_t * data);


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__FIRMWARE__LIB__TWI__H

