/* ----------------------------------------------------------------------------
 * key functions : special : code
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include <stdbool.h>
#include <stdint.h>
#include "../../../lib-other/pjrc/usb_keyboard/usb_keyboard.h"
#include "../../../lib/usb/usage-page/keyboard.h"
#include "../../../keyboard/layout.h"
#include "../../../main.h"
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
 * Increase layer, Execute key
 * - Increment the current layer by the value specified in the keymap (for all
 *   non-masked keys), and execute (usually press|release) the key in the same
 *   position on that new layer
 *
 * Note
 * - Meant to be paired with `kbfun_layer_dec_exec()`
 */
void kbfun_layer_inc_exec(void) {
	uint8_t keycode = kb_layout_get(layer, row, col);

	// switch layers
	_kbfun_layer_set_current(main_layers_current + keycode);

	// exececute second key (in the same position)
	// - `layer+keycode` will be constant (under normal circumstances)
	//   between the press and release
	layer += keycode;
	main_exec_key();
}


/*
 * Decrease layer, Execute key
 * - Decrement the current layer by the value specified in the keymap (for all
 *   non-masked keys), and execute (usually press|release) the key in the same
 *   position on that new layer
 *
 * Note
 * - Meant to be paired with `kbfun_layer_inc_exec()`
 */
void kbfun_layer_dec_exec(void) {
	uint8_t keycode = kb_layout_get(layer, row, col);

	// switch layers
	_kbfun_layer_set_current(main_layers_current - keycode);

	// exececute second key (in the same position)
	// - `layer+keycode` will be constant (under normal circumstances)
	//   between the press and release
	layer += keycode;
	main_exec_key();
}


/*
 * Two keys => capslock
 * - When assigned to two keys (e.g. the physical left and right shift keys)
 *   (in both the press and release matrices), pressing and holding down one of
 *   the keys will make the second key toggle capslock
 *
 * Note
 * - If either of the shifts are pressed when the second key is pressed, they
 *   wil be released so that capslock will register properly when pressed.
 *   Capslock will then be pressed and released, and the original state of the
 *   shifts will be restored
 */
void kbfun_2_keys_capslock_press_release(void) {
	static uint8_t keys_pressed;
	static bool lshift_pressed;
	static bool rshift_pressed;

	uint8_t keycode = kb_layout_get(layer, row, col);

	if (!is_pressed) keys_pressed--;

	// take care of the key that was actually pressed
	_kbfun_press_release(is_pressed, keycode);

	// take care of capslock (only on the press of the 2nd key)
	if (keys_pressed == 1 && is_pressed) {
		// save the state of left and right shift
		lshift_pressed = _kbfun_is_pressed(KEY_LeftShift);
		rshift_pressed = _kbfun_is_pressed(KEY_RightShift);
		// disable both
		_kbfun_press_release(false, KEY_LeftShift);
		_kbfun_press_release(false, KEY_RightShift);

		// press capslock, then release it
		_kbfun_press_release(true, KEY_CapsLock);
		usb_keyboard_send();
		_kbfun_press_release(false, KEY_CapsLock);
		usb_keyboard_send();

		// restore the state of left and right shift
		if (lshift_pressed)
			_kbfun_press_release(true, KEY_LeftShift);
		if (rshift_pressed)
			_kbfun_press_release(true, KEY_RightShift);
	}

	if (is_pressed) keys_pressed++;
}

