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


#include <avr/interrupt.h>
#include "lib-other/pjrc/usb_keyboard/usb_keyboard.h"
#include "lib/data-types/common.h"
#include "lib/usb/usage-page/keyboard.h"
#include "keyboard.h"

#include "key-functions.h"
#include "key-functions--private.h"


// ----------------------------------------------------------------------------
// public functions (not for keys)
// ----------------------------------------------------------------------------

/*
 * Exec key
 * - Execute the keypress or keyrelease function (if it exists) of the key at
 *   the current possition.  Pass the keycode at the current position, and pass
 *   all other arguments as received
 */
void _kbfun_exec_key( KBFUN_FUNCTION_ARGS ) {
	kbfun_funptr_t key_function =
		( (pressed_)
		  ? kb_layout_press_get(layer_, *row_, *col_)
		  : kb_layout_release_get(layer_, *row_, *col_) );

	if (key_function)
		(*key_function)(
				pressed_,
				kb_layout_get(layer_, *row_, *col_),
				layer_,
				row_,
				col_,
				current_layer_,
				current_layers_,
				pressed_layers_ );
}


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
void _press_release(bool pressed, uint8_t keycode) {
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
void _layer_set_current(
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
void _layer_set_mask(
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
 * Press|Release
 * - Generate a normal keypress or keyrelease
 */
void kbfun_press_release( KBFUN_FUNCTION_ARGS ) {
	_press_release(pressed_, keycode_);
}

/*
 * Toggle
 * - Toggle the key pressed or unpressed
 */
void kbfun_toggle( KBFUN_FUNCTION_ARGS ) {
	if (_is_pressed(keycode_))
		_press_release(false, keycode_);
	else
		_press_release(true, keycode_);
}

/*
 * Increase layer
 * - Increment the current layer by the value specified in the keymap (for all
 *   non-masked keys)
 */
void kbfun_layer_inc( KBFUN_FUNCTION_ARGS ) {
	_layer_set_current(
			(*current_layer_) + keycode_,
			current_layer_,
			current_layers_ );
}

/*
 * Decrease layer
 * - Decrement the current layer by the value specified in the keymap (for all
 *   non-masked keys)
 */
void kbfun_layer_dec( KBFUN_FUNCTION_ARGS ) {
	_layer_set_current(
			(*current_layer_) - keycode_,
			current_layer_,
			current_layers_ );
}

/*
 * Increase layer, Execute key
 * - Increment the current layer by the value specified in the keymap (for all
 *   non-masked keys), and execute (usually press|release) the key in the same
 *   position on that new layer
 *
 * Note
 * - Meant to be paired with `kbfun_layer_dec_exec()`
 */
void kbfun_layer_inc_exec( KBFUN_FUNCTION_ARGS ) {
	// switch layers
	_layer_set_current(
			(*current_layer_) + keycode_,
			current_layer_,
			current_layers_ );

	// exececute second key (in the same position)
	// - `layer_+keycode_` will be constant (under normal circumstances)
	//   between the press and release
	_kbfun_exec_key(
			pressed_, 0, layer_+keycode_,
			row_, col_, current_layer_,
			current_layers_, pressed_layers_ );
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
void kbfun_layer_dec_exec( KBFUN_FUNCTION_ARGS ) {
	// switch layers
	_layer_set_current(
			(*current_layer_) - keycode_,
			current_layer_,
			current_layers_ );

	// exececute second key (in the same position)
	// - `layer_+keycode_` will be constant (under normal circumstances)
	//   between the press and release
	_kbfun_exec_key(
			pressed_, 0, layer_+keycode_,
			row_, col_, current_layer_,
			current_layers_, pressed_layers_ );
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
void kbfun_2_keys_capslock_press_release( KBFUN_FUNCTION_ARGS ) {
	static uint8_t keys_pressed;
	static bool lshift_pressed;
	static bool rshift_pressed;

	if (!pressed_) keys_pressed--;

	// take care of the key that was actually pressed
	_press_release(pressed_, keycode_);

	// take care of capslock (only on the press of the 2nd key)
	if (keys_pressed == 1 && pressed_) {
		// save the state of left and right shift
		lshift_pressed = _is_pressed(KEY_LeftShift);
		rshift_pressed = _is_pressed(KEY_RightShift);
		// disable both
		_press_release(false, KEY_LeftShift);
		_press_release(false, KEY_RightShift);

		// press capslock, then release it
		_press_release(true, KEY_CapsLock);
		usb_keyboard_send();
		_press_release(false, KEY_CapsLock);
		usb_keyboard_send();

		// restore the state of left and right shift
		if (lshift_pressed)
			_press_release(true, KEY_LeftShift);
		if (rshift_pressed)
			_press_release(true, KEY_RightShift);
	}

	if (pressed_) keys_pressed++;
}


// TODO: maybe the numpad functions (and other logical sets of functions?) need
// to be in (a) seaparate file(s).
/* ----------------------------------------------------------------------------
 * Numpad functions
 * - Functions to implement an embedded numpad
 *
 * Notes
 * - The numpad is toggled by shifting (without changing the overall current
 *   layer) the layer of the keys specified in this function to the value
 *   specified in the keymap
 * - When the numpad is toggled, the numlock is set to on (for active) or off
 *   (for inactive) as well
 * - All these functions cooperate, but if more than one layer mask of this
 *   type is used (by a different set of functions) at the same time, the
 *   second will override the first, and any keys covered by both will be reset
 *   to the overall current layer when either is released (even if the other is
 *   still pressed)
 * ------------------------------------------------------------------------- */

// prefix function (undefined later)
// - to keep these names reasonable in this block, and obviously not global
//   outside it
// - 'L' is for 'local'
#define L(name) _kbfun_layermask_numpad__##name

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

// vars
static bool L(numpad_activated) = false;
static bool L(layer_mask)[KB_ROWS][KB_COLUMNS] =
	MATRIX_LAYER(
		// unused
		0,

		// left hand
		  0,  0,  0,  0,  0,  0,  0,
		  0,  0,  0,  0,  0,  0,  0,
		  0,  0,  0,  0,  0,  0,
		  0,  0,  0,  0,  0,  0,  0,
		  0,  0,  0,  0,  0,
		                      0,  0,
		                      0,  0,  0,
		                      0,  0,  0,

		// right hand
		      0,  0,  1,  1,  1,  1,  0,
		      0,  0,  1,  1,  1,  1,  0,
		          0,  1,  1,  1,  1,  0,
		      0,  0,  1,  1,  1,  1,  0,
		              0,  0,  0,  0,  0,
		      0,  0,
		  0,  0,  0,
		  0,  0,  0 );

// functions
static inline void L(toggle_numlock)(void) {
	_press_release(true, KEYPAD_NumLock_Clear);
	usb_keyboard_send();
	_press_release(false, KEYPAD_NumLock_Clear);
	usb_keyboard_send();
}

static void L(toggle_numpad)(
		uint8_t numpad_layer,
		uint8_t current_layer,
		uint8_t (*current_layers)[KB_ROWS][KB_COLUMNS] ) {

	if (L(numpad_activated)) {
		// deactivate numpad
		_layer_set_mask(current_layer, L(layer_mask), current_layers);
		L(numpad_activated) = false;

		// if: numlock on
		if (keyboard_leds & (1<<0))
			L(toggle_numlock)();
	} else {
		// activate numpad
		_layer_set_mask(numpad_layer, L(layer_mask), current_layers);
		L(numpad_activated) = true;

		// if: numlock off
		if (!(keyboard_leds & (1<<0)))
			L(toggle_numlock)();
	}
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

/*
 * Numpad toggle
 * - Toggles the numpad and sets numlock on (for active) or off (for inactive)
 *   with it, if it's not already in that state
 */
void kbfun_layermask_numpad_toggle( KBFUN_FUNCTION_ARGS ) {
	L(toggle_numpad)(keycode_, *current_layer_, current_layers_);
}

/*
 * Numpad on
 * - Set the numpad on (along with numlock, if it's not already)
 */
void kbfun_layermask_numpad_on( KBFUN_FUNCTION_ARGS ) {
	if (!L(numpad_activated))
		L(toggle_numpad)(keycode_, *current_layer_, current_layers_);
}

/*
 * Numpad off
 * - Set the numpad off (along with numlock, if it's not already)
 */
void kbfun_layermask_numpad_off( KBFUN_FUNCTION_ARGS ) {
	if (L(numpad_activated))
		L(toggle_numpad)(keycode_, *current_layer_, current_layers_);
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

// prefix function (undefined here)
#undef L

/* ----------------------------------------------------------------------------
 * ------------------------------------------------------------------------- */


// ----------------------------------------------------------------------------
// public functions (device specific)
// ----------------------------------------------------------------------------

void kbfun_jump_to_bootloader( KBFUN_FUNCTION_ARGS ) {

	// from PJRC (slightly modified)
	// <http://www.pjrc.com/teensy/jump_to_bootloader.html>
#if MAKEFILE_BOARD == teensy-2-0
	// --- for all Teensy boards
	cli();

	// disable watchdog, if enabled
	// disable all peripherals
	UDCON = 1;
	USBCON = (1<<FRZCLK);  // disable USB
	UCSR1B = 0;
	_delay_ms(5);

	// --- Teensy 2.0 specific
	EIMSK = 0; PCICR = 0; SPCR = 0; ACSR = 0; EECR = 0; ADCSRA = 0;
	TIMSK0 = 0; TIMSK1 = 0; TIMSK3 = 0; TIMSK4 = 0; UCSR1B = 0; TWCR = 0;
	DDRB = 0; DDRC = 0; DDRD = 0; DDRE = 0; DDRF = 0; TWCR = 0;
	PORTB = 0; PORTC = 0; PORTD = 0; PORTE = 0; PORTF = 0;
	asm volatile("jmp 0x7E00");
#endif

	// else, function does nothing
}

