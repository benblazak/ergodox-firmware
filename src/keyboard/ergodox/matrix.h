/* ----------------------------------------------------------------------------
 * ergoDOX: keyboard matrix specific exports
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef MATRIX_h
	#define MATRIX_h

	#include "lib/data-types.h"

	#define KB_ROWS    12  // must match real life
	#define KB_COLUMNS  7  // must match real life

	extern bool kb_is_pressed[KB_ROWS][KB_COLUMNS] = {};

#endif

