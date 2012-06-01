/* ----------------------------------------------------------------------------
 * led stuff that isn't microprocessor or layout specific
 *
 * you should also include this file for low-level led macros, as it will
 * always include the file(s) containing those
 *
 * - low level led macros should all start with '_led_'
 * - public led macros should start with 'kb_led_'
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef LED_h
	#define LED_h

	#include <util/delay.h>

	#include "teensy-2-0.h"  // for low-level led macros


	#define kb_led_state_power_on() do {		\
			_led_all_set_percent(0.05);	\
			_led_all_on();			\
			} while(0)

	// note: need to delay for a total of ~1 second
	#define kb_led_delay_usb_init() do {		\
			_led_1_set_percent(0.5);	\
			_delay_ms(333);			\
			_led_2_set_percent(0.5);	\
			_delay_ms(333);			\
			_led_3_set_percent(0.5);	\
			_delay_ms(333);			\
			} while(0)

	#define kb_led_state_ready() do {		\
			_led_all_off();			\
			_led_all_set_percent(0.5);	\
			} while(0)

#endif

