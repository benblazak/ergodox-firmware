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

    // keep track of the layer the key was pressed on, so we can release it on
    // the same layer
    // - if the release is transparent, search through the layer stack for a
    //   non-transparent release in the same position, as normal
    // - don't need to initialize, since we'll only read from positions that
    //   we've previously set
    static uint8_t pressed_layer[OPT__KB__ROWS][OPT__KB__COLUMNS];

    void (*function)(void);
    uint8_t layer;

    for(uint8_t i = 0; i < layer_stack__size()+1+1; i++) {  // i = offset+1
        if (i == 0)
            if (!pressed)
                layer = pressed_layer[row][column];
            else
                continue;
        else
            layer = layer_stack__peek(i-1);

        function = (void (*)(void))
                   pgm_read_word( &( _layout[ layer             ]
                                            [ row               ]
                                            [ column            ]
                                            [ (pressed) ? 0 : 1 ] ) );

        if (function == &KF(transp))
            function = NULL;

        if (function) {
            if (pressed)
                pressed_layer[row][column] = layer;

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

