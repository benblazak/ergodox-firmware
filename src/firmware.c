/* ----------------------------------------------------------------------------
 * Firmware for the ergoDOX keyboard
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak
 * Released under The MIT License (MIT) (see "license.md") at
 * <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include "hardware/ergodox.h"

#include "lib/twi.h"
#include "lib/print.h"


void main() {
	init();
}

void init() {
	controller_init();  // must be first
	kb_init();          // must be second

	// TODO: other stuff?
}

