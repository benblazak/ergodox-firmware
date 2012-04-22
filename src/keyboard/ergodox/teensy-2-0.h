/* ----------------------------------------------------------------------------
 * ergoDOX controller: Teensy 2.0 specific exports
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef TEENSY_2_0_h
	#define TEENSY_2_0_h

	#include <avr/io.h>  // for the register macros

	#include "lib/_data-types.h"

	#include "matrix.h"

	// LED control
	#define KB_LED1_ON             (DDRB |=  (1<<5))
	#define KB_LED1_OFF            (DDRB &= ~(1<<5))
	#define KB_LED1_SET(n)         (OCR1A = (uint8_t)(n))
	#define KB_LED1_SET_PERCENT(n) (OCR1A = (uint8_t)((n) * 0xFF))
	#define KB_LED2_ON             (DDRB |=  (1<<6))
	#define KB_LED2_OFF            (DDRB &= ~(1<<6))
	#define KB_LED2_SET(n)         (OCR1B = (uint8_t)(n))
	#define KB_LED2_SET_PERCENT(n) (OCR1B = (uint8_t)((n) * 0xFF))
	#define KB_LED3_ON             (DDRB |=  (1<<7))
	#define KB_LED3_OFF            (DDRB &= ~(1<<7))
	#define KB_LED3_SET(n)         (OCR1C = (uint8_t)(n))
	#define KB_LED3_SET_PERCENT(n) (OCR1C = (uint8_t)((n) * 0xFF))


	#ifdef KEYBOARD_INCLUDE_PRIVATE

		uint8_t teensy_init(void);
		uint8_t teensy_update_matrix(
				bool matrix[KB_ROWS][KB_COLUMNS] );

	#endif

#endif

