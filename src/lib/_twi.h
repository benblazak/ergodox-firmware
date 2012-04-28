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


#define str(s) #s                              // stringify
#define expstr(s) str(s)                       // expand -> stringify
#define inc expstr(_twi/MAKEFILE_BOARD.h)  // inc(lude)
#include inc
#undef str
#undef expstr
#undef inc

