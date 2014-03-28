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
	void kbfun_press_release_preserve_sticky (void);
	void kbfun_toggle        (void);
	void kbfun_transparent   (void);
	// --- layer push/pop functions
	void kbfun_layer_push_1  (void);
	void kbfun_layer_push_2  (void);
	void kbfun_layer_push_3  (void);
	void kbfun_layer_push_4  (void);
	void kbfun_layer_push_5  (void);
	void kbfun_layer_push_6  (void);
	void kbfun_layer_push_7  (void);
	void kbfun_layer_push_8  (void);
	void kbfun_layer_push_9  (void);
	void kbfun_layer_push_10 (void);
	void kbfun_layer_sticky_1  (void);
	void kbfun_layer_sticky_2  (void);
	void kbfun_layer_sticky_3  (void);
	void kbfun_layer_sticky_4  (void);
	void kbfun_layer_sticky_5  (void);
	void kbfun_layer_sticky_6  (void);
	void kbfun_layer_sticky_7  (void);
	void kbfun_layer_sticky_8  (void);
	void kbfun_layer_sticky_9  (void);
	void kbfun_layer_sticky_10 (void);
	void kbfun_layer_pop_1   (void);
	void kbfun_layer_pop_2   (void);
	void kbfun_layer_pop_3   (void);
	void kbfun_layer_pop_4   (void);
	void kbfun_layer_pop_5   (void);
	void kbfun_layer_pop_6   (void);
	void kbfun_layer_pop_7   (void);
	void kbfun_layer_pop_8   (void);
	void kbfun_layer_pop_9   (void);
	void kbfun_layer_pop_10  (void);
	// ---

	// device
	void kbfun_jump_to_bootloader (void);

	// special
	void kbfun_shift_press_release           (void);
	void kbfun_2_keys_capslock_press_release (void);
	void kbfun_layer_push_numpad             (void);
	void kbfun_layer_pop_numpad              (void);
	void kbfun_mediakey_press_release        (void);

#endif

