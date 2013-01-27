/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Implements the "controller" section of '.../firmware/keyboard.h'
 */


#include <stdbool.h>
#include <stdint.h>
#include "../../../firmware/keyboard.h"
#include "./controller/mcp23018.h"
#include "./controller/teensy-2-0.h"

// ----------------------------------------------------------------------------

/**                                              functions/kb__init/description
 * Returns:
 * - success: `0`
 * - failure: the number of the function that failed
 */
uint8_t kb__init(void) {
    if (teensy__init())    // must be first (to initialize twi, and such)
        return 1;
    if (mcp23018__init())  // must be second
        return 2;

    return 0;  // success
}

/**                                     functions/kb__update_matrix/description
 * Returns:
 * - success: `0`
 * - failure: number of the function that failed
 */
uint8_t kb__update_matrix(bool matrix[KB__ROWS][KB__COLUMNS]) {
    if (teensy__update_matrix(matrix))
        return 1;
    if (mcp23018__update_matrix(matrix))
        return 2;

    return 0;  // success
}

