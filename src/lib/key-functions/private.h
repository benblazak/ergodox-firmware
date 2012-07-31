/* ----------------------------------------------------------------------------
 * key functions : private : exports
 *
 * Things to be used only by keyfunctions.  Exported so layouts can use these
 * functions to help define their own, if they like.
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef LIB__KEY_FUNCTIONS__INTERNAL_h
	#define LIB__KEY_FUNCTIONS__INTERNAL_h

	#include "./public.h"

	// --------------------------------------------------------------------

	void _kbfun_press_release(bool pressed, uint8_t keycode);
	void _kbfun_layer_set_current(
			uint8_t value,
			uint8_t * current_layer,
			uint8_t (*current_layers_)[KB_ROWS][KB_COLUMNS] );
	void _kbfun_layer_set_mask(
			uint8_t layer,
			bool positions[KB_ROWS][KB_COLUMNS],
			uint8_t (*current_layers)[KB_ROWS][KB_COLUMNS] );
	bool _kbfun_is_pressed(uint8_t keycode);

#endif

