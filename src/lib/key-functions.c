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

#include "key-functions.h"  // includes the appropriate keyboard 'matrix.h'
#include "key-functions--private.h"


// ----------------------------------------------------------------------------
// private functions
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
 *   or remove 'keycode' from the list of currently pressed keys, to be sent at
 *   the end of the current cycle (see main.c)
 */
void _press_release(uint8_t keycode, bool pressed) {
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

/*
 * Set current layer
 * - Sets any keys currently set to the overall current layer to the new layer,
 *   and then sets the overall current layer
 *
 * Arguments
 * - value: the new layer value
 * - current_layer: (a pointer to) the overall current layer (see main.c)
 * - current_layers: (a pointer to a matrix of) the current layer for each key
 *   (see main.c and lib/key-functions.h)
 *
 * Note
 * - Leaving all non-current layer values alone allows changing layers while
 *   maintaining a possibly enabled layer mask (as might be used to implement
 *   firmware enabled numlock)
 */
void _layer_set_current(
		uint8_t value,
		uint8_t * current_layer,
		uint8_t (*current_layers)[KB_ROWS][KB_COLUMNS] ) {

	// don't switch to out-of-bounds layers
	if ( value < 0 || value >= KB_LAYERS )
		return;

	for (uint8_t row=0; row<KB_ROWS; row++)
		for (uint8_t col=0; col<KB_COLUMNS; col++)
			// if a key is set to a non-current layer, let it be
			if ((*current_layers)[row][col] == *current_layer)
				(*current_layers)[row][col] = value;

	(*current_layer) = value;
}

/*
 * Is the given keycode pressed?
 */
bool _is_pressed(uint8_t keycode) {
	// modifier keys
	switch (keycode) {
		case KEY_LeftControl:  if (keyboard_modifier_keys & (1<<0))
					       return true;
		case KEY_LeftShift:    if (keyboard_modifier_keys & (1<<1))
					       return true;
		case KEY_LeftAlt:      if (keyboard_modifier_keys & (1<<2))
					       return true;
		case KEY_LeftGUI:      if (keyboard_modifier_keys & (1<<3))
					       return true;
		case KEY_RightControl: if (keyboard_modifier_keys & (1<<4))
					       return true;
		case KEY_RightShift:   if (keyboard_modifier_keys & (1<<5))
					       return true;
		case KEY_RightAlt:     if (keyboard_modifier_keys & (1<<6))
					       return true;
		case KEY_RightGUI:     if (keyboard_modifier_keys & (1<<7))
					       return true;
	}

	// all others
	for (uint8_t i=0; i<6; i++)
		if (keyboard_keys[i] == keycode)
			return true;

	return false;
}


// ----------------------------------------------------------------------------
// public functions
// ----------------------------------------------------------------------------

/*
 * Press
 * - Generate a normal keypress
 */
void kbfun_press( KBFUN_FUNCTION_ARGS ) {
	_press_release(keycode_, true);
}

/*
 * Release
 * - Generate a normal keyrelease
 */
void kbfun_release( KBFUN_FUNCTION_ARGS ) {
	_press_release(keycode_, false);
}

/*
 * Set layer
 * - Set layer to the value specified in the keymap (using the value as a
 *   number instead of a keycode)
 */
void kbfun_layer_set( KBFUN_FUNCTION_ARGS ) {
	_layer_set_current( keycode_, current_layer_, current_layers_ );
}

/*
 * Increase layer
 * - Increment layer by the value specified in the keymap (for all non-masked
 *   keys)
 */
void kbfun_layer_inc( KBFUN_FUNCTION_ARGS ) {
	_layer_set_current(
			(*current_layer_) + keycode_,
			current_layer_,
			current_layers_ );
}

/*
 * Decrease layer
 * - Decrement layer by the value specified in the keymap (for all non-masked
 *   keys)
 */
void kbfun_layer_dec( KBFUN_FUNCTION_ARGS ) {
	_layer_set_current(
			(*current_layer_) - keycode_,
			current_layer_,
			current_layers_ );
}

/*
 * Two keys => capslock
 * - When assigned to two keys (e.g. the physical left and right shift keys)
 *   (in both the press and release matrices), pressing and holding down one of
 *   the keys will make the second toggle capslock
 *
 * Note
 * - If either of the shifts are pressed when the second key is pressed, they
 *   wil be released so that capslock will register properly when pressed.
 *   Capslock will then be pressed and released, and the original state of the
 *   shifts will be restored
 */
#include "../lib/usb/usage-page/keyboard.h"
void kbfun_2_keys_capslock_press_release( KBFUN_FUNCTION_ARGS ) {
	static uint8_t keys_pressed;
	static bool lshift_pressed;
	static bool rshift_pressed;

	if (!pressed_) keys_pressed--;

	// take care of the key that was actually pressed
	_press_release(keycode_, pressed_);

	// take care of capslock (only on the press of the 2nd key)
	if (keys_pressed == 1 && pressed_) {
		// save the state of left and right shift
		lshift_pressed = _is_pressed(KEY_LeftShift);
		rshift_pressed = _is_pressed(KEY_RightShift);
		// disable both
		_press_release(KEY_LeftShift, false);
		_press_release(KEY_RightShift, false);

		// press capslock, then release it
		_press_release(KEY_CapsLock, true);
		usb_keyboard_send();
		_press_release(KEY_CapsLock, false);
		usb_keyboard_send();

		// restore the state of left and right shift
		if (lshift_pressed)
			_press_release(KEY_LeftShift, true);
		if (rshift_pressed)
			_press_release(KEY_RightShift, true);
	}

	if (pressed_) keys_pressed++;
}

