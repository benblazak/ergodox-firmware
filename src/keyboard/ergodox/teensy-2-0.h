/* ----------------------------------------------------------------------------
 * ergoDOX controller: Teensy 2.0 specific exports
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef TEENSY_2_0_h
	#define TEENSY_2_0_h

	#ifndef INCLUDE_PREFIX
		#define INCLUDE_PREFIX teensy_
	#endif

	#define prefix(s) INCLUDE_PREFIX##s
	#define pprefix(s) PRIVATE_INCLUDE_PREFIX##s

	// --------------------------------------------------------------------

	#include <avr/io.h>  // for the register macros

	// LED control
	#define prefix(LED1_ON)             (OCR1A = 0xFF)
	#define prefix(LED1_OFF)            (OCR1A = 0x00)
	#define prefix(LED1_SET)(n)         (OCR1A = (uint8_t)(n))
	#define prefix(LED1_SET_PERCENT)(n) (OCR1A = (uint8_t)((n) * 0xFF))
	#define prefix(LED2_ON)             (OCR1B = 0xFF)
	#define prefix(LED2_OFF)            (OCR1B = 0x00)
	#define prefix(LED2_SET)(n)         (OCR1B = (uint8_t)(n))
	#define prefix(LED2_SET_PERCENT)(n) (OCR1B = (uint8_t)((n) * 0xFF))
	#define prefix(LED3_ON)             (OCR1C = 0xFF)
	#define prefix(LED3_OFF)            (OCR1C = 0x00)
	#define prefix(LED3_SET)(n)         (OCR1C = (uint8_t)(n))
	#define prefix(LED3_SET_PERCENT)(n) (OCR1C = (uint8_t)((n) * 0xFF))

	// --------------------------------------------------------------------

	#ifdef PRIVATE_INCLUDE_PREFIX

		void pprefix(init)(void)
			__attribute__((alias ("teensy_init")));

	#endif

	// --------------------------------------------------------------------

	#undef prefix
	#undef pprefix
	#undef INCLUDE_PREFIX
	#undef PRIVATE_INCLUDE_PREFIX

#endif

