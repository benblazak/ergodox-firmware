/* ----------------------------------------------------------------------------
 * ergoDOX : controller : Teensy 2.0 specific exports : LED control
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef KEYBOARD__ERGODOX__CONTROLLER__TEENSY_2_0__LED_h
	#define KEYBOARD__ERGODOX__CONTROLLER__TEENSY_2_0__LED_h

	#include <stdint.h>
	#include <avr/io.h>  // for the register macros

	// --------------------------------------------------------------------

	#define _kb_led_1_on()           (DDRB |=  (1<<5))
	#define _kb_led_1_off()          (DDRB &= ~(1<<5))
	#define _kb_led_1_set(n)         (OCR1A = (uint8_t)(n))
	#define _kb_led_1_set_percent(n) (OCR1A = (uint8_t)((n) * 0xFF))

	#define _kb_led_2_on()           (DDRB |=  (1<<6))
	#define _kb_led_2_off()          (DDRB &= ~(1<<6))
	#define _kb_led_2_set(n)         (OCR1B = (uint8_t)(n))
	#define _kb_led_2_set_percent(n) (OCR1B = (uint8_t)((n) * 0xFF))

	#define _kb_led_3_on()           (DDRB |=  (1<<7))
	#define _kb_led_3_off()          (DDRB &= ~(1<<7))
	#define _kb_led_3_set(n)         (OCR1C = (uint8_t)(n))
	#define _kb_led_3_set_percent(n) (OCR1C = (uint8_t)((n) * 0xFF))


	#define _kb_led_all_on() do {	\
		_kb_led_1_on();		\
		_kb_led_2_on();		\
		_kb_led_3_on();		\
		} while(0)

	#define _kb_led_all_off() do {	\
		_kb_led_1_off();	\
		_kb_led_2_off();	\
		_kb_led_3_off();	\
		} while(0)

	#define _kb_led_all_set(n) do {	\
		_kb_led_1_set(n);	\
		_kb_led_2_set(n);	\
		_kb_led_3_set(n);	\
		} while(0)

	#define _kb_led_all_set_percent(n) do {	\
		_kb_led_1_set_percent(n);	\
		_kb_led_2_set_percent(n);	\
		_kb_led_3_set_percent(n);	\
		} while(0)

#endif

