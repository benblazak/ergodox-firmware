/* ----------------------------------------------------------------------------
 * ergoDOX specific exports
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef ERGODOX_h
	#define ERGODOX_h

	#include "lib/data-types.h"

	#include "ergodox/layout.h"      // number of layers, layout
	#include "ergodox/matrix.h"      // kb dimensions, matrix status
	#include "ergodox/mcp23018.h"    // (nothing right now)
	#include "ergodox/teensy-2-0.h"  // LED controls

	uint8_t kb_init(void);
	uint8_t kb_update_matrix(bool matrix[KB_ROWS][KB_COLUMNS]);

#endif

