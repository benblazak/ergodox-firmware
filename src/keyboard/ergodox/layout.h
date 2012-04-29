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

	#include "lib/data-types.h"
	#include "lib/key-functions.h"  // for `kbfun_funptr_t`

	#include "matrix.h"  // for number of rows and columns

	// include the appropriate keyboard layout header
	// for:
	// - number of layers
	// - layout matrix definitions
	// - possible non-default layout 'get' and 'set' definitions
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


	// default layout 'get' functions
	//
	// these are for when the matrices are stored solely in RAM.  they're
	// here so layouts can redefine them if they with and use RAM, Flash,
	// EEPROM, or any combination of those, while maintaining the same
	// interface
	//
	// - 'set' functions are optional, and should be defined in the layout
	//   specific '.h'.  they'll require the use of the EEPROM, possibly in
	//   clever conjunction with one of the other two memories (since the
	//   EEPROM is small)
	//
	// - to override these with real functions, set the macro equal to
	//   itself (e.g. `#define kb_layout_get kb_layout_get`) and provide
	//   function prototypes in the layout specific '.h'

	#ifndef kb_layout_get
		#define kb_layout_get(layer,row,column) \
			(_kb_layout[layer][row][column])
	#endif

	#ifndef kb_layout_press_get
		#define kb_layout_press_get(layer,row,column) \
			(_kb_layout_press[layer][row][column])
	#endif

	#ifndef kb_layout_release_get
		#define kb_layout_release_get(layer,row,column) \
			(_kb_layout_release[layer][row][column])
	#endif

#endif

