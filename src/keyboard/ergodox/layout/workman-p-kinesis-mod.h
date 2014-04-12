/* ----------------------------------------------------------------------------
 * ergoDOX : layout : Workman-P : exports
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef KEYBOARD__ERGODOX__LAYOUT__WORKMAN_P_h
	#define KEYBOARD__ERGODOX__LAYOUT__WORKMAN_P_h

	#include "../controller.h"

	// --------------------------------------------------------------------

	#define kb_led_num_on()      _kb_led_1_on()
	#define kb_led_num_off()     _kb_led_1_off()
	#define kb_led_caps_on()     _kb_led_2_on()
	#define kb_led_caps_off()    _kb_led_2_off()
	#define kb_led_scroll_on()   _kb_led_3_on()
	#define kb_led_scroll_off()  _kb_led_3_off()

	// --------------------------------------------------------------------

	#include "./default--led-control.h"
	#include "./default--matrix-control.h"

#endif

