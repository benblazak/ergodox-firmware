/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * A central place for all `#include`s and common definitions relevant to the
 * layout files
 */


#ifndef ERGODOX_FIRMWARE__KEYBOARD__ERGODOX__LAYOUT__COMMON__DEFINITIONS__H
#define ERGODOX_FIRMWARE__KEYBOARD__ERGODOX__LAYOUT__COMMON__DEFINITIONS__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <avr/pgmspace.h>
#include "../../../../../firmware/lib/timer.h"
#include "../../../../../firmware/lib/usb.h"
#include "../../../../../firmware/lib/usb/usage-page/keyboard.h"
#include "../../../../../firmware/lib/layout/key-functions.h"
#include "../../../../../firmware/lib/layout/layer-stack.h"
#include "../../../../../firmware/keyboard.h"

// ----------------------------------------------------------------------------

/**                                                        macros/P/description
 * Expand `name` into the corresponding "press" function name
 */
#define  P(name)  keys__press__##name

/**                                                        macros/R/description
 * Expand `name` into the corresponding "release" function name
 */
#define  R(name)  keys__release__##name

/**                                                        macros/K/description
 * Expand into a "key" suitable for putting into the layout matrix
 */
#define  K(name)  { &keys__press__##name, &keys__release__##name }

/**                                                       macros/KF/description
 * Expand `name` into the corresponding "key_functions" function name
 */
#define  KF(name)  key_functions__##name

// ----------------------------------------------------------------------------
// special meaning keys (may be used by `exec_key()`)

/**                                                     keys/transp/description
 * transparent
 *
 * This key signals to the firmware (specifically the
 * `kb__layout__exec_key_location()` function) that it should look for what key
 * to "press" or "release" by going down the layer-stack until it finds a
 * non-transparent key at the same position.
 *
 * Notes:
 * - With this scheme, keys may be half transparent; that is, the "press" part
 *   of a key may be transparent while the "release" part isn't, or vice versa.
 *   I expect this to be fairly uncommon though.
 */
void KF(transp) (void) {}
#define  keys__press__transp    KF(transp)
#define  keys__release__transp  KF(transp)

/**                                                        keys/nop/desctiption
 * no operation
 *
 * This key does nothing (and is not transparent).
 */
void KF(nop) (void) {}
#define  keys__press__nop    KF(nop)
#define  keys__release__nop  KF(nop)

// ----------------------------------------------------------------------------

/**                                                    types/_key_t/description
 * The type we will use for our "key"s
 *
 * Notes:
 * - Keys will be of the form
 *   `_key_t key = { &press_function, &release_function };`
 *
 * - The fact that keys are of this type (composed of two
 *   `void (*function)(void)` pointers) is assumed throughout most of these
 *   layout files
 */
typedef  void (*_key_t[2])(void);

/**                                                 types/_layout_t/description
 * The type we will use for our layout matrix
 *
 * Notes:
 * - The first dimension of the matrix (left blank in the typedef since it
 *   varies between layouts) is "layers"
 */
typedef  const _key_t _layout_t[][OPT__KB__ROWS][OPT__KB__COLUMNS];

// ----------------------------------------------------------------------------

/**                                               variables/_layout/description
 * The variable containing our layout matrix
 */
static _layout_t PROGMEM _layout;

/**                                                variables/_flags/description
 * A collection of flags pertaining to the operation of `...exec_key()`
 *
 * Struct members:
 * - `tick_keypresses`: A predicate indicating whether or not to "tick"
 *   keypresses on this run of the function (see the documentation in
 *   ".../firmware/lib/timer.h" for more precisely what this means)
 *     - This is useful for defining things like sticky keys, if, e.g., you
   *     want to make it so that you can press more than one and have none of
   *     them release until the press of the next normal key.
 */
static struct {
    bool tick_keypresses : 1;
} _flags = { .tick_keypresses = true };


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__KEYBOARD__ERGODOX__LAYOUT__COMMON__DEFINITIONS__H

