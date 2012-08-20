/* ----------------------------------------------------------------------------
 * ergoDOX : controller: MCP23018 specific code
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include <stdbool.h>
#include <stdint.h>
#include <util/twi.h>
#include "../../../lib/twi.h"  // `TWI_FREQ` defined in "teensy-2-0.c"
#include "../options.h"
#include "../matrix.h"
#include "./mcp23018--functions.h"

// ----------------------------------------------------------------------------

// check options
#if  (MCP23018__DRIVE_ROWS && MCP23018__DRIVE_COLUMNS)	\
 || !(MCP23018__DRIVE_ROWS || MCP23018__DRIVE_COLUMNS)
	#error "See 'Pin drive direction' in 'options.h'"
#endif

// ----------------------------------------------------------------------------

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
 * - `twi_stop()` must be called *exactly once* for each twi block, the way
 *   things are currently set up.  this may change in the future.
 */
uint8_t mcp23018_init(void) {
	uint8_t ret;

	// set pin direction
	// - unused  : input  : 1
	// - input   : input  : 1
	// - driving : output : 0
	twi_start();
	ret = twi_send(TWI_ADDR_WRITE);
	if (ret) goto out;  // make sure we got an ACK
	twi_send(IODIRA);
	#if MCP23018__DRIVE_ROWS
		twi_send(0b11111111);  // IODIRA
		twi_send(0b11000000);  // IODIRB
	#elif MCP23018__DRIVE_COLUMNS
		twi_send(0b10000000);  // IODIRA
		twi_send(0b11111111);  // IODIRB
	#endif
	twi_stop();

	// set pull-up
	// - unused  : on  : 1
	// - input   : on  : 1
	// - driving : off : 0
	twi_start();
	ret = twi_send(TWI_ADDR_WRITE);
	if (ret) goto out;  // make sure we got an ACK
	twi_send(GPPUA);
	#if MCP23018__DRIVE_ROWS
		twi_send(0b11111111);  // GPPUA
		twi_send(0b11000000);  // GPPUB
	#elif MCP23018__DRIVE_COLUMNS
		twi_send(0b10000000);  // GPPUA
		twi_send(0b11111111);  // GPPUB
	#endif
	twi_stop();

	// set logical value (doesn't matter on inputs)
	// - unused  : hi-Z : 1
	// - input   : hi-Z : 1
	// - driving : hi-Z : 1
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
#if KB_ROWS != 6 || KB_COLUMNS != 14
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
		for (uint8_t row=0; row<=5; row++)
			for (uint8_t col=0; col<=6; col++)
				matrix[row][col] = 0;

		return ret;
	}


	// --------------------------------------------------------------------
	// update our part of the matrix

	#if MCP23018__DRIVE_ROWS
		for (uint8_t row=0; row<=5; row++) {
			// set active row low  : 0
			// set other rows hi-Z : 1
			twi_start();
			twi_send(TWI_ADDR_WRITE);
			twi_send(GPIOB);
			twi_send( 0xFF & ~(1<<(5-row)) );
			twi_stop();

			// read column data
			twi_start();
			twi_send(TWI_ADDR_WRITE);
			twi_send(GPIOA);
			twi_start();
			twi_send(TWI_ADDR_READ);
			twi_read(&data);
			twi_stop();

			// update matrix
			for (uint8_t col=0; col<=6; col++) {
				matrix[row][col] = !( data & (1<<col) );
			}
		}

		// set all rows hi-Z : 1
		twi_start();
		twi_send(TWI_ADDR_WRITE);
		twi_send(GPIOB);
		twi_send(0xFF);
		twi_stop();

	#elif MCP23018__DRIVE_COLUMNS
		for (uint8_t col=0; col<=6; col++) {
			// set active column low  : 0
			// set other columns hi-Z : 1
			twi_start();
			twi_send(TWI_ADDR_WRITE);
			twi_send(GPIOA);
			twi_send( 0xFF & ~(1<<col) );
			twi_stop();

			// read row data
			twi_start();
			twi_send(TWI_ADDR_WRITE);
			twi_send(GPIOB);
			twi_start();
			twi_send(TWI_ADDR_READ);
			twi_read(&data);
			twi_stop();

			// update matrix
			for (uint8_t row=0; row<=5; row++) {
				matrix[row][col] = !( data & (1<<(5-row)) );
			}
		}

		// set all columns hi-Z : 1
		twi_start();
		twi_send(TWI_ADDR_WRITE);
		twi_send(GPIOA);
		twi_send(0xFF);
		twi_stop();

	#endif

	// /update our part of the matrix
	// --------------------------------------------------------------------

	return ret;  // success
}

