/* ----------------------------------------------------------------------------
 * ergoDOX controller: Teensy 2.0 specific code
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include <avr/io.h>
#include "lib/data-types.h"
#define TWI_FREQ 400000
#include "lib/twi.h"

#define KEYBOARD_INCLUDE_PRIVATE
#include "matrix.h"
#include "teensy-2-0.h"


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
 *   "teensy-2-0.md".
 */
// --- helpers
#define TEENSYPIN_WRITE(register, operation, pin) \
	_TEENSYPIN_WRITE(register, operation, pin)
#define _TEENSYPIN_WRITE(register, operation, pin_letter, pin_number) \
	((register##pin_letter) operation (1<<(pin_number)))

#define TEENSYPIN_READ(pin) \
	_TEENSYPIN_READ(pin)
#define _TEENSYPIN_READ(pin_letter, pin_number) \
	((PIN##pin_letter) & (1<<(pin_number)))

#define SET |=
#define CLEAR &=~

// --- unused
#define UNUSED_0 B, 1  // SPI pin
#define UNUSED_1 B, 2  // SPI pin
#define UNUSED_2 B, 3  // SPI pin
#define UNUSED_3 D, 4  // hard to use with breadboard (on the end)
#define UNUSED_4 D, 5  // hard to use with breadboard (on the end)
#define UNUSED_5 E, 6  // hard to use with breadboard (internal)

// --- rows
#define ROW_0 F, 0
#define ROW_1 F, 1
#define ROW_2 F, 4
#define ROW_3 F, 5
#define ROW_4 F, 6
#define ROW_5 F, 7

// --- columns
#define COLUMN_0 B, 4
#define COLUMN_1 C, 6
#define COLUMN_2 C, 7
#define COLUMN_3 D, 2
#define COLUMN_4 D, 3
#define COLUMN_5 D, 7
#define COLUMN_6 B, 0


/* returns
 * - success: 0
 */
uint8_t teensy_init(void) {
	CPU_PRESCALE(CPU_16MHz);  // speed should match F_CPU in makefile

	// onboard LED
	DDRD  &= ~(1<<6);  // set D(6) as input
	PORTD &= ~(1<<6);  // set D(6) internal pull-up disabled

	// keyboard LEDs (see "PWM on ports OC1(A|B|C)" in "teensy-2-0.md")
	DDRB   |= 0b11100000;  // set B(7,6,5) as output
	TCCR1A  = 0b10101001;  // set and configure fast PWM
	TCCR1B  = 0b00001001;  // set and configure fast PWM

	KB_LED1_SET_PERCENT(0.5); KB_LED1_OFF;
	KB_LED2_SET_PERCENT(0.5); KB_LED2_OFF;
	KB_LED3_SET_PERCENT(0.5); KB_LED3_OFF;

	// I2C (TWI)
	twi_init();  // on pins D(1,0)

	// unused pins
	// --- set as input
	TEENSYPIN_WRITE(DDR, CLEAR, UNUSED_0);
	TEENSYPIN_WRITE(DDR, CLEAR, UNUSED_1);
	TEENSYPIN_WRITE(DDR, CLEAR, UNUSED_2);
	TEENSYPIN_WRITE(DDR, CLEAR, UNUSED_3);
	TEENSYPIN_WRITE(DDR, CLEAR, UNUSED_4);
	TEENSYPIN_WRITE(DDR, CLEAR, UNUSED_5);
	// --- set internal pull-up enabled
	TEENSYPIN_WRITE(PORT, SET, UNUSED_0);
	TEENSYPIN_WRITE(PORT, SET, UNUSED_1);
	TEENSYPIN_WRITE(PORT, SET, UNUSED_2);
	TEENSYPIN_WRITE(PORT, SET, UNUSED_3);
	TEENSYPIN_WRITE(PORT, SET, UNUSED_4);
	TEENSYPIN_WRITE(PORT, SET, UNUSED_5);

	// rows
	// --- set as input (hi-Z)
	TEENSYPIN_WRITE(DDR, CLEAR, ROW_0);
	TEENSYPIN_WRITE(DDR, CLEAR, ROW_1);
	TEENSYPIN_WRITE(DDR, CLEAR, ROW_2);
	TEENSYPIN_WRITE(DDR, CLEAR, ROW_3);
	TEENSYPIN_WRITE(DDR, CLEAR, ROW_4);
	TEENSYPIN_WRITE(DDR, CLEAR, ROW_5);
	// --- set internal pull-up disabled
	TEENSYPIN_WRITE(PORT, CLEAR, ROW_0);
	TEENSYPIN_WRITE(PORT, CLEAR, ROW_1);
	TEENSYPIN_WRITE(PORT, CLEAR, ROW_2);
	TEENSYPIN_WRITE(PORT, CLEAR, ROW_3);
	TEENSYPIN_WRITE(PORT, CLEAR, ROW_4);
	TEENSYPIN_WRITE(PORT, CLEAR, ROW_5);

	// columns
	// --- set as input
	TEENSYPIN_WRITE(DDR, CLEAR, COLUMN_0);
	TEENSYPIN_WRITE(DDR, CLEAR, COLUMN_1);
	TEENSYPIN_WRITE(DDR, CLEAR, COLUMN_2);
	TEENSYPIN_WRITE(DDR, CLEAR, COLUMN_3);
	TEENSYPIN_WRITE(DDR, CLEAR, COLUMN_4);
	TEENSYPIN_WRITE(DDR, CLEAR, COLUMN_5);
	TEENSYPIN_WRITE(DDR, CLEAR, COLUMN_6);
	// --- set internal pull-up enabled
	TEENSYPIN_WRITE(PORT, SET, COLUMN_0);
	TEENSYPIN_WRITE(PORT, SET, COLUMN_1);
	TEENSYPIN_WRITE(PORT, SET, COLUMN_2);
	TEENSYPIN_WRITE(PORT, SET, COLUMN_3);
	TEENSYPIN_WRITE(PORT, SET, COLUMN_4);
	TEENSYPIN_WRITE(PORT, SET, COLUMN_5);
	TEENSYPIN_WRITE(PORT, SET, COLUMN_6);

	return 0;  // success
}

/* returns
 * - success: 0
 */
#if KB_ROWS != 12 || KB_COLUMNS != 7
	#error "Expecting different keyboard dimensions"
#endif
static inline void _update_columns(
		bool matrix[KB_ROWS][KB_COLUMNS], uint8_t row ) {
	matrix[row][0] = ! TEENSYPIN_READ(COLUMN_0);
	matrix[row][1] = ! TEENSYPIN_READ(COLUMN_1);
	matrix[row][2] = ! TEENSYPIN_READ(COLUMN_2);
	matrix[row][3] = ! TEENSYPIN_READ(COLUMN_3);
	matrix[row][4] = ! TEENSYPIN_READ(COLUMN_4);
	matrix[row][5] = ! TEENSYPIN_READ(COLUMN_5);
	matrix[row][6] = ! TEENSYPIN_READ(COLUMN_6);
}
uint8_t teensy_update_matrix(bool matrix[KB_ROWS][KB_COLUMNS]) {
	TEENSYPIN_WRITE(DDR, SET, ROW_0);    // set row low (set as output)
	_update_columns(matrix, 0);          // read col 0..6 and update matrix
	TEENSYPIN_WRITE(DDR, CLEAR, ROW_0);  // set row hi-Z (set as input)

	TEENSYPIN_WRITE(DDR, SET, ROW_1);
	_update_columns(matrix, 1);
	TEENSYPIN_WRITE(DDR, CLEAR, ROW_1);

	TEENSYPIN_WRITE(DDR, SET, ROW_2);
	_update_columns(matrix, 2);
	TEENSYPIN_WRITE(DDR, CLEAR, ROW_2);

	TEENSYPIN_WRITE(DDR, SET, ROW_3);
	_update_columns(matrix, 3);
	TEENSYPIN_WRITE(DDR, CLEAR, ROW_3);

	TEENSYPIN_WRITE(DDR, SET, ROW_4);
	_update_columns(matrix, 4);
	TEENSYPIN_WRITE(DDR, CLEAR, ROW_4);

	TEENSYPIN_WRITE(DDR, SET, ROW_5);
	_update_columns(matrix, 5);
	TEENSYPIN_WRITE(DDR, CLEAR, ROW_5);

	return 0;  // success
}

