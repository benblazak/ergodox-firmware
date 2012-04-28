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
	#include "lib/_key-functions.h"  // for `kbfun_funptr_t`

	#include "matrix.h"  // for number of rows and columns

	// include the appropriate keyboard layout header;
	// for number of layers
	#undef _str
	#undef _expstr
	#undef _inc
	#define _str(s) #s          // stringify
	#define _expstr(s) _str(s)  // expand -> stringify
	#define _inc _expstr(layout/MAKEFILE_KEYBOARD_LAYOUT.h)  // inc(lude)
	#include _inc
	#undef _str
	#undef _expstr
	#undef _inc

	extern uint8_t
			kb_layout        [KB_LAYERS][KB_ROWS][KB_COLUMNS];
	extern kbfun_funptr_t
			kb_layout_press  [KB_LAYERS][KB_ROWS][KB_COLUMNS];
	extern kbfun_funptr_t
			kb_layout_release[KB_LAYERS][KB_ROWS][KB_COLUMNS];

#endif

