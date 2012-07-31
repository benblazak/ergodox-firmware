/* ----------------------------------------------------------------------------
 * Very simple Teensy 2.0 TWI library : code
 *
 * - This is mostly straight from the datasheet, section 20.6.6, figure 20-11
 *   (the code example in C), and section 20.8.1, figure 20-12
 * - Also see the documentation for `<util/twi.h>` at
 *   <http://www.nongnu.org/avr-libc/user-manual/group__util__twi.html#ga8d3aca0acc182f459a51797321728168>
 *
 * Some other (more complete) TWI libraries for the Teensy 2.0 (and other Atmel
 * processors):
 * - [i2cmaster] (http://homepage.hispeed.ch/peterfleury/i2cmaster.zip)
 *   - written by [peter-fleury] (http://homepage.hispeed.ch/peterfleury/)
 * - [the arduino twi library]
 *   (https://github.com/arduino/Arduino/tree/master/libraries/Wire/utility)
 *   - look for an older version if you need one that doesn't depend on all the
 *     other Arduino stuff
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


// ----------------------------------------------------------------------------
// conditional compile
#if MAKEFILE_BOARD == teensy-2-0
// ----------------------------------------------------------------------------


#include <util/twi.h>
#include "./teensy-2-0.h"

// ----------------------------------------------------------------------------

void twi_init(void) {
	// set the prescaler value to 0
	TWSR &= ~( (1<<TWPS1)|(1<<TWPS0) );
	// set the bit rate
	// - TWBR should be 10 or higher (datasheet section 20.5.2)
	// - TWI_FREQ should be 400000 (400kHz) max (datasheet section 20.1)
	TWBR = ((F_CPU / TWI_FREQ) - 16) / 2;
}

uint8_t twi_start(void) {
	// send start
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTA);
	// wait for transmission to complete
	while (!(TWCR & (1<<TWINT)));
	// if it didn't work, return the status code (else return 0)
	if ( (TW_STATUS != TW_START) &&
	     (TW_STATUS != TW_REP_START) )
		return TW_STATUS;  // error
	return 0;  // success
}

void twi_stop(void) {
	// send stop
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	// wait for transmission to complete
	while (TWCR & (1<<TWSTO));
}

uint8_t twi_send(uint8_t data) {
	// load data into the data register
	TWDR = data;
	// send data
	TWCR = (1<<TWINT)|(1<<TWEN);
	// wait for transmission to complete
	while (!(TWCR & (1<<TWINT)));
	// if it didn't work, return the status code (else return 0)
	if ( (TW_STATUS != TW_MT_SLA_ACK)  &&
	     (TW_STATUS != TW_MT_DATA_ACK) &&
	     (TW_STATUS != TW_MR_SLA_ACK) )
		return TW_STATUS;  // error
	return 0;  // success
}

uint8_t twi_read(uint8_t * data) {
	// read 1 byte to TWDR, send ACK
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	// wait for transmission to complete
	while (!(TWCR & (1<<TWINT)));
	// set data variable
	*data = TWDR;
	// if it didn't work, return the status code (else return 0)
	if (TW_STATUS != TW_MR_DATA_ACK)
		return TW_STATUS;  // error
	return 0;  // success
}


// ----------------------------------------------------------------------------
#endif
// ----------------------------------------------------------------------------

