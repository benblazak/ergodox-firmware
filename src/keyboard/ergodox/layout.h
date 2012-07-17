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

	#include <avr/pgmspace.h>
	#include "lib/data-types/common.h"
	#include "lib/key-functions.h"  // for `kbfun_funptr_t`

	#include "matrix.h"  // for number of rows and columns

	// include the appropriate keyboard layout header
	// for:
	// - possible non-default number of layers
	// - possible non-default layout matrix definitions
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


	// default number of layers
	#ifndef KB_LAYERS
		#define KB_LAYERS 10
	#endif


	// default layout 'get' macros and `extern` matrix declarations
	//
	// these are for when the matrices are stored solely in Flash.  layouts
	// may redefine them if they wish and use RAM, EEPROM, or any
	// combination of the three, as long as they maintain the same
	// interface.
	//
	// - if the macro is overridden, the matrix declaration must be too,
	//   and vice versa.
	//
	// - 'set' functions are optional, and should be defined in the layout
	//   specific '.h'.  they'll require the use of the EEPROM, possibly in
	//   clever conjunction with one of the other two memories (since the
	//   EEPROM is small).  custom key functions will also need to be
	//   written.
	//
	// - to override these macros with real functions, set the macro equal
	//   to itself (e.g. `#define kb_layout_get kb_layout_get`) and provide
	//   function prototypes in the layout specific '.h'

	#ifndef kb_layout_get
		extern uint8_t PROGMEM \
			       _kb_layout[KB_LAYERS][KB_ROWS][KB_COLUMNS];

		#define kb_layout_get(layer,row,column) \
			( (uint8_t) \
			  pgm_read_byte(&( \
				_kb_layout[layer][row][column] )) )
	#endif

	#ifndef kb_layout_press_get
		extern kbfun_funptr_t PROGMEM \
			_kb_layout_press[KB_LAYERS][KB_ROWS][KB_COLUMNS];

		#define kb_layout_press_get(layer,row,column) \
			( (kbfun_funptr_t) \
			  pgm_read_word(&( \
				_kb_layout_press[layer][row][column] )) )
	#endif

	#ifndef kb_layout_release_get
		extern kbfun_funptr_t PROGMEM \
			_kb_layout_release[KB_LAYERS][KB_ROWS][KB_COLUMNS];

		#define kb_layout_release_get(layer,row,column) \
			( (kbfun_funptr_t) \
			  pgm_read_word(&( \
				_kb_layout_release[layer][row][column] )) )

	#endif


	// default logical LED macros (all defined to nothing)
	#ifndef kb_led_num_on
		#define kb_led_num_on()
	#endif
	#ifndef kb_led_num_off
		#define kb_led_num_off()
	#endif
	#ifndef kb_led_caps_on
		#define kb_led_caps_on()
	#endif
	#ifndef kb_led_caps_off
		#define kb_led_caps_off()
	#endif
	#ifndef kb_led_scroll_on
		#define kb_led_scroll_on()
	#endif
	#ifndef kb_led_scroll_off
		#define kb_led_scroll_off()
	#endif
	#ifndef kb_led_compose_on
		#define kb_led_compose_on()
	#endif
	#ifndef kb_led_compose_off
		#define kb_led_compose_off()
	#endif
	#ifndef kb_led_kana_on
		#define kb_led_kana_on()
	#endif
	#ifndef kb_led_kana_off
		#define kb_led_kana_off()
	#endif

#endif

