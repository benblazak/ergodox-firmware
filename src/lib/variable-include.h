/* ----------------------------------------------------------------------------
 * Macros to help with conditional includes
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#undef  INCLUDE
#define  STR(s)  #s          // stringify
#define  EXP_STR(s)  STR(s)  // expand -> stringify

