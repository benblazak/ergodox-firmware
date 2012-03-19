#include <util/delay.h>
#include "teensy-2-0.h"

int main(void) {
	teensy_init();

	TEENSY_LED1_ON;
	TEENSY_LED2_ON;
	TEENSY_LED3_ON;

	for(uint8_t i=0;;i++) {
		TEENSY_LED1_SET( (i+(3*0xFF/2/3)) % 0xFF/2 );
		TEENSY_LED2_SET( (i+(2*0xFF/2/3)) % 0xFF/2 );
		TEENSY_LED3_SET( (i+(1*0xFF/2/3)) % 0xFF/2 );

// 		counting_up
// 			? (i == 0xFF ? counting_up = 0 : i++)
// 			: (i == 0x00 ? counting_up = 1 : i--);

		_delay_ms(10);
	}

	return 0;
}

