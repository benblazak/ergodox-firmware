/* ----------------------------------------------------------------------------
 * Test TWI write (with a Teensy 2.0 and I/O expander)
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

#include <avr/io.h>
#include <util/twi.h>
#include <util/delay.h>

#define TWI_FREQ 400000
#include "../lib/teensy-2-0/twi.c"


// processor frequency (from <http://www.pjrc.com/teensy/prescaler.html>)
#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define CPU_16MHz       0x00


// ----------------------------------------------------------------------------
// helper functions
// ----------------------------------------------------------------------------

#define blink_led(time1, time2) { \
	/* Teensy 2.0 onboard LED on PD6
	   on high, off low */ \
	PORTD |=  (1<<6); \
	_delay_ms(time1); \
	PORTD &= ~(1<<6); \
	_delay_ms(time2); \
}


// ---------------------------------------------------------------------------- // TWI
// ----------------------------------------------------------------------------

#define IODIRA 0x00
#define IODIRB 0x01
#define GPPUA  0x0C
#define GPPUB  0x0D
#define GPIOA  0x12
#define GPIOB  0x13
#define OLATA  0x14
#define OLATB  0x15

#define TWI_ADDR_WRITE (0b0100000<<1)|TW_WRITE
#define TWI_ADDR_READ (0b0100000<<1)|TW_READ


// ----------------------------------------------------------------------------
// main
// ----------------------------------------------------------------------------

/* notes:
 * - won't work without the `twi_stop()`s after each block
 */
int main(void) {
	CPU_PRESCALE(CPU_16MHz);

	twi_init();

	// set all gpio pins as:

	// output
	twi_start();
	twi_send(TWI_ADDR_WRITE);
	twi_send(IODIRA);
	twi_send(0);
	twi_send(0);
	twi_stop();

	// with pull-up
	twi_start();
	twi_send(TWI_ADDR_WRITE);
	twi_send(GPPUA);
	twi_send(0xff);
	twi_send(0xff);
	twi_stop();

	// logical 1
	twi_start();
	twi_send(TWI_ADDR_WRITE);
	twi_send(OLATA);
	twi_send(0xff);
	twi_send(0xff);
	twi_stop();

	return 0;
}

