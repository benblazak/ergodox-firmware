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


	#define kb_led_num_on()      _kb_led_1_on()
	#define kb_led_num_off()     _kb_led_1_off()
	#define kb_led_caps_on()     _kb_led_2_on()
	#define kb_led_caps_off()    _kb_led_2_off()
	#define kb_led_scroll_on()   _kb_led_3_on()
	#define kb_led_scroll_off()  _kb_led_3_off()

#endif

