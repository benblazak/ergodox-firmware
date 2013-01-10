/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**
 * - description: |
 *   A default way to execute keys.  Meant to be included by the layout using
 *   it (and nowhere else, since it's actual code).
 *
 *   Note:  This oddish setup is used to allow layouts to easily change some
 *   default things without having to deal with all of them.
 */


#ifndef ERGODOX_FIRMWARE__KEYBOARD__ERGODOX__LAYOUT__DEFAULT__EXEC_KEY_C_H
#define ERGODOX_FIRMWARE__KEYBOARD__ERGODOX__LAYOUT__DEFAULT__EXEC_KEY_C_H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


#include "./common.h"

extern key_t layout[][KB__ROWS][KB__COLUMNS];

// ----------------------------------------------------------------------------

void kb__layout__exec_key( bool   pressed,
                           int8_t layer,
                           int8_t row,
                           int8_t column ) {
    // TODO
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
#endif  // ERGODOX_FIRMWARE__KEYBOARD__ERGODOX__LAYOUT__DEFAULT__EXEC_KEY_C_H

