/* ----------------------------------------------------------------------------
 * ergoDOX : controller specific code
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include <stdbool.h>
#include <stdint.h>
#include "./matrix.h"
#include "./controller/mcp23018--functions.h"
#include "./controller/teensy-2-0--functions.h"

// ----------------------------------------------------------------------------

/* returns
 * - success: 0
 * - error: number of the function that failed
 */
uint8_t kb_init(void) {
	if (teensy_init())    // must be first
		return 1;
	if (mcp23018_init())  // must be second
		return 2;

	return 0;  // success
}

/* returns
 * - success: 0
 * - error: number of the function that failed
 */
uint8_t kb_update_matrix(bool matrix[KB_ROWS][KB_COLUMNS]) {
	if (teensy_update_matrix(matrix))
		return 1;
	if (mcp23018_update_matrix(matrix))
		return 2;

	return 0;  // success
}

