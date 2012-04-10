/* ----------------------------------------------------------------------------
 * ergoDOX specific code: tying it all together
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include "lib/data-types.h"

#define KEYBOARD_INCLUDE_PRIVATE
#include "ergodox/matrix.h"
#include "ergodox/mcp23018.h"
#include "ergodox/teensy-2-0.h"


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
	if (teensy_update_matrix(matrix))    // must be first
		return 1;
	if (mcp23018_update_matrix(matrix))  // must be second
		return 2;

	return 0;  // success
}

