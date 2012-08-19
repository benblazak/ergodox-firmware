/* ----------------------------------------------------------------------------
 * ergoDOX : layout exports
 *
 * Different layouts are included by modifying a variable in the makefile.
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef KEYBOARD__ERGODOX__LAYOUT_h
	#define KEYBOARD__ERGODOX__LAYOUT_h

	// --------------------------------------------------------------------

	// include the appropriate keyboard layout header
	#include "../../lib/variable-include.h"
	#define INCLUDE EXP_STR( ./layout/MAKEFILE_KEYBOARD_LAYOUT.h )
	#include INCLUDE

#endif

