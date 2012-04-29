/* ----------------------------------------------------------------------------
 * ergoDOX controller: MCP23018 specific code
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include <util/twi.h>
#include "lib/data-types.h"
#include "lib/twi.h"  // `TWI_FREQ` defined in "teensy-2-0.c"

#define KEYBOARD_INCLUDE_PRIVATE
#include "matrix.h"
#include "mcp23018.h"


// register addresses (see "mcp23018.md")
#define IODIRA 0x00  // i/o direction register
#define IODIRB 0x01
#define GPPUA  0x0C  // GPIO pull-up resistor register
#define GPPUB  0x0D
#define GPIOA  0x12  // general purpose i/o port register (write modifies OLAT)
#define GPIOB  0x13
#define OLATA  0x14  // output latch register
#define OLATB  0x15

// TWI aliases
#define TWI_ADDR_WRITE ( (MCP23018_TWI_ADDRESS<<1) | TW_WRITE )
#define TWI_ADDR_READ  ( (MCP23018_TWI_ADDRESS<<1) | TW_READ  )


/* returns:
 * - success: 0
 * - failure: twi status code
 *
 * notes:
 * - `twi_stop()` must be called *exactly once* for each twi block, the way
 *   things are currently set up.  this may change in the future.
 */
uint8_t mcp23018_init(void) {
	uint8_t ret;

	// set pin direction
	// - unused  : input  : 1
	// - rows    : output : 0
	// - columns : input  : 1
	twi_start();
	ret = twi_send(TWI_ADDR_WRITE);
	if (ret) goto out;  // make sure we got an ACK
	twi_send(IODIRA);
	twi_send(0b11000000);  // IODIRA
	twi_send(0b11111111);  // IODIRB
	twi_stop();

	// set pull-up
	// - unused  : on  : 1
	// - rows    : off : 0
	// - columns : on  : 1
	twi_start();
	ret = twi_send(TWI_ADDR_WRITE);
	if (ret) goto out;  // make sure we got an ACK
	twi_send(GPPUA);
	twi_send(0b11000000);  // GPPUA
	twi_send(0b11111111);  // GPPUB
	twi_stop();

	// set logical value (doesn't matter on inputs)
	// - unused  : high (hi-Z) : 1
	// - rows    : high (hi-Z) : 1
	// - columns : high (hi-Z) : 1
	twi_start();
	ret = twi_send(TWI_ADDR_WRITE);
	if (ret) goto out;  // make sure we got an ACK
	twi_send(OLATA);
	twi_send(0b11111111);  //OLATA
	twi_send(0b11111111);  //OLATB

out:
	twi_stop();
	return ret;
}

/* returns:
 * - success: 0
 * - failure: twi status code
 */
#if KB_ROWS != 12 || KB_COLUMNS != 7
	#error "Expecting different keyboard dimensions"
#endif
uint8_t mcp23018_update_matrix(bool matrix[KB_ROWS][KB_COLUMNS]) {
	uint8_t ret, data;

	// initialize things, just to make sure
	// - it's not appreciably faster to skip this, and it takes care of the
	//   case when the i/o expander isn't plugged in during the first
	//   init()
	ret = mcp23018_init();

	// if there was an error
	if (ret) {
		// clear our part of the matrix
		for (uint8_t row=0x6; row<=0xB; row++)
			for (uint8_t col=0; col<=6; col++)
				matrix[row][col] = 0;

		return ret;
	}

	// update our part of the matrix
	for (uint8_t row=0x6; row<=0xB; row++) {
		// set active row low : 0
		// set other rows high (hi-Z) : 1
		twi_start();
		twi_send(TWI_ADDR_WRITE);
		twi_send(OLATA);
		twi_send( 0b11111111 & ~(1<<(row-6)) );
		twi_stop();

		// read column data
		twi_start();
		twi_send(TWI_ADDR_WRITE);
		twi_send(GPIOB);
		twi_start();
		twi_send(TWI_ADDR_READ);
		twi_read(&data);
		twi_stop();

		// update matrix
		for (uint8_t col=0; col<=6; col++)
			matrix[row][col] = !( data & (1<<col) );
	}

	// set all rows high (hi-Z) : 1
	twi_start();
	twi_send(TWI_ADDR_WRITE);
	twi_send(GPIOA);
	twi_send(0b11111111);
	twi_stop();

	return ret;  // success
}

