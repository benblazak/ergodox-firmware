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


void kbfun_press( KBFUN_FUNCTION_ARGS ) {
	// no-op
	if (keycode_ == 0)
		return;

	// modifier keys
	switch (keycode_) {
		case KEY_LeftControl:  keyboard_modifier_keys |= (1<<0);
				       return;
		case KEY_LeftShift:    keyboard_modifier_keys |= (1<<1);
				       return;
		case KEY_LeftAlt:      keyboard_modifier_keys |= (1<<2);
				       return;
		case KEY_LeftGUI:      keyboard_modifier_keys |= (1<<3);
				       return;
		case KEY_RightControl: keyboard_modifier_keys |= (1<<4);
				       return;
		case KEY_RightShift:   keyboard_modifier_keys |= (1<<5);
				       return;
		case KEY_RightAlt:     keyboard_modifier_keys |= (1<<6);
				       return;
		case KEY_RightGUI:     keyboard_modifier_keys |= (1<<7);
				       return;
	}

	// all others
	for (uint8_t i=0; i<6; i++)
		if (keyboard_keys[i] == 0) {
			keyboard_keys[i] = keycode_;
			return;
		}
}

void kbfun_release( KBFUN_FUNCTION_ARGS ) {
	// no-op
	if (keycode_ == 0)
		return;

	// modifier keys
	switch (keycode_) {
		case KEY_LeftControl:  keyboard_modifier_keys &= ~(1<<0);
				       return;
		case KEY_LeftShift:    keyboard_modifier_keys &= ~(1<<1);
				       return;
		case KEY_LeftAlt:      keyboard_modifier_keys &= ~(1<<2);
				       return;
		case KEY_LeftGUI:      keyboard_modifier_keys &= ~(1<<3);
				       return;
		case KEY_RightControl: keyboard_modifier_keys &= ~(1<<4);
				       return;
		case KEY_RightShift:   keyboard_modifier_keys &= ~(1<<5);
				       return;
		case KEY_RightAlt:     keyboard_modifier_keys &= ~(1<<6);
				       return;
		case KEY_RightGUI:     keyboard_modifier_keys &= ~(1<<7);
				       return;
	}

	// all others
	for (uint8_t i=0; i<6; i++)
		if (keyboard_keys[i] == keycode_) {
			keyboard_keys[i] = 0;
			return;
		}
}

// TODO:
// - implement two shifts => capslock
// - implement layer lock key combos (make a function to switch to a specific
//   layer)

void kbfun_layer_inc( KBFUN_FUNCTION_ARGS ) {
	for (uint8_t row=0; row<KB_ROWS; row++)
		for (uint8_t col=0; col<KB_COLUMNS; col++)
			if ((*current_layers_)[row][col] < (KB_LAYERS-1))
				((*current_layers_)[row][col])++;
			// else do nothing
}

void kbfun_layer_dec( KBFUN_FUNCTION_ARGS ) {
	for (uint8_t row=0; row<KB_ROWS; row++)
		for (uint8_t col=0; col<KB_COLUMNS; col++)
			if ((*current_layers_)[row][col] > 0)
				((*current_layers_)[row][col])--;
			// else do nothing
}

