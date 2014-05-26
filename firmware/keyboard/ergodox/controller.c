/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Implements the "controller" section of '.../firmware/keyboard.h'
 */

#include <stdbool.h>
#include <stdint.h>
#include "./controller/mcp23018.h"
#include "./controller/teensy-2-0.h"
#include "../../../firmware/lib/layout/eeprom-macro.h"
#include "../../../firmware/keyboard.h"

// ----------------------------------------------------------------------------

uint8_t kb__init(void) {
    if (teensy__init())    // must be first (to initialize twi, and such)
        return 1;
    if (mcp23018__init())  // must be second
        return 2;

    if (eeprom_macro__init())
        return 3;

    return 0;  // success
}

uint8_t kb__update_matrix(bool matrix[OPT__KB__ROWS][OPT__KB__COLUMNS]) {
    if (teensy__update_matrix(matrix))
        return 1;
    if (mcp23018__update_matrix(matrix))
        return 2;

    return 0;  // success
}

