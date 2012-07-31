/* ----------------------------------------------------------------------------
 * key functions : public exports
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef LIB__KEY_FUNCTIONS__COMMON_h
	#define LIB__KEY_FUNCTIONS__COMMON_h

	#include <stdbool.h>
	#include <stdint.h>
	#include "src/keyboard/matrix.h"

	// --------------------------------------------------------------------

	#define KBFUN_FUNCTION_ARGS					\
		bool pressed_,						\
		uint8_t keycode_,					\
		uint8_t layer_,						\
		uint8_t * row_,						\
		uint8_t * col_,						\
		uint8_t * current_layer_,				\
		uint8_t (*current_layers_)[KB_ROWS][KB_COLUMNS],	\
		uint8_t (*pressed_layers_)[KB_ROWS][KB_COLUMNS]

	// --------------------------------------------------------------------

	typedef void (*kbfun_funptr_t)( KBFUN_FUNCTION_ARGS );

	// --------------------------------------------------------------------

	// basic
	void kbfun_press_release	( KBFUN_FUNCTION_ARGS );
	void kbfun_toggle		( KBFUN_FUNCTION_ARGS );
	void kbfun_layer_inc		( KBFUN_FUNCTION_ARGS );
	void kbfun_layer_dec		( KBFUN_FUNCTION_ARGS );

	// device
	void kbfun_jump_to_bootloader	( KBFUN_FUNCTION_ARGS );

	// numpad
	void kbfun_layermask_numpad_toggle	( KBFUN_FUNCTION_ARGS );
	void kbfun_layermask_numpad_on		( KBFUN_FUNCTION_ARGS );
	void kbfun_layermask_numpad_off		( KBFUN_FUNCTION_ARGS );

	// special
	void kbfun_layer_inc_exec			( KBFUN_FUNCTION_ARGS );
	void kbfun_layer_dec_exec			( KBFUN_FUNCTION_ARGS );
	void kbfun_2_keys_capslock_press_release	( KBFUN_FUNCTION_ARGS );

#endif

