/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**
 * - description: |
 *   A place for all things common to the other default files, including
 *   `#include`s.  Other code (especially functions defined in this directory)
 *   may break if you change things defined here, so be careful if you do.
 */


#ifndef ERGODOX_FIRMWARE__KEYBOARD__ERGODOX__LAYOUT__DEFAULT__COMMON_H
#define ERGODOX_FIRMWARE__KEYBOARD__ERGODOX__LAYOUT__DEFAULT__COMMON_H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include "../../../../../firmware/keyboard.h"
#include "../../../../../firmware/lib/layout/key-functions.h"
#include "../../../../../firmware/lib/usb/usage-page/keyboard.h"

// ----------------------------------------------------------------------------

typedef  const kb__key_t * const PROGMEM  key_t


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__KEYBOARD__ERGODOX__LAYOUT__DEFAULT__COMMON_H

