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

#include "keyboard.h"


int main(void) {
	kb_init();  // does controller initialization too

	kb_led_state_power_on();

	usb_init();
	while (!usb_configured());
	kb_led_delay_usb_init();  // give the OS time to load drivers, etc.

	kb_led_state_ready();

	for (;;) {
		static uint8_t current_layer = 0;

		// swap `kb_is_pressed` and `kb_was_pressed`, then update
		bool (*temp)[KB_ROWS][KB_COLUMNS] = kb_was_pressed;
		kb_was_pressed = kb_is_pressed;
		kb_is_pressed = temp;

		kb_update_matrix(*kb_is_pressed);

		// call the appropriate function for each key, then send the usb report
		// if necessary
		// - everything else is the key function's responsibility; see the
		//   keyboard layout file ("keyboard/ergodox/layout/*.c") for which key
		//   is assigned which function (per layer), and "lib/key-functions.c"
		//   for their definitions
		for (uint8_t row=0; row<KB_ROWS; row++) {
			for (uint8_t col=0; col<KB_COLUMNS; col++) {
				bool is_pressed = (*kb_is_pressed)[row][col];
				bool was_pressed = (*kb_was_pressed)[row][col];
				if (is_pressed != was_pressed) {
					if (is_pressed) {
						kbfun_funptr_t press_function =
								kb_layout_press_get(current_layer, row, col);
						if (press_function) {
							(*press_function)(
									kb_layout_get(current_layer, row, col),
									&current_layer, &row, &col );
						}
					} else {
						kbfun_funptr_t release_function =
								kb_layout_release_get(current_layer, row, col);
						if (release_function) {
							(*release_function)(
									kb_layout_get(current_layer, row, col),
									&current_layer, &row, &col );
						}
					}

					usb_keyboard_send();
					_delay_ms(KB_DEBOUNCE_TIME);
				}
			}
		}

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

