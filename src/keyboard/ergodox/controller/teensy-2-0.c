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
#include "../options.h"
#include "../matrix.h"
#include "./teensy-2-0--functions.h"
#include "./teensy-2-0--led.h"

// ----------------------------------------------------------------------------

// check options
#if  (TEENSY__DRIVE_ROWS && TEENSY__DRIVE_COLUMNS)	\
 || !(TEENSY__DRIVE_ROWS || TEENSY__DRIVE_COLUMNS)
	#error "See 'Pin drive direction' in 'options.h'"
#endif
// ----------------------------------------------------------------------------

// processor frequency (from <http://www.pjrc.com/teensy/prescaler.html>)
#define  CPU_PRESCALE(n)  (CLKPR = 0x80, CLKPR = (n))
#define  CPU_16MHz        0x00
#define  CPU_8MHz         0x01
#define  CPU_4MHz         0x02
#define  CPU_2MHz         0x03
#define  CPU_1MHz         0x04
#define  CPU_500kHz       0x05
#define  CPU_250kHz       0x06
#define  CPU_125kHz       0x07
#define  CPU_62kHz        0x08


/*
 * pin macros
 * - note: you can move the `UNUSED`, `ROW`, and `COLUMN` pins around, but be
 *   sure to keep the set of all the pins listed constant.  other pins are not
 *   movable, and either are referenced explicitly or have macros defined for
 *   them elsewhere.
 * - note: if you change pin assignments, please be sure to update
 *   "teensy-2-0.md", and the '.svg' circuit diagram.
 */

// --- unused
#define  UNUSED_0  C, 7
#define  UNUSED_1  D, 7
#define  UNUSED_2  D, 4  // hard to use with breadboard (on the end)
#define  UNUSED_3  D, 5  // hard to use with breadboard (on the end)
#define  UNUSED_4  E, 6  // hard to use with breadboard (internal)

// --- rows
#define  ROW_0  F, 7
#define  ROW_1  F, 6
#define  ROW_2  F, 5
#define  ROW_3  F, 4
#define  ROW_4  F, 1
#define  ROW_5  F, 0

// --- columns
#define  COLUMN_7  B, 0
#define  COLUMN_8  B, 1
#define  COLUMN_9  B, 2
#define  COLUMN_A  B, 3
#define  COLUMN_B  D, 2
#define  COLUMN_C  D, 3
#define  COLUMN_D  C, 6

// --- helpers
#define  SET    |=
#define  CLEAR  &=~

#define  _teensypin_write(register, operation, pin_letter, pin_number)	\
	do {								\
		((register##pin_letter) operation (1<<(pin_number)));	\
		_delay_us(1);  /* allow pins time to stabilize */	\
	} while(0)
#define  teensypin_write(register, operation, pin)	\
	_teensypin_write(register, operation, pin)

#define  _teensypin_read(pin_letter, pin_number)	\
	((PIN##pin_letter) & (1<<(pin_number)))
#define  teensypin_read(pin)	\
	_teensypin_read(pin)

#define  teensypin_write_all_unused(register, operation)		\
	do {								\
		teensypin_write(register, operation, UNUSED_0);		\
		teensypin_write(register, operation, UNUSED_1);		\
		teensypin_write(register, operation, UNUSED_2);		\
		teensypin_write(register, operation, UNUSED_3);		\
		teensypin_write(register, operation, UNUSED_4); }	\
	while(0)

#define  teensypin_write_all_row(register, operation)		\
	do {							\
		teensypin_write(register, operation, ROW_0);	\
		teensypin_write(register, operation, ROW_1);	\
		teensypin_write(register, operation, ROW_2);	\
		teensypin_write(register, operation, ROW_3);	\
		teensypin_write(register, operation, ROW_4);	\
		teensypin_write(register, operation, ROW_5); }	\
	while(0)

#define  teensypin_write_all_column(register, operation)		\
	do {								\
		teensypin_write(register, operation, COLUMN_7);		\
		teensypin_write(register, operation, COLUMN_8);		\
		teensypin_write(register, operation, COLUMN_9);		\
		teensypin_write(register, operation, COLUMN_A);		\
		teensypin_write(register, operation, COLUMN_B);		\
		teensypin_write(register, operation, COLUMN_C);		\
		teensypin_write(register, operation, COLUMN_D); }	\
	while(0)


/*
 * update macros
 */
#define  update_rows_for_column(matrix, column)				\
	do {								\
		/* set column low (set as output) */			\
		teensypin_write(DDR, SET, COLUMN_##column);		\
		/* read rows 0..5 and update matrix */			\
		matrix[0x0][0x##column] = ! teensypin_read(ROW_0);	\
		matrix[0x1][0x##column] = ! teensypin_read(ROW_1);	\
		matrix[0x2][0x##column] = ! teensypin_read(ROW_2);	\
		matrix[0x3][0x##column] = ! teensypin_read(ROW_3);	\
		matrix[0x4][0x##column] = ! teensypin_read(ROW_4);	\
		matrix[0x5][0x##column] = ! teensypin_read(ROW_5);	\
		/* set column hi-Z (set as input) */			\
		teensypin_write(DDR, CLEAR, COLUMN_##column);		\
	} while(0)

#define  update_columns_for_row(matrix, row)				\
	do {								\
		/* set row low (set as output) */			\
		teensypin_write(DDR, SET, ROW_##row);			\
		/* read columns 7..D and update matrix */		\
		matrix[0x##row][0x7] = ! teensypin_read(COLUMN_7);	\
		matrix[0x##row][0x8] = ! teensypin_read(COLUMN_8);	\
		matrix[0x##row][0x9] = ! teensypin_read(COLUMN_9);	\
		matrix[0x##row][0xA] = ! teensypin_read(COLUMN_A);	\
		matrix[0x##row][0xB] = ! teensypin_read(COLUMN_B);	\
		matrix[0x##row][0xC] = ! teensypin_read(COLUMN_C);	\
		matrix[0x##row][0xD] = ! teensypin_read(COLUMN_D);	\
		/* set row hi-Z (set as input) */			\
		teensypin_write(DDR, CLEAR, ROW_##row);			\
	} while(0)

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

	// rows and columns
	teensypin_write_all_row(DDR, CLEAR);     // set as input (hi-Z)
	teensypin_write_all_column(DDR, CLEAR);  // set as input (hi-Z)
	#if TEENSY__DRIVE_ROWS
		teensypin_write_all_row(PORT, CLEAR);   // pull-up disabled
		teensypin_write_all_column(PORT, SET);  // pull-up enabled
	#elif TEENSY__DRIVE_COLUMNS
		teensypin_write_all_row(PORT, SET);       // pull-up enabled
		teensypin_write_all_column(PORT, CLEAR);  // pull-up disabled
	#endif

	return 0;  // success
}

/* returns
 * - success: 0
 */
#if KB_ROWS != 6 || KB_COLUMNS != 14
	#error "Expecting different keyboard dimensions"
#endif

uint8_t teensy_update_matrix(bool matrix[KB_ROWS][KB_COLUMNS]) {
	#if TEENSY__DRIVE_ROWS
		update_columns_for_row(matrix, 0);
		update_columns_for_row(matrix, 1);
		update_columns_for_row(matrix, 2);
		update_columns_for_row(matrix, 3);
		update_columns_for_row(matrix, 4);
		update_columns_for_row(matrix, 5);
	#elif TEENSY__DRIVE_COLUMNS
		update_rows_for_column(matrix, 7);
		update_rows_for_column(matrix, 8);
		update_rows_for_column(matrix, 9);
		update_rows_for_column(matrix, A);
		update_rows_for_column(matrix, B);
		update_rows_for_column(matrix, C);
		update_rows_for_column(matrix, D);
	#endif

	return 0;  // success
}
