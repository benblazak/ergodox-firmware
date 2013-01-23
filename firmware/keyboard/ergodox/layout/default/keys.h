/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**
 * - description: |
 *   Extended (from the definitions in ".../lib/layout/keys.h") default key
 *   definitions.  Feel free not to use them, if they're not convenient.
 */


#ifndef ERGODOX_FIRMWARE__KEYBOARD__ERGODOX__LAYOUT__DEFAULT__KEYS_H
#define ERGODOX_FIRMWARE__KEYBOARD__ERGODOX__LAYOUT__DEFAULT__KEYS_H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


#include "./common.h"

// ----------------------------------------------------------------------------

// `keys__` macros (needed by ".../lib/layout/keys.h")

#define  KEYS__DEFAULT(name, value)             \
    key_t name = {                              \
        .press_function   = &kf__press,         \
        .press_value      = value,              \
        .release_function = &kf__release,       \
        .release_value    = value }                                          

#define  KEYS__SHIFTED(name, value)                         \
    const uint16_t PROGMEM name##__press[] = {              \
        2, &kf__press, KEY__LeftShift,                      \
           &kf__press, value };                             \
    const uint16_t PROGMEM name##__release[] = {            \
        2, &kf__release, KEY__LeftShift,                    \
           &kf__release, value };                           \
    key_t name = { &kf__macro__progmem, &name##__press,     \
                   &kf__macro__progmem, &name##__release }


// other `keys__` macros (in the `keys__` namespace for consistency)

#define  KEYS__TWO_KEYS_CAPSLOCK_PRESS_RELEASE(name, value)     \
    const uint16_t PROGMEM name##__press[] = {                  \
        2, &kf__two_keys_capslock, 1,                           \
           &kf__press, value };                                 \
    const uint16_t PROGMEM name##__release[] = {                \
        2, &kf__two_keys_capslock, 0,                           \
           &kf__release, value };                               \
    key_t name = { &kf__macro__progmem, &name##__press,         \
                   &kf__macro__progmem, &name##release }         

// ----------------------------------------------------------------------------

// default key definitions

#include "../../../../firmware/lib/layout/keys.h"


// special meaning

key_t Transp   = NULL;                  // transparent
key_t NA       = { NULL, 0, NULL, 0 };  // "not applicable" (do nothing)


// special keycode

KEYS__DEFAULT( Power,    KEY__Power      );
KEYS__DEFAULT( VolumeU,  KEY__VolumeUp   );
KEYS__DEFAULT( VolumeD,  KEY__VolumeDown );
KEYS__DEFAULT( Mute,     KEY__Mute       );


// special function

// --- Sh2KCapL
KEYS__TWO_KEYS_CAPSLOCK_PRESS_RELEASE( Sh2KCapL, KEY__LeftShift );

// --- Sh2KCapR
KEYS__TWO_KEYS_CAPSLOCK_PRESS_RELEASE( Sh2KCapR, KEY__RightShift );

// --- Btldr
key_t Btldr = { &kf__jump_to_bootloader, 0, NULL, 0 };


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__KEYBOARD__ERGODOX__LAYOUT__DEFAULT__KEYS_H

