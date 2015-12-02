/* ----------------------------------------------------------------------------
 * Ergodox layout sample
 * Revised by lotem <chen.sst@gmail.com>
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>,
 *    2013 Ryan Prince <judascleric@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */
#include <stdint.h>
#include <stddef.h>
#include <avr/pgmspace.h>
#include "../../../lib/data-types/misc.h"
#include "../../../lib/key-functions/public.h"
#include "../../../lib/usb/usage-page/keyboard--short-names.h"
#include "../matrix.h"
#include "../layout.h"

void kbfun_layer_pop_all(void) {
  kbfun_layer_pop_1();
  kbfun_layer_pop_2();
  kbfun_layer_pop_3();
  kbfun_layer_pop_4();
  kbfun_layer_pop_5();
  kbfun_layer_pop_6();
  kbfun_layer_pop_7();
  kbfun_layer_pop_8();
  kbfun_layer_pop_9();
  kbfun_layer_pop_10();
}

#include "ergodox-layout-impl.h"
/* TODO: change to your layout file. */
#include "sample-layout.h"

#include "ergodox-layout-impl-press.h"
/* TODO: change to your layout file. */
#include "sample-layout.h"

#include "ergodox-layout-impl-release.h"
/* TODO: change to your layout file. */
#include "sample-layout.h"

