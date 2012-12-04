// vim: ts=4 sw=4 sts=4
/* ----------------------------------------------------------------------------
 * main()
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include <stdbool.h>
#include <stdint.h>
#include <util/delay.h>
#include "./lib-other/pjrc/usb_keyboard/usb_keyboard.h"
#include "./lib/key-functions/public.h"
#include "./keyboard/controller.h"
#include "./keyboard/layout.h"
#include "./keyboard/matrix.h"
#include "./main.h"

// ----------------------------------------------------------------------------

#define  MAX_ACTIVE_LAYERS  20

// ----------------------------------------------------------------------------

static bool _main_kb_is_pressed[KB_ROWS][KB_COLUMNS];
bool (*main_kb_is_pressed)[KB_ROWS][KB_COLUMNS] = &_main_kb_is_pressed;

static bool _main_kb_was_pressed[KB_ROWS][KB_COLUMNS];
bool (*main_kb_was_pressed)[KB_ROWS][KB_COLUMNS] = &_main_kb_was_pressed;

uint8_t main_layers_pressed[KB_ROWS][KB_COLUMNS];

uint8_t main_loop_row;
uint8_t main_loop_col;

uint8_t main_arg_layer;
uint8_t main_arg_layer_offset;
uint8_t main_arg_row;
uint8_t main_arg_col;
bool    main_arg_is_pressed;
bool    main_arg_was_pressed;

// ----------------------------------------------------------------------------

/*
 * main()
 */
int main(void) {
	kb_init();  // does controller initialization too

	kb_led_state_power_on();

	usb_init();
	while (!usb_configured());
	kb_led_delay_usb_init();  // give the OS time to load drivers, etc.

	kb_led_state_ready();

	for (;;) {
		// swap `main_kb_is_pressed` and `main_kb_was_pressed`, then update
		bool (*temp)[KB_ROWS][KB_COLUMNS] = main_kb_was_pressed;
		main_kb_was_pressed = main_kb_is_pressed;
		main_kb_is_pressed = temp;

		kb_update_matrix(*main_kb_is_pressed);

		// this loop is responsible to
		// - "execute" keys when they change state
		// - keep track of which layers the keys were on when they were pressed
		//   (so they can be released using the function from that layer)
		//
		// note
		// - everything else is the key function's responsibility
		//   - see the keyboard layout file ("keyboard/ergodox/layout/*.c") for
		//     which key is assigned which function (per layer)
		//   - see "lib/key-functions/public/*.c" for the function definitions
		#define row          main_loop_row
		#define col          main_loop_col
		#define layer        main_arg_layer
		#define is_pressed   main_arg_is_pressed
		#define was_pressed  main_arg_was_pressed
		for (row=0; row<KB_ROWS; row++) {
			for (col=0; col<KB_COLUMNS; col++) {
				is_pressed = (*main_kb_is_pressed)[row][col];
				was_pressed = (*main_kb_was_pressed)[row][col];

				if (is_pressed != was_pressed) {
					if (is_pressed) {
						layer = main_layers_peek(0);
						main_layers_pressed[row][col] = layer;
					} else {
						layer = main_layers_pressed[row][col];
					}

					// set remaining vars, and "execute" key
					main_arg_row          = row;
					main_arg_col          = col;
					main_arg_layer_offset = 0;
					main_exec_key();
				}
			}
		}
		#undef row
		#undef col
		#undef layer
		#undef is_pressed
		#undef was_pressed

		// send the USB report (even if nothing's changed)
		usb_keyboard_send();
		_delay_ms(MAKEFILE_DEBOUNCE_TIME);

		// update LEDs
		if (keyboard_leds & (1<<0)) { kb_led_num_on(); }
		else { kb_led_num_off(); }
		if (keyboard_leds & (1<<1)) { kb_led_caps_on(); }
		else { kb_led_caps_off(); }
		if (keyboard_leds & (1<<2)) { kb_led_scroll_on(); }
		else { kb_led_scroll_off(); }
		if (keyboard_leds & (1<<3)) { kb_led_compose_on(); }
		else { kb_led_compose_off(); }
		if (keyboard_leds & (1<<4)) { kb_led_kana_on(); }
		else { kb_led_kana_off(); }
	}

	return 0;
}

// ----------------------------------------------------------------------------

// convenience macros (for the helper functions below)
#define  layer        main_arg_layer
#define  row          main_arg_row
#define  col          main_arg_col
#define  is_pressed   main_arg_is_pressed
#define  was_pressed  main_arg_was_pressed

// ----------------------------------------------------------------------------

/*
 * Exec key
 * - Execute the keypress or keyrelease function (if it exists) of the key at
 *   the current possition.
 */
void main_exec_key(void) {
	void (*key_function)(void) =
		( (is_pressed)
		  ? kb_layout_press_get(layer, row, col)
		  : kb_layout_release_get(layer, row, col) );

	if (key_function)
		(*key_function)();
}


/* ----------------------------------------------------------------------------
 * Layer Functions
 * ----------------------------------------------------------------------------
 * We keep track of which layer is foremost by placing it on a stack.  Layers
 * may appear in the stack more than once.  The base layer will always be
 * layer-0.  
 *
 * Implemented as a fixed size stack.
 * ------------------------------------------------------------------------- */

// ----------------------------------------------------------------------------

struct layers {
	uint8_t layer;
	uint8_t id;
};

// ----------------------------------------------------------------------------

struct layers layers[MAX_ACTIVE_LAYERS];
uint8_t       layers_head = 0;
uint8_t       layers_ids_in_use[MAX_ACTIVE_LAYERS] = {true};

/*
 * peek()
 *
 * Arguments
 * - 'offset': the offset (down the stack) from the head element
 *
 * Returns
 * - success: the layer-number of the requested element (which may be 0)
 * - failure: 0 (default) (out of bounds)
 */
uint8_t main_layers_peek(uint8_t offset) {
	if (offset <= layers_head)
		return layers[layers_head - offset].layer;

	return 0;  // default, or error
}

/*
 * push()
 *
 * Arguments
 * - 'layer': the layer-number to push to the top of the stack
 *
 * Returns
 * - success: the id assigned to the newly added element
 * - failure: 0 (the stack was already full)
 */
uint8_t main_layers_push(uint8_t layer) {
	// look for an available id
	for (uint8_t id=1; id<MAX_ACTIVE_LAYERS; id++)
		// if one is found
		if (layers_ids_in_use[id] == false) {
			layers_ids_in_use[id] = true;
			layers_head++;
			layers[layers_head].layer = layer;
			layers[layers_head].id = id;
			return id;
		}

	return 0;  // default, or error
}

/*
 * pop_id()
 *
 * Arguments
 * - 'id': the id of the element to pop from the stack
 */
void main_layers_pop_id(uint8_t id) {
	// look for the element with the id we want to pop
	for (uint8_t element=1; element<=layers_head; element++)
		// if we find it
		if (layers[element].id == id) {
			// move all layers above it down one
			for (; element<layers_head; element++) {
				layers[element].layer = layers[element+1].layer;
				layers[element].id = layers[element+1].id;
			}
			// reinitialize the topmost (now unused) slot
			layers[layers_head].layer = 0;
			layers[layers_head].id = 0;
			// record keeping
			layers_ids_in_use[id] = false;
			layers_head--;
		}
}

/*
 * get_offset_id()
 *
 * Arguments
 * - 'id': the id of the element you want the offset of
 *
 * Returns
 * - success: the offset (down the stack from the head element) of the element
 *   with the given id
 * - failure: 0 (default) (id unassigned)
 */
uint8_t main_layers_get_offset_id(uint8_t id) {
	// look for the element with the id we want to get the offset of
	for (uint8_t element=1; element<=layers_head; element++)
		// if we find it
		if (layers[element].id == id)
			return (layers_head - element);

	return 0;  // default, or error

}

/* ----------------------------------------------------------------------------
 * ------------------------------------------------------------------------- */

