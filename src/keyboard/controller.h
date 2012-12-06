/* ----------------------------------------------------------------------------
 * controller specific exports
 *
 * Files for different keyboards are used by modifying a variable in the
 * Makefile
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include "../lib/variable-include.h"
#define INCLUDE EXP_STR( ./MAKEFILE_KEYBOARD/controller.h )
#include INCLUDE

