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
#include "lib/usb/keyboard-usage-page.h"
#include "keyboard.h"

#include "key-functions.h"


// ----------------------------------------------------------------------------

#if 0  // not being used right now
static uint8_t _inc_current_layer(uint8_t * current_layer) {
	if (*current_layer < (KB_LAYERS-1))
		(*current_layer)++;
	else
		return 1;  // error: can't increase

	return 0;  // success
}

static uint8_t _dec_current_layer(uint8_t * current_layer) {
	if (*current_layer > 0)
		(*current_layer)--;
	else
		return 1;  // error: can't decrease

	return 0;  // success
}
#endif


// ----------------------------------------------------------------------------

void kbfun_press(
		uint8_t * keycode, uint8_t * current_layer,
		uint8_t * row,     uint8_t * col ) {

	// no-op
	if (*keycode == 0)
		return;

	// modifier keys
	switch (*keycode) {
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
			keyboard_keys[i] = *keycode;
			break;
		}
}

void kbfun_release(
		uint8_t * keycode, uint8_t * current_layer,
		uint8_t * row,     uint8_t * col ) {

	// no-op
	if (*keycode == 0)
		return;

	// modifier keys
	switch (*keycode) {
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
		if (keyboard_keys[i] == *keycode) {
			keyboard_keys[i] = 0;
			break;
		}
}

