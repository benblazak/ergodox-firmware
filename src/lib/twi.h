/* ----------------------------------------------------------------------------
 * TWI (I2C) : exports
 *
 * Code specific to different development boards is used by modifying a
 * variable in the makefile.
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include "../lib/variable-include.h"
#define INCLUDE EXP_STR( ./twi/MAKEFILE_BOARD.h )
#include INCLUDE

