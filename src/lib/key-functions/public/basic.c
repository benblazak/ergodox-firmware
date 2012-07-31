/* ----------------------------------------------------------------------------
 * key functions : basic : code
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include "../public.h"
#include "../private.h"

// ----------------------------------------------------------------------------

/*
 * Press|Release
 * - Generate a normal keypress or keyrelease
 */
void kbfun_press_release( KBFUN_FUNCTION_ARGS ) {
	_kbfun_press_release(pressed_, keycode_);
}

/*
 * Toggle
 * - Toggle the key pressed or unpressed
 */
void kbfun_toggle( KBFUN_FUNCTION_ARGS ) {
	if (_kbfun_is_pressed(keycode_))
		_kbfun_press_release(false, keycode_);
	else
		_kbfun_press_release(true, keycode_);
}

/*
 * Increase layer
 * - Increment the current layer by the value specified in the keymap (for all
 *   non-masked keys)
 */
void kbfun_layer_inc( KBFUN_FUNCTION_ARGS ) {
	_kbfun_layer_set_current(
			(*current_layer_) + keycode_,
			current_layer_,
			current_layers_ );
}

/*
 * Decrease layer
 * - Decrement the current layer by the value specified in the keymap (for all
 *   non-masked keys)
 */
void kbfun_layer_dec( KBFUN_FUNCTION_ARGS ) {
	_kbfun_layer_set_current(
			(*current_layer_) - keycode_,
			current_layer_,
			current_layers_ );
}

