/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * A central place for the `#include`s relevant to the layout files
 */


#ifndef ERGODOX_FIRMWARE__KEYBOARD__ERGODOX__LAYOUT__COMMON__DEFINITIONS__H
#define ERGODOX_FIRMWARE__KEYBOARD__ERGODOX__LAYOUT__COMMON__DEFINITIONS__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <avr/pgmspace.h>
#include "../../../../../firmware/keyboard.h"
#include "../../../../../firmware/lib/usb.h"
#include "../../../../../firmware/lib/usb/usage-page/keyboard.h"
#include "../../../../../firmware/lib/layout/key-functions.h"

// ----------------------------------------------------------------------------

/**                                                  typedefs/key_t/description
 * The type we will use for our "key"s
 *
 * Notes:
 * - Keys will be of the form
 *   `key_t key = { &press_function, &release_function };`
 */
typedef  void (*key_t[2])(void);

/**                                               typedefs/layout_t/description
 * The type we will use for our layout matrix
 *
 * Notes:
 * - The first dimension of the matrix (left blank in the typedef since it
 *   varies between layouts) is "layers"
 */
typedef  key_t PROGMEM layout_t[][KB__ROWS][KB__COLUMNS];


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__KEYBOARD__ERGODOX__LAYOUT__COMMON__DEFINITIONS__H

