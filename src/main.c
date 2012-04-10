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

//dbg
int main(void) {
	kb_init();  // does controller initialization too

	usb_init();
	while (!usb_configured());
	_delay_ms(1000);  // make sure the OS has had time to load drivers, etc.

	for (;;) {
// 		int current_layer = 0;

		KB_LED1_ON; _delay_ms(200); KB_LED1_OFF; _delay_ms(200);
		KB_LED1_ON; _delay_ms(200); KB_LED1_OFF; _delay_ms(200);

// 		for (int row=0; row<KB_ROWS; row++)
// 			for (int col=0; col<KB_COLUMNS; col++)
// 				(*kb_is_pressed)[row][col] = 0;

// 		kb_update_matrix(*kb_is_pressed);
// 
// 		for (int row=0; row<KB_ROWS; row++) {
// 			for (int col=0; col<KB_COLUMNS; col++) {
// 				if ((*kb_is_pressed)[row][col]) {
// 					usb_keyboard_press(kb_layout[current_layer][row][col], 0);
// 				}
// 			}
// 		}
	}
}

#if 0 //dbg
int main(void) {
	kb_init();  // does controller initialization too

	usb_init();
	while (!usb_configured());
	_delay_ms(1000);  // make sure the OS has had time to load drivers, etc.

	for (;;) {
		static uint8_t current_layer = 0;

		// swap `kb_is_pressed` and `kb_was_pressed`, then update
		bool (*temp)[KB_ROWS][KB_COLUMNS] = kb_was_pressed;
		kb_was_pressed = kb_is_pressed;
		kb_is_pressed = temp;

		kb_update_matrix(*kb_is_pressed);

		// call the appropriate function for each key, then send the report
		for (uint8_t row=0; row<KB_ROWS; row++)
			for (uint8_t col=0; col<KB_COLUMNS; col++)
				if (*kb_is_pressed[row][col] != *kb_was_pressed[row][col]) {
					if (!*kb_is_pressed[row][col])
						if (*kb_layout_press[current_layer][row][col])
							(*kb_layout_press[current_layer][row][col])(
									&kb_layout[current_layer][row][col],
									&current_layer, &row, &col );
					} else
						if (*kb_layout_release[current_layer][row][col])
							(*kb_layout_release[current_layer][row][col])(
									&kb_layout[current_layer][row][col],
									&current_layer, &row, &col );
				}

		usb_keyboard_send();

		// update LEDs
		(keyboard_leds & (1<<0)) ? KB_LED1_ON : KB_LED1_OFF;  // num lock
		(keyboard_leds & (1<<1)) ? KB_LED2_ON : KB_LED2_OFF;  // caps lock
		(keyboard_leds & (1<<2)) ? KB_LED3_ON : KB_LED3_OFF;  // scroll lock
#if 0  // not implemented right now
		(keyboard_leds & (1<<3)) ? KB_LED4_ON : KB_LED4_OFF;  // compose
		(keyboard_leds & (1<<4)) ? KB_LED5_ON : KB_LED5_OFF;  // kana
#endif
	}

	return 0;
}
#endif

