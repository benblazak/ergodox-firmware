/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * A place for all things common to the other default files, including
 * `#include`s.
 */


#ifndef ERGODOX_FIRMWARE__KEYBOARD__ERGODOX__LAYOUT__DEFAULT__COMMON__H
#define ERGODOX_FIRMWARE__KEYBOARD__ERGODOX__LAYOUT__DEFAULT__COMMON__H
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
#include "../../../../../firmware/lib/usb.h"

// ----------------------------------------------------------------------------

typedef struct {
    kf__function_pointer_t  press_function;
    uint16_t                press_value;
    kf__function_pointer_t  release_function;
    uint16_t                release_value;
} key_t;

#define  KEY_T  const key_t * const PROGMEM


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__KEYBOARD__ERGODOX__LAYOUT__DEFAULT__COMMON__H

