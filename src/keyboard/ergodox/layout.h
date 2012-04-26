/* ----------------------------------------------------------------------------
 * ergoDOX layout : exports
 *
 * Different layouts are included by modifying a variable in the makefile.
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

#ifndef LAYOUT_h
	#define LAYOUT_h

	#include "lib/_data-types.h"

	#include "key-functions.h"  // for `kbfun_funptr_t`

	#include "matrix.h"  // for number of rows and columns

	#include KEYBOARD_LAYOUT  // for number of layers

	extern uint8_t
			kb_layout        [KB_LAYERS][KB_ROWS][KB_COLUMNS];
	extern kbfun_funptr_t
			kb_layout_press  [KB_LAYERS][KB_ROWS][KB_COLUMNS];
	extern kbfun_funptr_t
			kb_layout_release[KB_LAYERS][KB_ROWS][KB_COLUMNS];

#endif

