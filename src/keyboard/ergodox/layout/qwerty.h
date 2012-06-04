/* ----------------------------------------------------------------------------
 * ergoDOX layout : QWERTY : exports
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef LAYOUT_QWERTY_h
	#define LAYOUT_QWERTY_h

	#include "../led.h"


	#define KB_LAYERS 2  // must match what's defined in "qwerty.c"

	#define kb_led_num_on()      _led_1_on()
	#define kb_led_num_off()     _led_1_off()
	#define kb_led_caps_on()     _led_2_on()
	#define kb_led_caps_off()    _led_2_off()
	#define kb_led_scroll_on()   _led_3_on()
	#define kb_led_scroll_off()  _led_3_off()

#endif

