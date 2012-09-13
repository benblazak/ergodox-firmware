/* ----------------------------------------------------------------------------
 * ergoDOX controller: Teensy 2.0 specific exports : private
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef TEENSY_2_0_h_PRIVATE
	#define TEENSY_2_0_h_PRIVATE

	#include "matrix.h"

	uint8_t teensy_init(void);
	uint8_t teensy_update_matrix( bool matrix[KB_ROWS][KB_COLUMNS] );

#endif

