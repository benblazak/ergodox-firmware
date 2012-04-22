/* ----------------------------------------------------------------------------
 * key functions: code
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include "lib/pjrc/usb_keyboard/usb_keyboard.h"
#include "lib/_data-types.h"
#include "lib/_usb/keyboard-usage-page.h"

#include "keyboard.h"


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

	for (uint8_t i=0; i<6; i++)
		if (keyboard_keys[i] == 0) {
			keyboard_keys[i] = *keycode;
			break;
		}
}

void kbfun_release(
		uint8_t * keycode, uint8_t * current_layer,
		uint8_t * row,     uint8_t * col ) {

	for (uint8_t i=0; i<6; i++)
		if (keyboard_keys[i] == *keycode) {
			keyboard_keys[i] = 0;
			break;
		}
}

void kbfun_mod_press(
		uint8_t * keycode, uint8_t * current_layer,
		uint8_t * row,     uint8_t * col ) {

	switch (*keycode) {
		case KEY_LeftControl:  keyboard_modifier_keys |= (1<<0); break;
		case KEY_LeftShift:    keyboard_modifier_keys |= (1<<1); break;
		case KEY_LeftAlt:      keyboard_modifier_keys |= (1<<2); break;
		case KEY_LeftGUI:      keyboard_modifier_keys |= (1<<3); break;
		case KEY_RightControl: keyboard_modifier_keys |= (1<<4); break;
		case KEY_RightShift:   keyboard_modifier_keys |= (1<<5); break;
		case KEY_RightAlt:     keyboard_modifier_keys |= (1<<6); break;
		case KEY_RightGUI:     keyboard_modifier_keys |= (1<<7); break;
	}
}

void kbfun_mod_release(
		uint8_t * keycode, uint8_t * current_layer,
		uint8_t * row,     uint8_t * col ) {

	switch (*keycode) {
		case KEY_LeftControl: keyboard_modifier_keys &= ~(1<<0); break;
		case KEY_LeftShift:   keyboard_modifier_keys &= ~(1<<1); break;
		case KEY_LeftAlt:     keyboard_modifier_keys &= ~(1<<2); break;
		case KEY_LeftGUI:     keyboard_modifier_keys &= ~(1<<3); break;
		case KEY_RightControl:keyboard_modifier_keys &= ~(1<<4); break;
		case KEY_RightShift:  keyboard_modifier_keys &= ~(1<<5); break;
		case KEY_RightAlt:    keyboard_modifier_keys &= ~(1<<6); break;
		case KEY_RightGUI:    keyboard_modifier_keys &= ~(1<<7); break;
	}
}

