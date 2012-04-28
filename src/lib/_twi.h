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


#undef _str
#undef _expstr
#undef _inc
#define _str(s) #s          // stringify
#define _expstr(s) _str(s)  // expand -> stringify
#define _inc _expstr(_twi/MAKEFILE_BOARD.h)  // inc(lude)
#include _inc
#undef _str
#undef _expstr
#undef _inc

