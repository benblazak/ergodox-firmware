/* ----------------------------------------------------------------------------
 * ergoDOX controller: MCP23018 specific code
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

// TODO: still working on all this
// - need to separate the 'check if everything's all right' function, i think
// - do more error checking in update_matrix() ?
// - does update_matrix() really need a helper function? can it be conditional?
// - [and lots of stuff, just need to clean it up] :)

#include <util/twi.h>

#include "lib/data-types.h"
#include "lib/teensy-2-0/twi.h"  // `TWI_FREQ` defined in "teensy-2-0.c"

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


// ----------------------------------------------------------------------------

/* returns:
 * - success: 0
 * - failure: twi status code
 *
 * notes:
 * - this checks whether the device is initialized by reading from it.  not the
 *   most efficient method, but easy and fairly reliable.
 */
static uint8_t _init(bool release_twi_bus) {
	static bool initialized;
	uint8_t ret, data;

	// check for errors and previous initialization

	twi_start();
	ret = twi_send(TWI_ADDR_WRITE);

	if (ret) goto out;  // address write failed (no ACK)

	twi_send(OLATA);
	twi_start();
	twi_send(TWI_ADDR_READ);
	ret = twi_read(&data);

	if (ret) goto out;  // read failed
	if (data == 0xFF) goto out;  // already initialized (OLATA == 0xFF)

	// initialize things, if we need to and we can

	// set pin direction
	// - unused  : input  : 1
	// - rows    : output : 0
	// - columns : input  : 1
	twi_start();
	twi_send(TWI_ADDR_WRITE);
	twi_send(IODIRA);
	twi_send(0b11000000);  // IODIRA
	twi_send(0b11111111);  // IODIRB

	// set pull-up
	// - unused  : on  : 1
	// - rows    : off : 0
	// - columns : on  : 1
	twi_start();
	twi_send(TWI_ADDR_WRITE);
	twi_send(GPPUA);
	twi_send(0b11000000);  // GPPUA
	twi_send(0b11111111);  // GPPUB

	// set logical value (doesn't matter on inputs)
	// - unused  : high (hi-Z) : 1
	// - rows    : high (hi-Z) : 1
	// - columns : high (hi-Z) : 1
	twi_start();
	twi_send(TWI_ADDR_WRITE);
	twi_send(OLATA);
	twi_send(0b11111111);  //OLATA
	twi_send(0b11111111);  //OLATB

out:
	if (release_twi_bus)
		twi_stop();

	if (ret) initialized = false;
	else     initialized = true;

	return ret;
}

// ----------------------------------------------------------------------------

/* returns:
 * - success: 0
 * - failure: twi status code
 */
uint8_t mcp23018_init(void) {
	return _init(true);
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

	// initialize things if necessary
	ret = _init(false);

	// if there was an error
	if (ret) {
		// clear the matrix
		for (uint8_t row=0x6; row<=0xB; row++)
			for (uint8_t col=0; col<=6; col++)
				matrix[row][col] = 0;

		// release the twi bus and return
		twi_stop();
		return ret;
	}

	// update our part of the matrix
	for (uint8_t row=0x6; row<=0xB; row++) {
		// set active row low : 0
		// set other rows high (hi-Z) : 1
		twi_start();
		twi_send(TWI_ADDR_WRITE);
		twi_send(OLATA);
		twi_send( 0b11111111 & ~(1<<(row-6)) );  // OLATA

		// get column data
		twi_start();
		twi_send(TWI_ADDR_WRITE);
		twi_send(GPIOB);
		twi_send(TWI_ADDR_READ);
		twi_read(&data);  // GPIOB

		// update matrix
		for (uint8_t col=0; col<=6; col++)
			matrix[row][col] = !( data & (1<<col) );
	}

	// set all rows high (hi-Z) : 1
	twi_start();
	twi_send(TWI_ADDR_WRITE);
	twi_send(GPIOA);
	twi_send(0b11111111);

	// release the twi bus and return
	twi_stop();
	return 0;  // success
}

