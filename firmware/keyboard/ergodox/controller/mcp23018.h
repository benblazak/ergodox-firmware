/* ----------------------------------------------------------------------------
 * Copyright (c) 2012, 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * For inclusion by '../controller.c'
 */


#ifndef ERGODOX_FIRMWARE__FIRMWARE__KEYBOARD__ERGODOX__CONTROLLER__MCP23018__H
#define ERGODOX_FIRMWARE__FIRMWARE__KEYBOARD__ERGODOX__CONTROLLER__MCP23018__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


#include <stdbool.h>
#include <stdint.h>
#include "../../../../firmware/keyboard.h"

// ----------------------------------------------------------------------------

uint8_t mcp23018__init          (void);
uint8_t mcp23018__update_matrix (bool matrix[OPT__KB__ROWS][OPT__KB__COLUMNS]);


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__FIRMWARE__KEYBOARD__ERGODOX__CONTROLLER__MCP23018__H

