/* ----------------------------------------------------------------------------
 * Copyright (c) 2013, 2014 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * A default way to execute keys
 *
 * Usage notes:
 * - Depends on (must be included after) "variables.part.h" and "keys.part.h"
 */


/**                                  functions/kb__layout__exec_key/description
 * Assumptions:
 * - All arguments are valid.
 *
 * Implementation notes:
 * - The default layer is layer 0.
 * - This function is only responsible for layer resolution (which includes the
 *   handling of transparent keys).  Everything else, it passes to
 *   `kb__layout__exec_key_layer()`.
 */
void kb__layout__exec_key(bool pressed, uint8_t row, uint8_t column) {

    // - to keep track of the layer a key was pressed on, so we can release on
    //   the same layer
    static uint8_t pressed_layer[OPT__KB__ROWS][OPT__KB__COLUMNS];

    uint8_t layer;
    void (*function)(void);

    // handle the case that a key is released, and the layer it was pressed on
    // has a non-transparent release function in the given location

    if (! pressed) {
        layer = pressed_layer[row][column];
        function = (void (*)(void))
                   pgm_read_word( &( layout[ layer    ]
                                           [ row      ]
                                           [ column   ]
                                           [ !pressed ] ) );

        if (function != &KF(transp)) {
            kb__layout__exec_key_layer( pressed, layer, row, column );
            return;
        }
    }

    // otherwise, search through the layer stack for a layer with a
    // non-transparent key-function in the given location

    // - altogether, unless we find a non-transparent key-function earlier, we
    //   want to peek at offsets `0` through `layer_stack__size()`.  this will
    //   cause us to peek out of bounds on the last iteration, so that layer 0
    //   will be the default (see the documentation for
    //   ".../lib/layout/layer-stack")
    for (uint8_t i=0; i <= layer_stack__size(); i++) {
        layer = layer_stack__peek(i);
        function = (void (*)(void))
                   pgm_read_word( &( layout[ layer    ]
                                           [ row      ]
                                           [ column   ]
                                           [ !pressed ] ) );

        if (function != &KF(transp)) {
            if (pressed)
                pressed_layer[row][column] = layer;

            kb__layout__exec_key_layer( pressed, layer, row, column );
            return;
        }
    }

    // if we get here, there was a transparent key in layer 0; do nothing
}

/**                            functions/kb__layout__exec_key_layer/description
 * Assumptions:
 * - All arguments are valid.
 *
 * TODO:
 * - take care of the recording and such of macros :)
 *   - need to ignore layer-shift keys when recording
 */
void kb__layout__exec_key_layer( bool    pressed,
                                 uint8_t layer,
                                 uint8_t row,
                                 uint8_t column ) {

    void (*function)(void) = (void (*)(void)) 
                             pgm_read_word( &( layout[ layer    ]
                                                     [ row      ]
                                                     [ column   ]
                                                     [ !pressed ] ) );
    if (! function) return;

    // set default values
    // - the key-function will not be able to see the values set previously
    // - any function scheduled to run will be able to see the values set
    //   by the immediately preceding function; but that may change in the
    //   future, so it shouldn't be relied on.  if functions need to
    //   communicate with each other, they should share a file-local or global
    //   variable.
    flags[0].key_type.sticky      = false;
    flags[0].key_type.layer_shift = false;
    flags[0].key_type.layer_lock  = false;

    (*function)();

    if (pressed)
        timer___tick_keypresses();
}

