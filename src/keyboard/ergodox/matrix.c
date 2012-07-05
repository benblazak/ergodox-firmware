/* ----------------------------------------------------------------------------
 * ergoDOX: keyboard matrix specific code
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include "lib/data-types.h"

#include "matrix.h"


static bool _kb_is_pressed[KB_ROWS][KB_COLUMNS];
static bool _kb_was_pressed[KB_ROWS][KB_COLUMNS];

bool (*kb_is_pressed)[KB_ROWS][KB_COLUMNS] = &_kb_is_pressed;
bool (*kb_was_pressed)[KB_ROWS][KB_COLUMNS] = &_kb_was_pressed;

