/* ----------------------------------------------------------------------------
 * ergoDOX specific exports
 * includes (for centralization) the public exports from all subfiles
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef ERGODOX_h
	#define ERGODOX_h

	#include "lib/data-types.h"

	#include "ergodox/layout.h"      // number of layers, layout
	#include "ergodox/led.h"         // logical led controls
	#include "ergodox/matrix.h"      // kb dimensions, matrix status
	#include "ergodox/mcp23018.h"    // (nothing right now)
	#include "ergodox/teensy-2-0.h"  // LED controls


	// note:
	// - see your keyswitch specification for the necessary value.  for
	//   cherry mx switches, the switch bounce time is speced to be <= 5ms.
	//   it looks like most switches are speced to be between 5 and 8 ms.
	// - if timing is important, balance this value with the main() loop
	//   run time (~5ms, last i checked, nearly all of it in the i2c
	//   update() function)
	#define KB_DEBOUNCE_TIME 5  // in ms


	uint8_t kb_init(void);
	uint8_t kb_update_matrix(bool matrix[KB_ROWS][KB_COLUMNS]);

#endif

