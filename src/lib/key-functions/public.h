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

	// --------------------------------------------------------------------

	// basic
	void kbfun_press_release (void);
	void kbfun_toggle        (void);
	void kbfun_layer_inc     (void);
	void kbfun_layer_dec     (void);

	// device
	void kbfun_jump_to_bootloader (void);

	// numpad
	void kbfun_layermask_numpad_toggle (void);
	void kbfun_layermask_numpad_on     (void);
	void kbfun_layermask_numpad_off    (void);

	// special
	void kbfun_layer_inc_exec                (void);
	void kbfun_layer_dec_exec                (void);
	void kbfun_2_keys_capslock_press_release (void);

#endif

