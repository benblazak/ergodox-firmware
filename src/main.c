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

// #include "keyboard.h"
//dbg
#define KEYBOARD_INCLUDE_PRIVATE
#include "keyboard/ergodox/teensy-2-0.h"
#include "keyboard/ergodox/mcp23018.h"
#include "keyboard.h"
///


#define DEBOUNCE_TIME 5  // in ms;  see the spec for your keyswitches


//dbg
static void _toggle_led3(void) {
	static bool led_on = false;
	if (led_on) {
		KB_LED3_OFF;
		led_on = false;
	} else {
		KB_LED3_ON;
		led_on = true;
	}
}
///
int main(void) {
	kb_init();  // does controller initialization too

	usb_init();
	while (!usb_configured());
	_delay_ms(1000);  // make sure the OS has had time to load drivers, etc.

	for (;;) {
		//dbg
// 		KB_LED1_ON; _delay_ms(200); KB_LED1_OFF; _delay_ms(200);  //dbg
		static int counter=0;
		if (counter == 0)
			_toggle_led3();
		counter++;
		if (counter >= 1000)
			counter = 0;
		///
		static uint8_t current_layer = 0;

		// swap `kb_is_pressed` and `kb_was_pressed`, then update
		bool (*temp)[KB_ROWS][KB_COLUMNS] = kb_was_pressed;
		kb_was_pressed = kb_is_pressed;
		kb_is_pressed = temp;

		kb_update_matrix(*kb_is_pressed);

		// call the appropriate function for each key, then send the report if
		// necessary
		for (uint8_t row=0; row<KB_ROWS; row++) {
			for (uint8_t col=0; col<KB_COLUMNS; col++) {
				bool is_pressed = (*kb_is_pressed)[row][col];
				bool was_pressed = (*kb_was_pressed)[row][col];
				if (is_pressed != was_pressed) {
					if (is_pressed) {
						kbfun_funptr_t press_function =
								kb_layout_press[current_layer][row][col];
						if (press_function) {
							(*press_function)(
									&kb_layout[current_layer][row][col],
									&current_layer, &row, &col );
						}
					} else {
						kbfun_funptr_t release_function =
								kb_layout_release[current_layer][row][col];
						if (release_function) {
							(*release_function)(
									&kb_layout[current_layer][row][col],
									&current_layer, &row, &col );
						}
					}

					usb_keyboard_send();
					_delay_ms(DEBOUNCE_TIME);
				}
			}
		}

		// update LEDs
// 		(keyboard_leds & (1<<0)) ? KB_LED1_ON : KB_LED1_OFF;  // num lock
// 		(keyboard_leds & (1<<1)) ? KB_LED2_ON : KB_LED2_OFF;  // caps lock
// 		(keyboard_leds & (1<<2)) ? KB_LED3_ON : KB_LED3_OFF;  // scroll lock
		#if 0  // not implemented right now
		(keyboard_leds & (1<<3)) ? KB_LED4_ON : KB_LED4_OFF;  // compose
		(keyboard_leds & (1<<4)) ? KB_LED5_ON : KB_LED5_OFF;  // kana
		#endif
	}

	return 0;
}

