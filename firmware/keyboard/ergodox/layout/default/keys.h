/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Extended (from the definitions in ".../lib/layout/keys.h") default key
 * definitions.  Feel free not to use them, if they're not convenient.
 */


#ifndef ERGODOX_FIRMWARE__KEYBOARD__ERGODOX__LAYOUT__DEFAULT__KEYS__H
#define ERGODOX_FIRMWARE__KEYBOARD__ERGODOX__LAYOUT__DEFAULT__KEYS__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


#include "./common.h"

// ----------------------------------------------------------------------------

// `keys__` macros (needed by ".../lib/layout/keys.h")

#define  KEYS__DEFAULT(name, value)             \
    KEY_T name = {                              \
        .press_function   = &kf__press,         \
        .press_value      = value,              \
        .release_function = &kf__release,       \
        .release_value    = value }                                          

#define  KEYS__SHIFTED(name, value)                         \
    const uint16_t PROGMEM name##__press[] = {              \
        2, &kf__press, KEY__LeftShift,                      \
           &kf__press, value };                             \
    const uint16_t PROGMEM name##__release[] = {            \
        2, &kf__release, value,                             \
           &kf__release, KEY__LeftShift };                  \
    KEY_T name = { &kf__macro__progmem, &name##__press,     \
                   &kf__macro__progmem, &name##__release }


// other `keys__` macros (in the `keys__` namespace for consistency)

// TODO: rewrite to reflect: kf__two_keys_capslock() -> kf__toggle_capslock() +
//       kf__chord__progmem() (or some such thing)
// #define  KEYS__TWO_KEYS_CAPSLOCK(name, value)               \
//     const uint16_t PROGMEM name##__press[] = {              \
//         2, &kf__two_keys_capslock, 1,                       \
//            &kf__press, value };                             \
//     const uint16_t PROGMEM name##__release[] = {            \
//         2, &kf__two_keys_capslock, 0,                       \
//            &kf__release, value };                           \
//     KEY_T name = { &kf__macro__progmem, &name##__press,     \
//                    &kf__macro__progmem, &name##__release }         
#define  KEYS__TWO_KEYS_CAPSLOCK(name, value)  KEYS__DEFAULT(name, value)

// ----------------------------------------------------------------------------

// default key definitions

#include "../../../../firmware/lib/layout/keys.h"


// special meaning

KEY_T Transp   = NULL;                  // transparent
KEY_T NA       = { NULL, 0, NULL, 0 };  // "not applicable" (do nothing)


// special keycode

KEYS__DEFAULT( Power,    KEY__Power      );
KEYS__DEFAULT( VolumeU,  KEY__VolumeUp   );
KEYS__DEFAULT( VolumeD,  KEY__VolumeDown );
KEYS__DEFAULT( Mute,     KEY__Mute       );


// special function

// --- Sh2KCapL
KEYS__TWO_KEYS_CAPSLOCK( Sh2KCapL, KEY__LeftShift );

// --- Sh2KCapR
KEYS__TWO_KEYS_CAPSLOCK( Sh2KCapR, KEY__RightShift );

// --- Btldr
KEY_T Btldr = { &kf__jump_to_bootloader, 0, NULL, 0 };


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__KEYBOARD__ERGODOX__LAYOUT__DEFAULT__KEYS__H

