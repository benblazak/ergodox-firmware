/* ----------------------------------------------------------------------------
 * ergoDOX : controller specific exports
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef KEYBOARD__ERGODOX__CONTROLLER_h
	#define KEYBOARD__ERGODOX__CONTROLLER_h

	#include <stdbool.h>
	#include <stdint.h>
	#include "./matrix.h"

	// --------------------------------------------------------------------

	#include "./controller/teensy-2-0--led.h"

	// --------------------------------------------------------------------

	uint8_t kb_init(void);
	uint8_t kb_update_matrix(bool matrix[KB_ROWS][KB_COLUMNS]);

#endif

