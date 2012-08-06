/* ----------------------------------------------------------------------------
 * key functions : basic : code
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include "../../../main.h"
#include "../../../keyboard/layout.h"
#include "../public.h"
#include "../private.h"

// ----------------------------------------------------------------------------

// convenience macros
#define  layer        main_arg_layer
#define  row          main_arg_row
#define  col          main_arg_col
#define  is_pressed   main_arg_is_pressed
#define  was_pressed  main_arg_was_pressed

// ----------------------------------------------------------------------------

/*
 * Press|Release
 * - Generate a normal keypress or keyrelease
 */
void kbfun_press_release(void) {
	uint8_t keycode = kb_layout_get(layer, row, col);
	_kbfun_press_release(is_pressed, keycode);
}

/*
 * Toggle
 * - Toggle the key pressed or unpressed
 */
void kbfun_toggle(void) {
	uint8_t keycode = kb_layout_get(layer, row, col);

	if (_kbfun_is_pressed(keycode))
		_kbfun_press_release(false, keycode);
	else
		_kbfun_press_release(true, keycode);
}

/*
 * Increase layer
 * - Increment the current layer by the value specified in the keymap (for all
 *   non-masked keys)
 */
void kbfun_layer_inc(void) {
	uint8_t keycode = kb_layout_get(layer, row, col);
	_kbfun_layer_set_current(main_layers_current + keycode);
}

/*
 * Decrease layer
 * - Decrement the current layer by the value specified in the keymap (for all
 *   non-masked keys)
 */
void kbfun_layer_dec(void) {
	uint8_t keycode = kb_layout_get(layer, row, col);
	_kbfun_layer_set_current(main_layers_current - keycode);
}

