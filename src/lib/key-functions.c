/* ----------------------------------------------------------------------------
 * key functions: code
 *
 * These functions may do.. pretty much anything rational that thay like.  If
 * they want keycodes to be sent to the host in an aggrate report, they're
 * responsible for modifying the appropriate report variables.
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include "lib-other/pjrc/usb_keyboard/usb_keyboard.h"
#include "lib/data-types.h"
#include "lib/usb/usage-page/keyboard.h"
#include "keyboard.h"

#include "key-functions.h"

// ----------------------------------------------------------------------------

/*
 * Generate a normal keypress or keyrelease
 *
 * Arguments
 * - keycode: the keycode to use
 * - pressed: whether to generate a keypress (true) or keyrelease (false)
 *
 * Note
 * - Because of the way USB does things, what this actually does is either add
 *   or remove 'keycode' from the list of currently pressed keys
 */
static void _press_release(uint8_t keycode, bool pressed) {
	// no-op
	if (keycode == 0)
		return;

	// modifier keys
	switch (keycode) {
		case KEY_LeftControl:  (pressed)
				       ? (keyboard_modifier_keys |=  (1<<0))
				       : (keyboard_modifier_keys &= ~(1<<0));
				       return;
		case KEY_LeftShift:    (pressed)
				       ? (keyboard_modifier_keys |=  (1<<1))
				       : (keyboard_modifier_keys &= ~(1<<1));
				       return;
		case KEY_LeftAlt:      (pressed)
				       ? (keyboard_modifier_keys |=  (1<<2))
				       : (keyboard_modifier_keys &= ~(1<<2));
				       return;
		case KEY_LeftGUI:      (pressed)
				       ? (keyboard_modifier_keys |=  (1<<3))
				       : (keyboard_modifier_keys &= ~(1<<3));
				       return;
		case KEY_RightControl: (pressed)
				       ? (keyboard_modifier_keys |=  (1<<4))
				       : (keyboard_modifier_keys &= ~(1<<4));
				       return;
		case KEY_RightShift:   (pressed)
				       ? (keyboard_modifier_keys |=  (1<<5))
				       : (keyboard_modifier_keys &= ~(1<<5));
				       return;
		case KEY_RightAlt:     (pressed)
				       ? (keyboard_modifier_keys |=  (1<<6))
				       : (keyboard_modifier_keys &= ~(1<<6));
				       return;
		case KEY_RightGUI:     (pressed)
				       ? (keyboard_modifier_keys |=  (1<<7))
				       : (keyboard_modifier_keys &= ~(1<<7));
				       return;
	}

	// all others
	for (uint8_t i=0; i<6; i++) {
		if (pressed) {
			if (keyboard_keys[i] == 0) {
				keyboard_keys[i] = keycode;
				return;
			}
		} else {
			if (keyboard_keys[i] == keycode) {
				keyboard_keys[i] = 0;
				return;
			}
		}
	}
}

// ----------------------------------------------------------------------------

/*
 * - press
 * - generate a normal keypress
 */
void kbfun_press( KBFUN_FUNCTION_ARGS ) {
	_press_release(keycode_, true);
}

/*
 * - release
 * - generate a normal keyrelease
 */
void kbfun_release( KBFUN_FUNCTION_ARGS ) {
	_press_release(keycode_, false);
}

// TODO:
// - implement layer lock key combos (make a function to switch to a specific
//   layer)

/*
 * - next layer
 * - layer increment (for all keys)
 */
void kbfun_layer_inc( KBFUN_FUNCTION_ARGS ) {
	for (uint8_t row=0; row<KB_ROWS; row++)
		for (uint8_t col=0; col<KB_COLUMNS; col++)
			if ((*current_layers_)[row][col] < (KB_LAYERS-1))
				((*current_layers_)[row][col])++;
			// else do nothing
}

/*
 * - previous layer
 * - layer decrement (for all keys)
 */
void kbfun_layer_dec( KBFUN_FUNCTION_ARGS ) {
	for (uint8_t row=0; row<KB_ROWS; row++)
		for (uint8_t col=0; col<KB_COLUMNS; col++)
			if ((*current_layers_)[row][col] > 0)
				((*current_layers_)[row][col])--;
			// else do nothing
}

/*
 * - two keys => capslock
 * - when assigned to two keys (e.g. the physical left and right shift keys),
 *   pressing and holding down one of them makes the second toggle capslock
 */
void kbfun_2_keys_capslock_press_release( KBFUN_FUNCTION_ARGS ) {
	static uint8_t keys_pressed = 0;

	if (!pressed_) keys_pressed--;

	_press_release(keycode_, pressed_);
	if (keys_pressed == 1)
		_press_release(KEY_CapsLock, pressed_);

	if (pressed_) keys_pressed++;
}

