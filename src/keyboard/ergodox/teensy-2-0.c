/* ----------------------------------------------------------------------------
 * ergoDOX controller: Teensy 2.0 specific code
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include <avr/io.h>

#define TEENSY_2_0_h_INCLUDE_PRIVATE
#include "teensy-2-0.h"


// processor frequency (from <http://www.pjrc.com/teensy/prescaler.html>)
#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define CPU_16MHz       0x00
#define CPU_8MHz        0x01
#define CPU_4MHz        0x02
#define CPU_2MHz        0x03
#define CPU_1MHz        0x04
#define CPU_500kHz      0x05
#define CPU_250kHz      0x06
#define CPU_125kHz      0x07
#define CPU_62kHz       0x08


/* returns:
 * - success: 0
 * + will never return failure
 */
uint8_t teensy_init(void) {
	CPU_PRESCALE(CPU_16MHz);  // speed should match F_CPU in makefile

	// unused pins
	DDRB  &= ~0b00001110;  // set B(3,2,1) as input
	PORTB |=  0b00001110;  // set B(3,2,1) internal pull-up enabled
	DDRD  &= ~0b01110000;  // set D(6,5,4) as input
	PORTD |=  0b00110000;  // set D(  5,4) internal pull-up enabled
	DDRE  &= ~0b01000000;  // set E(6)     as input
	PORTE |=  0b01000000;  // set E(6)     internal pull-up enabled

	// LEDs (see "PWM on ports OC1(A|B|C)" in "teensy-2-0.md")
	DDRB   |= 0b11100000;  // set B(7,6,5) as output
	TCCR1A  = 0b10101001;  // set and configure fast PWM
	TCCR1B  = 0b00001001;  // set and configure fast PWM

	// rows
	DDRF  |=  0b11110011;  // set F(7,6,5,4,1,0) as output
	PORTF |=  0b11110011;  // set F(7,6,5,4,1,0) drive high

	// columns
	DDRB  &= ~0b00010001;  // set B(4,0)   as input
	PORTB |=  0b00010001;  // set B(4,0)   internal pull-up enabled
	DDRC  &= ~0b11000000;  // set C(7,6)   as input
	PORTC |=  0b11000000;  // set C(7,6)   internal pull-up enabled
	DDRD  &= ~0b10001100;  // set D(7,3,2) as input
	PORTD |=  0b10001100;  // set D(7,3,2) internal pull-up enabled

	// I2C (TWI)
	// on pins D(1,0); leave them alone here, so the TWI library can do as
	// it wishes

	return 0;  // success
}

