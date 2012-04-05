/* ----------------------------------------------------------------------------
 * ergoDOX controller: MCP23018 specific code
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include <util/twi.h>

#include "lib/data-types.h"
#define TWI_FREQ 400000
#include "lib/teensy-2-0/twi.h"

#include "matrix.h"
#define MCP23018_h_INCLUDE_PRIVATE
#include "mcp23018.h"


// register addresses (see "mcp23018.md")
#define IODIRA 0x00  // i/o direction register
#define IODIRB 0x01
#define GPPUA  0x0C  // GPIO pull-up resistor register
#define GPPUB  0x0D
#define GPIOA  0x12  // general purpose i/o port register
#define GPIOB  0x13
#define OLATA  0x14  // output latch register
#define OLATB  0x15

// TWI aliases
#define TWI_ADDR_WRITE ( (MCP23018_TWI_ADDRESS<<1) | TW_WRITE )
#define TWI_ADDR_READ  ( (MCP23018_TWI_ADDRESS<<1) | TW_READ  )


/*
 * returns:
 * - success: 0
 * - failure: twi status code
 */
uint8_t mcp23018_init(void) {
	uint8_t ret;

	twi_init();

	// quick check to see if the device is responding;  if it is, we'll
	// assume things are going to work
	twi_start();
	ret = twi_send(TWI_ADDR_WRITE);
	if (ret) {
		twi_stop();
		return ret;
	}

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
	twi_send(GPIOA);
	twi_send(0b11111111);  //GPIOA
	twi_send(0b11111111);  //GPIOB
	
	twi_stop();

	return 0;  // success
}

/* returns:
 * - success: 0
 * - failure: twi status code
 */
#if KB_ROWS != 12 || KB_COLUMNS != 7
	#error "Expecting different keyboard dimensions"
#endif
uint8_t mcp23018_update_matrix(uint8_t matrix[KB_ROWS][KB_COLUMNS]) {
	uint8_t ret, data;

	// quick check to see if the device is responding;  if it is, we'll
	// assume things are going to work
	twi_start();
	ret = twi_send(TWI_ADDR_WRITE);
	if (ret) {
		twi_stop();
		return ret;
	}

	for (uint8_t row=0x6; row<=0xB; row++) {
		// set row low : 0
		twi_start();
		twi_send(TWI_ADDR_WRITE);
		twi_send(GPIOA);
		twi_send( 0b00111111 & ~(1<<(row-6)) );  // GPIOA

		// get column data
		twi_start();
		twi_send(TWI_ADDR_READ);
		twi_read(&data);  // GPIOB  TODO: confirm

		// update matrix
		for (uint8_t col=0; col<=6; col++)
			matrix[row][col] = !( data & (1<<col) );
	}

	twi_stop();

	return 0;  // success
}

