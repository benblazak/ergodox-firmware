/* ----------------------------------------------------------------------------
 * key functions: private
 *
 * Things to be used only by keyfunctions.  Exported any layouts would like to
 * use these functions to help define their own.
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef KEY_FUNCTIONS_h_PRIVATE
	#define KEY_FUNCTIONS_h_PRIVATE

	void _press_release(bool pressed, uint8_t keycode);
	void _layer_set_current(
			uint8_t value,
			uint8_t * current_layer,
			uint8_t (*current_layers_)[KB_ROWS][KB_COLUMNS] );
	bool _is_pressed(uint8_t keycode);

#endif

