/* ----------------------------------------------------------------------------
 * key functions : private : code
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include <stdbool.h>
#include <stdint.h>
#include "../../lib-other/pjrc/usb_keyboard/usb_keyboard.h"
#include "../../lib/usb/usage-page/keyboard.h"
#include "../../keyboard/layout.h"
#include "../../keyboard/matrix.h"
#include "../../main.h"
#include "./public.h"

// ----------------------------------------------------------------------------

/*
 * Generate a normal keypress or keyrelease
 *
 * Arguments
 * - press: whether to generate a keypress (true) or keyrelease (false)
 * - keycode: the keycode to use
 *
 * Note
 * - Because of the way USB does things, what this actually does is either add
 *   or remove 'keycode' from the list of currently pressed keys, to be sent at
 *   the end of the current cycle (see main.c)
 */
void _kbfun_press_release(bool press, uint8_t keycode) {
	// no-op
	if (keycode == 0)
		return;

	// modifier keys
	switch (keycode) {
		case KEY_LeftControl:  (press)
				       ? (keyboard_modifier_keys |=  (1<<0))
				       : (keyboard_modifier_keys &= ~(1<<0));
				       return;
		case KEY_LeftShift:    (press)
				       ? (keyboard_modifier_keys |=  (1<<1))
				       : (keyboard_modifier_keys &= ~(1<<1));
				       return;
		case KEY_LeftAlt:      (press)
				       ? (keyboard_modifier_keys |=  (1<<2))
				       : (keyboard_modifier_keys &= ~(1<<2));
				       return;
		case KEY_LeftGUI:      (press)
				       ? (keyboard_modifier_keys |=  (1<<3))
				       : (keyboard_modifier_keys &= ~(1<<3));
				       return;
		case KEY_RightControl: (press)
				       ? (keyboard_modifier_keys |=  (1<<4))
				       : (keyboard_modifier_keys &= ~(1<<4));
				       return;
		case KEY_RightShift:   (press)
				       ? (keyboard_modifier_keys |=  (1<<5))
				       : (keyboard_modifier_keys &= ~(1<<5));
				       return;
		case KEY_RightAlt:     (press)
				       ? (keyboard_modifier_keys |=  (1<<6))
				       : (keyboard_modifier_keys &= ~(1<<6));
				       return;
		case KEY_RightGUI:     (press)
				       ? (keyboard_modifier_keys |=  (1<<7))
				       : (keyboard_modifier_keys &= ~(1<<7));
				       return;
	}

	// all others
	for (uint8_t i=0; i<6; i++) {
		if (press) {
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
 * Note
 * - Leaving all non-current layer values alone allows changing layers while
 *   maintaining a possibly enabled layer mask (as might be used to implement
 *   firmware enabled numlock)
 */
void _kbfun_layer_set_current(uint8_t layer) {
	// don't switch to out-of-bounds layers
	if ( layer < 0 || layer >= KB_LAYERS )
		return;

	for (uint8_t row=0; row<KB_ROWS; row++)
		for (uint8_t col=0; col<KB_COLUMNS; col++)
			// if a key is set to a non-current layer, leave it
			if (main_layers_press[row][col] == main_layers_current)
				main_layers_press[row][col] = layer;

	main_layers_current = layer;
}

/*
 * Set layer mask
 * - Sets the specified key positions to the specified layer
 */
void _kbfun_layer_set_mask(
		uint8_t layer,
		bool positions[KB_ROWS][KB_COLUMNS] ) {

	// don't switch to out-of-bounds layers
	if ( layer < 0 || layer >= KB_LAYERS )
		return;

	for (uint8_t row=0; row<KB_ROWS; row++)
		for (uint8_t col=0; col<KB_COLUMNS; col++)
			if (positions[row][col])
				main_layers_press[row][col] = layer;
}

/*
 * Is the given keycode pressed?
 */
bool _kbfun_is_pressed(uint8_t keycode) {
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

