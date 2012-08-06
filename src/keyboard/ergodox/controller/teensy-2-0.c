/* ----------------------------------------------------------------------------
 * ergoDOX : controller: Teensy 2.0 specific code
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


// for "lib/twi.h"
#define TWI_FREQ 400000

#include <stdbool.h>
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "../../../lib/twi.h"
#include "../matrix.h"
#include "./teensy-2-0--functions.h"
#include "./teensy-2-0--led.h"

// ----------------------------------------------------------------------------

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


/* pin macros
 * - note: you can move the `UNUSED`, `ROW`, and `COLUMN` pins around, but be
 *   sure to keep the set of all the pins listed constant.  other pins are not
 *   movable, and either are referenced explicitly or have macros defined for
 *   them elsewhere.
 * - note: if you change pin assignments, please be sure to update
 *   "teensy-2-0.md", and the '.svg' circuit diagram.
 */

// --- helpers
#define _teensypin_write(register, operation, pin_letter, pin_number)	\
	((register##pin_letter) operation (1<<(pin_number)))
#define teensypin_write(register, operation, pin) do {		\
	_teensypin_write(register, operation, pin);		\
	_delay_us(1);  /* allow pins time to stabilize */	\
	} while(0)

#define _teensypin_read(pin_letter, pin_number)	\
	((PIN##pin_letter) & (1<<(pin_number)))
#define teensypin_read(pin)	\
	_teensypin_read(pin)

#define teensypin_write_all_unused(register, operation)			\
	do {								\
		teensypin_write(register, operation, UNUSED_0);		\
		teensypin_write(register, operation, UNUSED_1);		\
		teensypin_write(register, operation, UNUSED_2);		\
		teensypin_write(register, operation, UNUSED_3);		\
		teensypin_write(register, operation, UNUSED_4); }	\
	while(0)

#define teensypin_write_all_row(register, operation)		\
	do {							\
		teensypin_write(register, operation, ROW_0);	\
		teensypin_write(register, operation, ROW_1);	\
		teensypin_write(register, operation, ROW_2);	\
		teensypin_write(register, operation, ROW_3);	\
		teensypin_write(register, operation, ROW_4);	\
		teensypin_write(register, operation, ROW_5); }	\
	while(0)

#define teensypin_write_all_column(register, operation)			\
	do {								\
		teensypin_write(register, operation, COLUMN_0);		\
		teensypin_write(register, operation, COLUMN_1);		\
		teensypin_write(register, operation, COLUMN_2);		\
		teensypin_write(register, operation, COLUMN_3);		\
		teensypin_write(register, operation, COLUMN_4);		\
		teensypin_write(register, operation, COLUMN_5);		\
		teensypin_write(register, operation, COLUMN_6); }	\
	while(0)

#define SET |=
#define CLEAR &=~

// --- unused
#define UNUSED_0 C, 7
#define UNUSED_1 D, 7
#define UNUSED_2 D, 4  // hard to use with breadboard (on the end)
#define UNUSED_3 D, 5  // hard to use with breadboard (on the end)
#define UNUSED_4 E, 6  // hard to use with breadboard (internal)

// --- rows
#define ROW_0 F, 7
#define ROW_1 F, 6
#define ROW_2 F, 5
#define ROW_3 F, 4
#define ROW_4 F, 1
#define ROW_5 F, 0

// --- columns
#define COLUMN_0 B, 0
#define COLUMN_1 B, 1
#define COLUMN_2 B, 2
#define COLUMN_3 B, 3
#define COLUMN_4 D, 2
#define COLUMN_5 D, 3
#define COLUMN_6 C, 6

// ----------------------------------------------------------------------------

/* returns
 * - success: 0
 */
uint8_t teensy_init(void) {
	// CPU speed : should match F_CPU in makefile
	#if F_CPU != 16000000
		#error "Expecting different CPU frequency"
	#endif
	CPU_PRESCALE(CPU_16MHz);

	// onboard LED
	// (tied to GND for hardware convenience)
	DDRD  &= ~(1<<6);  // set D(6) as input
	PORTD &= ~(1<<6);  // set D(6) internal pull-up disabled

	// (tied to Vcc for hardware convenience)
	DDRB  &= ~(1<<4);  // set B(4) as input
	PORTB &= ~(1<<4);  // set B(4) internal pull-up disabled

	// keyboard LEDs (see "PWM on ports OC1(A|B|C)" in "teensy-2-0.md")
	_kb_led_all_off();  // (just to put the pins in a known state)
	TCCR1A  = 0b10101001;  // set and configure fast PWM
	TCCR1B  = 0b00001001;  // set and configure fast PWM

	// I2C (TWI)
	twi_init();  // on pins D(1,0)

	// unused pins
	teensypin_write_all_unused(DDR, CLEAR); // set as input
	teensypin_write_all_unused(PORT, SET);  // set internal pull-up enabled

	// rows
	teensypin_write_all_row(DDR, CLEAR); // set as input
	teensypin_write_all_row(PORT, SET);  // set internal pull-up enabled

	// columns
	teensypin_write_all_column(DDR, CLEAR);   // set as input (hi-Z)
	teensypin_write_all_column(PORT, CLEAR);  // set internal pull-up
	                                          //   disabled

	return 0;  // success
}

/* returns
 * - success: 0
 */
#if KB_ROWS != 12 || KB_COLUMNS != 7
	#error "Expecting different keyboard dimensions"
#endif
static inline void _update_rows(
		bool matrix[KB_ROWS][KB_COLUMNS], uint8_t column ) {
	matrix[0][column] = ! teensypin_read(ROW_0);
	matrix[1][column] = ! teensypin_read(ROW_1);
	matrix[2][column] = ! teensypin_read(ROW_2);
	matrix[3][column] = ! teensypin_read(ROW_3);
	matrix[4][column] = ! teensypin_read(ROW_4);
	matrix[5][column] = ! teensypin_read(ROW_5);
}
uint8_t teensy_update_matrix(bool matrix[KB_ROWS][KB_COLUMNS]) {
	teensypin_write(DDR, SET, COLUMN_0);   // set col low (set as output)
	_update_rows(matrix, 0);               // read row 0..5 & update matrix
	teensypin_write(DDR, CLEAR, COLUMN_0); // set col hi-Z (set as input)

	teensypin_write(DDR, SET, COLUMN_1);
	_update_rows(matrix, 1);
	teensypin_write(DDR, CLEAR, COLUMN_1);

	teensypin_write(DDR, SET, COLUMN_2);
	_update_rows(matrix, 2);
	teensypin_write(DDR, CLEAR, COLUMN_2);

	teensypin_write(DDR, SET, COLUMN_3);
	_update_rows(matrix, 3);
	teensypin_write(DDR, CLEAR, COLUMN_3);

	teensypin_write(DDR, SET, COLUMN_4);
	_update_rows(matrix, 4);
	teensypin_write(DDR, CLEAR, COLUMN_4);

	teensypin_write(DDR, SET, COLUMN_5);
	_update_rows(matrix, 5);
	teensypin_write(DDR, CLEAR, COLUMN_5);

	teensypin_write(DDR, SET, COLUMN_6);
	_update_rows(matrix, 6);
	teensypin_write(DDR, CLEAR, COLUMN_6);

	return 0;  // success
}

