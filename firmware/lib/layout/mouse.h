/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Gyuri Horak <dyuri@horak.hu>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/dyuri/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**
 * Mouse related key functions
 *
 * Prefix: `key_functions__`
 */


#ifndef ERGODOX_FIRMWARE__FIRMWARE__LIB__LAYOUT__MOUSE__H
#define ERGODOX_FIRMWARE__FIRMWARE__LIB__LAYOUT__MOUSE__H
// ----------------------------------------------------------------------------

#include <stdint.h>

void key_functions__mouse_left_click (void);
void key_functions__mouse_buttons(uint8_t left, uint8_t middle, uint8_t right);

// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__FIRMWARE__LIB__LAYOUT__MOUSE__H
