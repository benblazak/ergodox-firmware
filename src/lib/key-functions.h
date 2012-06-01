/* ----------------------------------------------------------------------------
 * key functions: exports
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef KEY_FUNCTIONS_h
	#define KEY_FUNCTIONS_h

	#include "lib/data-types.h"

	typedef void (*kbfun_funptr_t)(
			uint8_t,   uint8_t *,
			uint8_t *, uint8_t * );

	void kbfun_press(
			uint8_t keycode, uint8_t * current_layer,
			uint8_t * row,   uint8_t * col );
	void kbfun_release(
			uint8_t keycode, uint8_t * current_layer,
			uint8_t * row,   uint8_t * col );

#endif

