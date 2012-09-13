// vim: ts=4 sw=4 sts=4
/* ----------------------------------------------------------------------------
 * main()
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include <util/delay.h>
#include "lib-other/pjrc/usb_keyboard/usb_keyboard.h"
#include "lib/data-types.h"
#include "lib/key-functions.h"

#include "keyboard.h"


int main(void) {
	kb_init();  // does controller initialization too

	kb_led_state_power_on();

	usb_init();
	while (!usb_configured());
	kb_led_delay_usb_init();  // give the OS time to load drivers, etc.

	kb_led_state_ready();

	for (;;) {
		// the overall current layer
		static uint8_t current_layer;
		// the current layer for each key
		static uint8_t current_layers[KB_ROWS][KB_COLUMNS];
		// the layer each key was on when it was last pressed
		static uint8_t pressed_layers[KB_ROWS][KB_COLUMNS];

		// swap `kb_is_pressed` and `kb_was_pressed`, then update
		bool (*temp)[KB_ROWS][KB_COLUMNS] = kb_was_pressed;
		kb_was_pressed = kb_is_pressed;
		kb_is_pressed = temp;

		kb_update_matrix(*kb_is_pressed);

		// this loop is responsible to
		// - "execute" keys when they change state (call `_kbfun_exec_key()`,
		//   which will call the appropriate function with the appropriate
		//   keycode argument from the kb_layout* matrices)
		// - keep track of which layers the keys were on when they were pressed
		//   (so they can be released using the function from that layer)
		//
		// note
		// - everything else is the key function's responsibility
		//   - see the keyboard layout file ("keyboard/ergodox/layout/*.c") for
		//     which key is assigned which function (per layer)
		//   - see "lib/key-functions.c" for the function definitions
		// - anything passed to the key function by reference is fair game for
		//   that function to modify
		for (uint8_t row=0; row<KB_ROWS; row++) {
			for (uint8_t col=0; col<KB_COLUMNS; col++) {

				bool is_pressed = (*kb_is_pressed)[row][col];
				bool was_pressed = (*kb_was_pressed)[row][col];

				if (is_pressed != was_pressed) {
					uint8_t layer = ( (is_pressed)
					                  ? current_layers[row][col]
					                  : pressed_layers[row][col] );

					if (is_pressed)
						pressed_layers[row][col] = layer;

					_kbfun_exec_key(
							is_pressed, 0, layer,
							&row, &col, &current_layer,
							&current_layers, &pressed_layers );
				}
			}
		}

		// send the USB report (even if nothing's changed)
		usb_keyboard_send();
		_delay_ms(KB_DEBOUNCE_TIME);

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

