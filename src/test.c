#include <stdio.h>
#include <util/delay.h>

#include "lib-other/pjrc/blinky/print.h"
#include "lib-other/pjrc/blinky/usb_debug_only.h"

#define TEENSY_2_0_h_INCLUDE_PRIVATE
#include "keyboard/ergodox/teensy-2-0.h"

int test_i2c(void);
int test_kb_teensy(void);
int main(void);

// ----------------------------------------------------------------------------

int main(void) {
	test_i2c();
	print("--------------");
	test_kb_teensy();
}

// ----------------------------------------------------------------------------

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

