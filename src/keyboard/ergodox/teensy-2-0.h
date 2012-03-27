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

	// LED control
	#define KB_LED1_ON             (OCR1A = 0xFF)
	#define KB_LED1_OFF            (OCR1A = 0x00)
	#define KB_LED1_SET(n)         (OCR1A = (uint8_t)(n))
	#define KB_LED1_SET_PERCENT(n) (OCR1A = (uint8_t)((n) * 0xFF))
	#define KB_LED2_ON             (OCR1B = 0xFF)
	#define KB_LED2_OFF            (OCR1B = 0x00)
	#define KB_LED2_SET(n)         (OCR1B = (uint8_t)(n))
	#define KB_LED2_SET_PERCENT(n) (OCR1B = (uint8_t)((n) * 0xFF))
	#define KB_LED3_ON             (OCR1C = 0xFF)
	#define KB_LED3_OFF            (OCR1C = 0x00)
	#define KB_LED3_SET(n)         (OCR1C = (uint8_t)(n))
	#define KB_LED3_SET_PERCENT(n) (OCR1C = (uint8_t)((n) * 0xFF))


	#ifdef TEENSY_2_0_h_INCLUDE_PRIVATE

		uint8_t teensy_init(void);

	#endif

#endif

