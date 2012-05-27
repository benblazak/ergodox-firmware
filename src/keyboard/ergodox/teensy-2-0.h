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
	#include "lib/data-types.h"

	#include "matrix.h"

	// LED control
	#define kb_led1_on()           (DDRB |=  (1<<6))
	#define kb_led1_off()          (DDRB &= ~(1<<6))
	#define kb_led1_set(n)         (OCR1B = (uint8_t)(n))
	#define kb_led1_set_percent(n) (OCR1B = (uint8_t)((n) * 0xFF))
	//
	#define kb_led2_on()           (DDRB |=  (1<<5))
	#define kb_led2_off()          (DDRB &= ~(1<<5))
	#define kb_led2_set(n)         (OCR1A = (uint8_t)(n))
	#define kb_led2_set_percent(n) (OCR1A = (uint8_t)((n) * 0xFF))
	//
	#define kb_led3_on()           (DDRB |=  (1<<7))
	#define kb_led3_off()          (DDRB &= ~(1<<7))
	#define kb_led3_set(n)         (OCR1C = (uint8_t)(n))
	#define kb_led3_set_percent(n) (OCR1C = (uint8_t)((n) * 0xFF))


	#ifdef KEYBOARD_INCLUDE_PRIVATE

		uint8_t teensy_init(void);
		uint8_t teensy_update_matrix(
				bool matrix[KB_ROWS][KB_COLUMNS] );

	#endif

#endif

