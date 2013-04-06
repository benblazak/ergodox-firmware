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

void kb__layout__exec_key_pointer(key_t * pointer) {  // TODO
}

void kb__layout__exec_key_location( bool   pressed,  // TODO
                                    int8_t layer,
                                    int8_t row,
                                    int8_t column ) {
    // - check for key redefinition in the EEPROM
    //   - if there is one, execute it, according to the appropriate rules
    // - lookup key in PROGMEM
    //   - if it's transparent, look up the one below it, and so on
    //     - NULL key pointers are transparent
    //     - { NULL, 0, NULL, 0 } keys do nothing; this is the default, if no
    //       key can be found
    //   - call the press or release function, with the appropriate argument
}


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__KEYBOARD__ERGODOX__LAYOUT__COMMON__EXEC_KEY__C__H

