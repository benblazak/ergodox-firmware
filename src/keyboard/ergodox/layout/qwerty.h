/* ----------------------------------------------------------------------------
 * ergoDOX layout : QWERTY : exports
 *
 * Meant to be included (as the last header) from "../layout.h"
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#define KB_LAYERS 1  // must match what's defined in the layout '.c' file


extern uint8_t        _kb_layout         [KB_LAYERS][KB_ROWS][KB_COLUMNS];
extern kbfun_funptr_t _kb_layout_press   [KB_LAYERS][KB_ROWS][KB_COLUMNS];
extern kbfun_funptr_t _kb_layout_release [KB_LAYERS][KB_ROWS][KB_COLUMNS];

