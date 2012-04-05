/* ----------------------------------------------------------------------------
 * ergoDOX layout specific exports
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

#ifndef LAYOUT_h
	#define LAYOUT_h

	#include "lib/data-types.h"

	#include "matrix.h"

	#define KB_LAYERS 1  // anything >= 1, as long as there's memory

	extern uint8_t const kb_layout[KB_LAYERS][KB_ROWS][KB_COLUMNS];

#endif

