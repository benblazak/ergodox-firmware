/* ----------------------------------------------------------------------------
 * key functions : numpad : code
 *
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
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include <stdbool.h>
#include <stdint.h>
#include "src/lib-other/pjrc/usb_keyboard/usb_keyboard.h"
#include "src/lib/usb/usage-page/keyboard.h"
#include "src/keyboard/matrix.h"
#include "../public.h"
#include "../private.h"


// ----------------------------------------------------------------------------
// vars
// ----------------------------------------------------------------------------

static bool _numpad_activated = false;

static bool _layer_mask[KB_ROWS][KB_COLUMNS] =
	KB_MATRIX_LAYER(
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


// ----------------------------------------------------------------------------
// private functions
// ----------------------------------------------------------------------------

static inline void _toggle_numlock(void) {
	_kbfun_press_release(true, KEYPAD_NumLock_Clear);
	usb_keyboard_send();
	_kbfun_press_release(false, KEYPAD_NumLock_Clear);
	usb_keyboard_send();
}

static void _toggle_numpad(
		uint8_t numpad_layer,
		uint8_t current_layer,
		uint8_t (*current_layers)[KB_ROWS][KB_COLUMNS] ) {

	if (_numpad_activated) {
		// deactivate numpad
		_kbfun_layer_set_mask(
				current_layer, _layer_mask, current_layers );
		_numpad_activated = false;

		// if: numlock on
		if (keyboard_leds & (1<<0))
			_toggle_numlock();
	} else {
		// activate numpad
		_kbfun_layer_set_mask(
				numpad_layer, _layer_mask, current_layers );
		_numpad_activated = true;

		// if: numlock off
		if (!(keyboard_leds & (1<<0)))
			_toggle_numlock();
	}
}


// ----------------------------------------------------------------------------
// public functions
// ----------------------------------------------------------------------------

/*
 * Numpad toggle
 * - Toggles the numpad and sets numlock on (for active) or off (for inactive)
 *   with it, if it's not already in that state
 */
void kbfun_layermask_numpad_toggle( KBFUN_FUNCTION_ARGS ) {
	_toggle_numpad(keycode_, *current_layer_, current_layers_);
}

/*
 * Numpad on
 * - Set the numpad on (along with numlock, if it's not already)
 */
void kbfun_layermask_numpad_on( KBFUN_FUNCTION_ARGS ) {
	if (!_numpad_activated)
		_toggle_numpad(keycode_, *current_layer_, current_layers_);
}

/*
 * Numpad off
 * - Set the numpad off (along with numlock, if it's not already)
 */
void kbfun_layermask_numpad_off( KBFUN_FUNCTION_ARGS ) {
	if (_numpad_activated)
		_toggle_numpad(keycode_, *current_layer_, current_layers_);
}

