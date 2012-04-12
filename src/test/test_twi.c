/* ----------------------------------------------------------------------------
 * Test for ACK on address write (with a Teensy 2.0 and I/O expander)
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

#include <avr/io.h>
#include <util/twi.h>
#include <util/delay.h>


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

void twi_init(void) {
	TWSR &= ~( (1<<TWPS1)|(1<<TWPS0) );
	TWBR = ((F_CPU / 100000) - 16) / 2;
// 	TWSR |= (1<<TWPS1)|(1<<TWPS0); //dbg
// 	TWBR = 0xFF; //dbg
}

uint8_t twi_start(void) {
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTA);
	while (!(TWCR & (1<<TWINT)));
	if ((TWSR & 0xF8) != TW_START)
		return TWSR & 0xF8;  // error
}

void twi_stop(void) {
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	while (TWCR & (1<<TWSTO));
}

uint8_t twi_send(uint8_t data) {
	TWDR = data;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	if ((TWSR & 0xF8) != TW_MT_SLA_ACK)
		return TWSR & 0xF8;  // error
}

// ----------------------------------------------------------------------------
// main
// ----------------------------------------------------------------------------

void main(void) {
	CPU_PRESCALE(CPU_16MHz);
	uint8_t ret;

	twi_init();

	for (uint8_t i=0;; i+=2) {  // try all even (write) addresses
		twi_start();
		ret = twi_send(i);  // i = address
		twi_stop();

		if (ret == 0x18)  // SLA+W sent; ACK received
			break;

		if (i == 0xFE)  // all done
			break;
	}

	// blink the return value
	// --- initial blink (get ready)
	blink_led(700, 200);
	// --- 1st hex number
	for (uint8_t i=0; i<(ret/0x10); i++) {
		blink_led(200, 100);
	}
	_delay_ms(400);
	// --- 2nd hex number
	for (uint8_t i=0; i<(ret%0x10); i++) {
		blink_led(200, 100);
	}
}

