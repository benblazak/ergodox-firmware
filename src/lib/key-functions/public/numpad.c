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
#include "../../../lib-other/pjrc/usb_keyboard/usb_keyboard.h"
#include "../../../lib/usb/usage-page/keyboard.h"
#include "../../../keyboard/layout.h"
#include "../../../keyboard/matrix.h"
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

static void _toggle_numpad(uint8_t numpad_layer) {
	if (_numpad_activated) {
		// deactivate numpad
		_kbfun_layer_set_mask(main_layers_current, _layer_mask);
		_numpad_activated = false;

		// if: numlock on
		if (keyboard_leds & (1<<0))
			_toggle_numlock();
	} else {
		// activate numpad
		_kbfun_layer_set_mask(numpad_layer, _layer_mask);
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
 * [name]
 *   Numpad toggle
 *
 * [description]
 *   Toggles the numpad and sets numlock on (for active) or off (for inactive)
 *   with it, if it's not already in that state
 */
void kbfun_layermask_numpad_toggle(void) {
	uint8_t keycode = kb_layout_get(layer, row, col);
	_toggle_numpad(keycode);
}

/*
 * [name]
 *   Numpad on
 *
 * [description]
 *   Set the numpad on (along with numlock, if it's not already)
 */
void kbfun_layermask_numpad_on(void) {
	uint8_t keycode = kb_layout_get(layer, row, col);
	if (!_numpad_activated)
		_toggle_numpad(keycode);
}

/*
 * [name]
 *   Numpad off
 *
 * [description]
 *   Set the numpad off (along with numlock, if it's not already)
 */
void kbfun_layermask_numpad_off(void) {
	uint8_t keycode = kb_layout_get(layer, row, col);
	if (_numpad_activated)
		_toggle_numpad(keycode);
}

