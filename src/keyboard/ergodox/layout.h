/* ----------------------------------------------------------------------------
 * ergoDOX layout specific exports
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

#ifndef LAYOUT_h
	#define LAYOUT_h

	#include "lib/_data-types.h"

	#include "key-functions.h"

	#include "matrix.h"

	#define KB_LAYERS 1  // must match what's defined in "layout.c"

	extern uint8_t
			kb_layout        [KB_LAYERS][KB_ROWS][KB_COLUMNS];
	extern kbfun_funptr_t
			kb_layout_press  [KB_LAYERS][KB_ROWS][KB_COLUMNS];
	extern kbfun_funptr_t
			kb_layout_release[KB_LAYERS][KB_ROWS][KB_COLUMNS];

#endif

