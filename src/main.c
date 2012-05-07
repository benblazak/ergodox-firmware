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


// note:
// - see your keyswitch specification for the necessary value.  for cherry mx
//   switches, bounce time should be <= 5ms.  it looks like most switches are
//   speced between 5 and 8 ms.
// - if timing is important, balance this value with the main() loop run time
//   (~5ms, last i checked, nearly all of it in the i2c update() function)
#define DEBOUNCE_TIME 5  // in ms


int main(void) {
	kb_init();  // does controller initialization too

	kb_led1_on();
	kb_led2_on();
	kb_led3_on();

	usb_init();
	while (!usb_configured());
	_delay_ms(1000);  // make sure the OS has had time to load drivers, etc.

	kb_led1_off();
	kb_led2_off();
	kb_led3_off();

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
					_delay_ms(DEBOUNCE_TIME);
				}
			}
		}

		// update LEDs
		(keyboard_leds & (1<<0)) ? kb_led1_on() : kb_led1_off(); // num lock
		(keyboard_leds & (1<<1)) ? kb_led2_on() : kb_led2_off(); // caps lock
		(keyboard_leds & (1<<2)) ? kb_led3_on() : kb_led3_off(); // scroll lock
		#if 0  // not implemented right now
		(keyboard_leds & (1<<3)) ? kb_led4_on() : kb_led4_off(); // compose
		(keyboard_leds & (1<<4)) ? kb_led5_on() : kb_led5_off(); // kana
		#endif
	}

	return 0;
}

