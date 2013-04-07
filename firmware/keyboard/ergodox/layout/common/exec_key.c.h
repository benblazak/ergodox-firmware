/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * A default way to execute keys.
 *
 * Meant to be included *only* by the layout using it.
 */


#ifndef ERGODOX_FIRMWARE__KEYBOARD__ERGODOX__LAYOUT__COMMON__EXEC_KEY__C__H
#define ERGODOX_FIRMWARE__KEYBOARD__ERGODOX__LAYOUT__COMMON__EXEC_KEY__C__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


#include "./definitions.h"

// ----------------------------------------------------------------------------

void kb__layout__exec_key(bool pressed, int8_t row, int8_t column) {
    void (*function)(void);

    for(uint8_t i=0; i<layer_stack__size(); i++) {
        function = _layout[ layer_stack__peek(i) ]
                          [ row                  ]
                          [ column               ]
                          [ (pressed) ? 0 : 1    ];
        if (function) {
            (*function)();

            if (pressed && _sticky_key) {
                (*_sticky_key)();
                _sticky_key = NULL;
            }

            return;
        }
    }

    // if we get here, there was a transparent key in layer 0; do nothing
}


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__KEYBOARD__ERGODOX__LAYOUT__COMMON__EXEC_KEY__C__H

