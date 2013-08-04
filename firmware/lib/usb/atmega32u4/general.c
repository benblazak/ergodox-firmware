/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Implements the "general" section of '.../firmware/lib/usb.h'
 *
 * This is currently a wrapper for the PJRC code
 */

#include <stdbool.h>
#include "./keyboard/from-pjrc/usb.h"
#include "../../usb.h"

// ----------------------------------------------------------------------------

void usb__init(void) { usb_init(); }

bool usb__is_configured(void) { return usb_configured(); }

