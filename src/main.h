/* ----------------------------------------------------------------------------
 * main() : functions and data that may be useful externally
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef MAIN_h
	#define MAIN_h

	#include <stdbool.h>
	#include <stdint.h>
	#include "./keyboard/matrix.h"

	// --------------------------------------------------------------------

	extern bool (*main_kb_is_pressed)[KB_ROWS][KB_COLUMNS];
	extern bool (*main_kb_was_pressed)[KB_ROWS][KB_COLUMNS];

	extern uint8_t main_layers_pressed[KB_ROWS][KB_COLUMNS];

	extern uint8_t main_loop_row;
	extern uint8_t main_loop_col;

	extern uint8_t main_arg_layer;
	extern uint8_t main_arg_layer_offset;
	extern uint8_t main_arg_row;
	extern uint8_t main_arg_col;
	extern bool    main_arg_is_pressed;
	extern bool    main_arg_was_pressed;

	// --------------------------------------------------------------------

	void main_exec_key (void);

	uint8_t main_layers_peek          (uint8_t offset);
	uint8_t main_layers_push          (uint8_t layer);
	void    main_layers_pop_id        (uint8_t id);
	uint8_t main_layers_get_offset_id (uint8_t id);


#endif

