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

	// --------------------------------------------------------------------
	// include the appropriate 'matrix.h'
	// -------
	// we're not simply including 'keyboard.h' here because this header is
	// meant to be included by 'keyboard/layout/*.c', which is indirectly
	// included by 'keyboard.h'; and that would lead to a circular include,
	// which gcc might (depending on the order of include statements it
	// encounters) deal with by processing this file before 'matrix.h',
	// which would give us undefined macros here
	#undef _str
	#undef _expstr
	#undef _inc
	#define _str(s) #s          // stringify
	#define _expstr(s) _str(s)  // expand -> stringify
	#define _inc _expstr(keyboard/MAKEFILE_KEYBOARD/matrix.h)  // inc(lude)
	#include _inc
	#undef _str
	#undef _expstr
	#undef _inc
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

	typedef void (*kbfun_funptr_t)( KBFUN_FUNCTION_ARGS );

	void _kbfun_exec_key ( KBFUN_FUNCTION_ARGS );

        void kbfun_press_release                 (KBFUN_FUNCTION_ARGS);
        void kbfun_toggle                        (KBFUN_FUNCTION_ARGS);
        void kbfun_layer_inc                     (KBFUN_FUNCTION_ARGS);
        void kbfun_layer_dec                     (KBFUN_FUNCTION_ARGS);
        void kbfun_layer_inc_exec                (KBFUN_FUNCTION_ARGS);
        void kbfun_layer_dec_exec                (KBFUN_FUNCTION_ARGS);
        void kbfun_2_keys_capslock_press_release (KBFUN_FUNCTION_ARGS);
        void kbfun_layermask_numpad_toggle       (KBFUN_FUNCTION_ARGS);
        void kbfun_layermask_numpad_on           (KBFUN_FUNCTION_ARGS);
        void kbfun_layermask_numpad_off          (KBFUN_FUNCTION_ARGS);
        void kbfun_jump_to_bootloader            (KBFUN_FUNCTION_ARGS);

#endif

