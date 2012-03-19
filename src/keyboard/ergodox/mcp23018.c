/* ----------------------------------------------------------------------------
 * ergoDOX controller: MCP23018 specific code
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak
 * Released under The MIT License (MIT) (see "license.md") at
 * <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#define TWI_ADDRESS MCP23018_TWI_ADDRESS  // from header file

#define True  ((uint8_t)1)
#define False ((uint8_t)0)

// register addresses (see "mcp23018.md")
#define IODIRA 0x00  // i/o direction register
#define IODIRB 0x01
#define GPPUA  0x0C  // GPIO pull-up resistor register
#define GPPUB  0x0D
#define GPIOA  0x12  // general purpose i/o port register
#define GPIOB  0x13
#define OLATA  0x14  // output latch register
#define OLATB  0x15


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "lib/arduino/twi.h"

#include "mcp23018.h"


void mcp23018_init(void) {
	uint8_t data[3];

	// set pin direction
	// - unused  : input  : 1
	// - rows    : output : 0
	// - columns : input  : 1
	data[0] = IODIRA;      // start register address
	data[1] = 0b11000000;  // IODIRA
	data[2] = 0b11111111;  // IODIRB
	twi_writeTo(TWI_ADDRESS, data, 3, True);

	// set pull-up
	// - unused  : on  : 1
	// - rows    : off : 0
	// - columns : on  : 1
	data[0] = GPPUA;       // start register address
	data[1] = 0b11000000;  // GPPUA
	data[2] = 0b11111111;  // GPPUB
	twi_writeTo(TWI_ADDRESS, data, 3, True);

	// set output pins high
	// - rows  : high : 1
	// - other : low  : 0 (or ignored)
	data[0] = OLATA;       // start register address
	data[1] = 0b00111111;  // OLATA
	twi_writeTo(TWI_ADDRESS, data, 2, True);
}

