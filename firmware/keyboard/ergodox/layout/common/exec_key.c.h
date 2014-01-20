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
 * TODO:
 * - should *.c.h functions have macros to guard against multiple includes?
 * - perhaps think about whether this organization of *.c.h files in
 *   .../layout/common is the best.  maybe it could be more modular.  maybe
 *   layers could be included, for use as parts of layouts.  maybe the default
 *   led functions could as well; or there could be a couple different sets of
 *   led function, in files with appropriate names.  dunno.
 */


#ifndef ERGODOX_FIRMWARE__KEYBOARD__ERGODOX__LAYOUT__COMMON__EXEC_KEY__C__H
#define ERGODOX_FIRMWARE__KEYBOARD__ERGODOX__LAYOUT__COMMON__EXEC_KEY__C__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


#include "./definitions.h"

// ----------------------------------------------------------------------------

void kb__layout__exec_key(bool pressed, uint8_t row, uint8_t column) {

    // if we press a key, we need to keep track of the layer it was pressed on,
    // so we can release it on the same layer
    // - if the release is transparent, search through the layer stack for a
    //   non-transparent release in the same position, as normal
    static uint8_t pressed_layer[OPT__KB__ROWS][OPT__KB__COLUMNS];

    void (*function)(void);
    uint8_t layer;

    // - add 1 to the stack size because we spend the first iteration checking
    //   to see if we need to release on a previously stored layer
    // - add 1 to the stack size in order to peek out of bounds on the last
    //   iteration (if we get that far), so that layer 0 is our default (see
    //   the documentation for ".../firmware/lib/layout/layer-stack.h")
    for (uint8_t i=0; i < layer_stack__size()+1+1; i++) {  // i = offset+1
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

            _flags.tick_keypresses = (pressed) ? true : false;  // set default

            (*function)();

            // TODO: *always* tick keypresses
            // TODO: instead of this, set a flag for the type of key pressed,
            // and any functions that execute can check it, and conditionally
            // reschedule themselves to run later, if they so desire
            if (_flags.tick_keypresses)
                timer___tick_keypresses();

            return;
        }
    }

    // if we get here, there was a transparent key in layer 0; do nothing
}


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__KEYBOARD__ERGODOX__LAYOUT__COMMON__EXEC_KEY__C__H

