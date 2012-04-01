/* ----------------------------------------------------------------------------
 * Test the Teensy 2.0 PWM code (see `#include`s)
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include <util/delay.h>

#define TEENSY_2_0_h_INCLUDE_PRIVATE
#include "../keyboard/ergodox/teensy-2-0.h"
#include "../keyboard/ergodox/teensy-2-0.c"


#define bool uint8_t
#define true  1
#define false 0


void main(void) {
	teensy_init();

	for (uint8_t i=0; i<3; i++) {
		KB_LED1_SET(0x10);
		KB_LED2_SET(0x20);
		KB_LED3_SET(0xFF);
		_delay_ms(500);
		KB_LED1_SET(0x20);
		KB_LED2_SET(0xFF);
		KB_LED3_SET(0x10);
		_delay_ms(500);
		KB_LED1_SET(0xFF);
		KB_LED2_SET(0x10);
		KB_LED3_SET(0x20);
		_delay_ms(500);
	}

	for (uint8_t i=0; i<2; i++) {
		KB_LED1_OFF;
		KB_LED2_OFF;
		KB_LED3_OFF;
		_delay_ms(500);
		KB_LED1_ON;
		KB_LED2_ON;
		KB_LED3_ON;
		_delay_ms(500);
	}

	bool counting_up = true;
	for (uint8_t i=0;;) {
		(counting_up) ? i++ : i--;
		if (i == 0xFF)
			counting_up = false;
		else if (i == 0)
			counting_up = true;

		KB_LED1_SET(i/2);
		KB_LED2_SET(i/2);
		KB_LED3_SET(i/2);
		_delay_ms(10);
	}
}

