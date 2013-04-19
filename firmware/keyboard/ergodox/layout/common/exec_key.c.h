/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * A default way to execute keys.
 *
 * Meant to be included *only* by the layout using it.
 *
 * TODO: oops... need to keep track of which layer keys were pressed on, so we
 * can release on the same layer
 */


#ifndef ERGODOX_FIRMWARE__KEYBOARD__ERGODOX__LAYOUT__COMMON__EXEC_KEY__C__H
#define ERGODOX_FIRMWARE__KEYBOARD__ERGODOX__LAYOUT__COMMON__EXEC_KEY__C__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


#include "./definitions.h"

// ----------------------------------------------------------------------------

void kb__layout__exec_key(bool pressed, uint8_t row, uint8_t column) {
    void (*function)(void);
    uint8_t offset = 0;

    do {
        function = _layout[ layer_stack__peek(offset) ]
                          [ row                       ]
                          [ column                    ]
                          [ (pressed) ? 0 : 1         ];

        if (function == &KF(transp))
            function = NULL;

        if (function) {
            (*function)();

            if (pressed && _sticky_key) {
                (*_sticky_key)();
                _sticky_key = NULL;
            }

            return;
        }

        offset++;
    } while (offset < layer_stack__size());

    // if we get here, there was a transparent key in layer 0; do nothing
}


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__KEYBOARD__ERGODOX__LAYOUT__COMMON__EXEC_KEY__C__H

