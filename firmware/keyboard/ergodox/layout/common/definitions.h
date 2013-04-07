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
#include "../../../../../firmware/lib/layout/layer-stack.h"

// ----------------------------------------------------------------------------

/**                                                  typedefs/key_t/description
 * The type we will use for our "key"s
 *
 * Notes:
 * - Keys will be of the form
 *   `key_t key = { &press_function, &release_function };`
 *
 * - The fact that keys are of this type (composed of two
 *   `void (*function)(void)` pointers) is assumed throughout most of these
 *   layout files
 */
typedef  void (*key_t[2])(void);

/**                                               typedefs/layout_t/description
 * The type we will use for our layout matrix
 *
 * Notes:
 * - The first dimension of the matrix (left blank in the typedef since it
 *   varies between layouts) is "layers"
 */
typedef  const key_t PROGMEM layout_t[][OPT__KB__ROWS][OPT__KB__COLUMNS];

/**                                                variables/layout/description
 * The variable containing our layout matrix
 */
layout_t _layout;

/**                                            variables/sticky_key/description
 * A pointer to the release function of the last sticky key pressed
 *
 * The function pointed to by this should be executed directly after executing
 * the "press" function of the next key pressed.
 *
 * Notes:
 * - In order for things to work right, sticky keys should either execute this
 *   stored function themselves before placing their own "release" function
 *   value here, or else save the value that's here and call it as part of
 *   their own "release" function.  If this isn't done, and the key pressed
 *   directly before this was a sticky key as well, then the previous sticky
 *   key will never be released.
 */
void (*_sticky_key)(void);


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__KEYBOARD__ERGODOX__LAYOUT__COMMON__DEFINITIONS__H

