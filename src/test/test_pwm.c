/* ----------------------------------------------------------------------------
 * Test the Teensy 2.0 PWM code (see `#include`s)
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include <util/delay.h>
#include <avr/io.h>


#define bool _Bool
#define true  1
#define false 0

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))

// LED control
#define KB_LED1_ON             (DDRB |=  (1<<5))
#define KB_LED1_OFF            (DDRB &= ~(1<<5))
#define KB_LED1_SET(n)         (OCR1A = (uint8_t)(n))
#define KB_LED1_SET_PERCENT(n) (OCR1A = (uint8_t)((n) * 0xFF))
#define KB_LED2_ON             (DDRB |=  (1<<6))
#define KB_LED2_OFF            (DDRB &= ~(1<<6))
#define KB_LED2_SET(n)         (OCR1B = (uint8_t)(n))
#define KB_LED2_SET_PERCENT(n) (OCR1B = (uint8_t)((n) * 0xFF))
#define KB_LED3_ON             (DDRB |=  (1<<7))
#define KB_LED3_OFF            (DDRB &= ~(1<<7))
#define KB_LED3_SET(n)         (OCR1C = (uint8_t)(n))
#define KB_LED3_SET_PERCENT(n) (OCR1C = (uint8_t)((n) * 0xFF))


int main(void) {
	CPU_PRESCALE(0);  // set for 16MHz

	// pwm init for keyboard LEDs
	// (see "PWM on ports OC1(A|B|C)" in "teensy-2-0.md")
	DDRB   |= 0b11100000;  // set B(7,6,5) as output
	TCCR1A  = 0b10101001;  // set and configure fast PWM
	TCCR1B  = 0b00001001;  // set and configure fast PWM


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

