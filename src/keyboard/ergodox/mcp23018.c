/* ----------------------------------------------------------------------------
 * ergoDOX controller: MCP23018 specific code
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

// TODO: this is not working yet

#if 0  // this is not the one we want; but it has all the right info
#include "lib-other/peter-fleury/i2cmaster/i2cmaster.h"

// so we can say `TWI_ADDRESS|I2C_WRITE`
#define TWI_ADDRESS (MCP23018_TWI_ADDRESS<<1)

uint8_t mcp23018_ready;  // false

uint8_t mcp23018_init(void) {
	// declare vars
	uint8_t error;

	// see if the device is ready
	// - success: set `mcp23018_ready = true` and continue initializing
	// - failure: return `error`; we can try again later
	error = i2c_start(TWI_ADDRESS|I2C_WRITE);
	if(error) {
		return error;
	} else {
		mcp23018_ready = true;
		i2c_stop();  // release bus
	}

	// set pin direction
	// - unused  : input  : 1
	// - rows    : output : 0
	// - columns : input  : 1
	i2c_start_wait(TWI_ADDRESS|I2C_WRITE);
	i2c_write(IODIRA);      // start register address
	i2c_write(0b11000000);  // IODIRA
	i2c_write(0b11111111);  // IODIRB
	i2c_stop();

	// set pull-up
	// - unused  : on : 1
	// - rows    : on : 1
	// - columns : on : 1
	i2c_start_wait(TWI_ADDRESS|I2C_WRITE);
	i2c_write(GPPUA);       // start register address
	i2c_write(0b11111111);  // GPPUA
	i2c_write(0b11111111);  // GPPUB
	i2c_stop();

	// set output pins high
	// - rows  : high : 1
	// - other : low  : 0 (or ignored)
	i2c_start_wait(TWI_ADDRESS|I2C_WRITE);
	i2c_write(OLATA);       // start register address
	i2c_write(0b00111111);  // OLATA
	i2c_stop();

	return 0;  // success
}
#endif


#include <util/delay.h>
#include <util/twi.h>
// #include "lib-other/arduino/arduino/libraries/Wire/utility/twi.h"
#include "lib-other/pjrc/blinky/print.h"
#include "lib-other/pjrc/blinky/usb_debug_only.h"

#define MCP23018_h_INCLUDE_PRIVATE
#include "mcp23018.h"
#include "teensy-2-0.h"
#include "lib/data-types.h"


// register addresses (see "mcp23018.md")
#define IODIRA 0x00  // i/o direction register
#define IODIRB 0x01
#define GPPUA  0x0C  // GPIO pull-up resistor register
#define GPPUB  0x0D
#define GPIOA  0x12  // general purpose i/o port register
#define GPIOB  0x13
#define OLATA  0x14  // output latch register
#define OLATB  0x15

static void twi_init(void) {
// 	TWSR &= ~( (1<<TWPS1)|(1<<TWPS0) );
	TWSR |= (1<<TWPS1)|(1<<TWPS0); //dbg
// 	TWBR = ((F_CPU / 100000) - 16) / 2;
	TWBR = 0xFF; //dbg
// 	TWCR = (1<<TWEA)|(1<<TWEN);
}

static uint8_t twi_start(void) {
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	if ((TWSR & 0xF8) != TW_START)
		return TWSR & 0xF8;  // error
}

static void twi_stop(void) {
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	while (!(TWCR & (1<<TWSTO)));
}

static uint8_t twi_send(uint8_t data) {
	TWDR = data;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	if ((TWSR & 0xF8) != TW_MT_SLA_ACK)
		return TWSR & 0xF8;  // error
}

static void hid_print_number_binary(uint8_t data) {
	print("0b");
	for(int8_t i=7; i>=0; i--) {
		(data & (1<<i))
			? pchar('1')
			: pchar('0');
	}
}
static void hid_print_number_hex(uint8_t data) {
	print("0x"); phex(data);
}
static uint8_t try_address(uint8_t address) {
	uint8_t error;

	print("\naddress "); hid_print_number_binary(address);
	twi_start();
	error = twi_send(address);
	twi_stop();
	print("    error "); hid_print_number_hex(error);

	return error;
}

uint8_t mcp23018_init(void) {
	uint8_t error, address;

	twi_init();

	// send address, wait
	for (uint8_t i=0b000; i<=0b111; i++) {
		address = (0b0100<<4)|(i<<1)|TW_WRITE;
		error = try_address(address);
	}
	address = 0;
	error = try_address(address);
// 	for (uint8_t i=0b0000000; i<=0b1111111; i++) {
// 		address = (i<<1)|TW_WRITE;
// 		error = try_address(address);
// 		if (! error == 0x20)
// 			return error;
// 	}


// 	uint8_t data[3];
//
// 	twi_init();
// 	twi_setAddress(MCP23018_TWI_ADDRESS);
// 
// 	data[0] = IODIRA;
// 	data[1] = 0b00000000;  // IODIRA
// 	error = twi_writeTo(MCP23018_TWI_ADDRESS, data, 2, true);
// 
// 	data[0] = OLATA;       // start register address
// 	data[1] = 0b00000000;  // OLATA
// 	twi_writeTo(MCP23018_TWI_ADDRESS, data, 2, true);

	return error;
}
