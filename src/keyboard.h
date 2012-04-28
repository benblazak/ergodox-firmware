/* ----------------------------------------------------------------------------
 * keyboard specific exports
 *
 * Different keyboards are included by modifying a variable in the makefile.
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
#define _inc _expstr(keyboard/MAKEFILE_KEYBOARD.h)  // inc(lude)
#include _inc
#undef _str
#undef _expstr
#undef _inc

