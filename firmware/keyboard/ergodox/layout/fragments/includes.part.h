/* ----------------------------------------------------------------------------
 * Copyright (c) 2013, 2014 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * A central place for all `#include`s relevant to the fragments of layout
 * code in this directory
 *
 * These includes, or at least most of them, will very likely be needed if any
 * of the other files in this directory are used.
 */


#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <avr/pgmspace.h>
#include "../../../../../firmware/lib/timer.h"
#include "../../../../../firmware/lib/usb.h"
#include "../../../../../firmware/lib/usb/usage-page/keyboard.h"
#include "../../../../../firmware/lib/layout/eeprom-macro.h"
#include "../../../../../firmware/lib/layout/key-functions.h"
#include "../../../../../firmware/lib/layout/layer-stack.h"
#include "../../../../../firmware/keyboard.h"

