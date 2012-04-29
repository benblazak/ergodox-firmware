/* ----------------------------------------------------------------------------
 * ergoDOX layout : QWERTY : exports
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include <avr/pgmspace.h>
#include "lib/data-types.h"
#include "lib/key-functions.h"  // for `kbfun_funptr_t`

#include "../matrix.h"  // for number of rows and columns


#define KB_LAYERS 1  // must match what's defined in the layout '.c' file


// override the defaults so we can use program space

extern uint8_t PROGMEM \
	       _kb_layout[KB_LAYERS][KB_ROWS][KB_COLUMNS];
#define kb_layout_get(layer,row,column) \
	( (uint8_t) (pgm_read_byte(&( \
		_kb_layout[layer][row][column] ))) )

extern kbfun_funptr_t PROGMEM \
	       _kb_layout_press[KB_LAYERS][KB_ROWS][KB_COLUMNS];
#define kb_layout_press_get(layer,row,column) \
	( (kbfun_funptr_t) (pgm_read_word(&( \
		_kb_layout_press[layer][row][column] ))) )

extern kbfun_funptr_t PROGMEM \
	       _kb_layout_release[KB_LAYERS][KB_ROWS][KB_COLUMNS];
#define kb_layout_release_get(layer,row,column) \
	( (kbfun_funptr_t) (pgm_read_word(&( \
		_kb_layout_release[layer][row][column] ))) )

