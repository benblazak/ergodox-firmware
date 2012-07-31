/* ----------------------------------------------------------------------------
 * key functions : private : code
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include <stdbool.h>
#include <stdint.h>
#include "src/lib-other/pjrc/usb_keyboard/usb_keyboard.h"
#include "src/lib/usb/usage-page/keyboard.h"
#include "src/keyboard/layout.h"
#include "src/keyboard/matrix.h"
#include "./public.h"

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
void _kbfun_press_release(bool pressed, uint8_t keycode) {
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
 * - layer: the new layer value
 * - current_layer: (a pointer to) the overall current layer (see main.c)
 * - current_layers: (a pointer to a matrix of) the current layer for each key
 *   (see main.c and lib/key-functions.h)
 *
 * Note
 * - Leaving all non-current layer values alone allows changing layers while
 *   maintaining a possibly enabled layer mask (as might be used to implement
 *   firmware enabled numlock)
 */
void _kbfun_layer_set_current(
		uint8_t layer,
		uint8_t * current_layer,
		uint8_t (*current_layers)[KB_ROWS][KB_COLUMNS] ) {

	// don't switch to out-of-bounds layers
	if ( layer < 0 || layer >= KB_LAYERS )
		return;

	for (uint8_t row=0; row<KB_ROWS; row++)
		for (uint8_t col=0; col<KB_COLUMNS; col++)
			// if a key is set to a non-current layer, leave it
			if ((*current_layers)[row][col] == *current_layer)
				(*current_layers)[row][col] = layer;

	(*current_layer) = layer;
}

/*
 * Set layer mask
 * - Sets the specified key positions to the specified layer
 */
void _kbfun_layer_set_mask(
		uint8_t layer,
		bool positions[KB_ROWS][KB_COLUMNS],
		uint8_t (*current_layers)[KB_ROWS][KB_COLUMNS] ) {

	// don't switch to out-of-bounds layers
	if ( layer < 0 || layer >= KB_LAYERS )
		return;

	for (uint8_t row=0; row<KB_ROWS; row++)
		for (uint8_t col=0; col<KB_COLUMNS; col++)
			if (positions[row][col])
				(*current_layers)[row][col] = layer;
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

