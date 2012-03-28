#include <stdio.h>
#include <util/delay.h>

#include "lib-other/pjrc/blinky/print.h"
#include "lib-other/pjrc/blinky/usb_debug_only.h"

#include "lib/data-types.h"

#define TEENSY_2_0_h_INCLUDE_PRIVATE
#include "keyboard/ergodox/teensy-2-0.h"

int blink_leds(void);
int test_i2c(void);
int test_kb_teensy(void);
int main(void);

// ----------------------------------------------------------------------------

int main(void) {
	teensy_init();

	KB_LED1_SET_PERCENT(.03);
	KB_LED2_SET_PERCENT(.03);
	KB_LED3_SET_PERCENT(.03);

// 	blink_leds();
// 	print("--------------");
	test_i2c();
	print("--------------");
	test_kb_teensy();
}

// ----------------------------------------------------------------------------

int blink_leds(void) {
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

int test_i2c(void) {
	usb_init();
	_delay_ms(500);  // just to be safe

	uint8_t ret;

	uint8_t len;
	char str[10];

	print("\nhello");

	ret = teensy_init();
	print("\nteensy_init() returned: 0x"); phex(ret);

	ret = mcp23018_init();
	print("\nmcp23018_init() returned: 0x"); phex(ret);

	usb_debug_flush_output();
	return 0;
}

// ----------------------------------------------------------------------------

int test_kb_teensy(void) {
}

