/* ----------------------------------------------------------------------------
 * ergoDOX : layout : default matrix control
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef KEYBOARD__ERGODOX__LAYOUT__DEFAULT__MATRIX_CONTROL_h
	#define KEYBOARD__ERGODOX__LAYOUT__DEFAULT__MATRIX_CONTROL_h

	#include <stdint.h>
	#include <avr/pgmspace.h>
	#include "../../../lib/data-types/misc.h"
	#include "../../../lib/key-functions/public.h"
	#include "../matrix.h"

	// --------------------------------------------------------------------

	#ifndef KB_LAYERS
		#define KB_LAYERS 10
	#endif

	// --------------------------------------------------------------------

	/*
	 * matrix 'get' macros, and `extern` matrix declarations
	 *
	 * These are written for when the matrices are stored solely in Flash.
	 * Layouts may redefine them if they wish and use Flash, RAM, EEPROM,
	 * or any combination of the three, as long as they maintain the same
	 * interface.
	 *
	 * - If the macro is overridden, the matrix declaration must be too,
	 *   and vice versa.
	 *
	 * - 'set' functions are optional, and should be defined in the layout
	 *   specific '.h'.  They'll require the use of the EEPROM, possibly in
	 *   clever conjunction with one of the other two memories (since the
	 *   EEPROM is small).  Custom key functions will also need to be
	 *   written.
	 *
	 * - To override these macros with real functions, set the macro equal
	 *   to itself (e.g. `#define kb_layout_get kb_layout_get`) and provide
	 *   function prototypes, in the layout specific '.h'
	 */

	#ifndef kb_layout_get
		extern const uint8_t PROGMEM \
			       _kb_layout[KB_LAYERS][KB_ROWS][KB_COLUMNS];

		#define kb_layout_get(layer,row,column) \
			( (uint8_t) \
			  pgm_read_byte(&( \
				_kb_layout[layer][row][column] )) )
	#endif

	#ifndef kb_layout_press_get
		extern const void_funptr_t PROGMEM \
			_kb_layout_press[KB_LAYERS][KB_ROWS][KB_COLUMNS];

		#define kb_layout_press_get(layer,row,column) \
			( (void_funptr_t) \
			  pgm_read_word(&( \
				_kb_layout_press[layer][row][column] )) )
	#endif

	#ifndef kb_layout_release_get
		extern const void_funptr_t PROGMEM \
			_kb_layout_release[KB_LAYERS][KB_ROWS][KB_COLUMNS];

		#define kb_layout_release_get(layer,row,column) \
			( (void_funptr_t) \
			  pgm_read_word(&( \
				_kb_layout_release[layer][row][column] )) )

	#endif

#endif

