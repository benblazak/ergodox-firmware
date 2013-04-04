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

// note: needed by ".../lib/layout/keys.h"
#define  KEYS__DEFAULT(name, value)                             \
    void keys__press__##name   (void) { kf__press(value);   }   \
    void keys__release__##name (void) { kf__release(value); }

// note: needed by ".../lib/layout/keys.h"
#define  KEYS__SHIFTED(name, value)                                     \
    void keys__press__##name   (void) { kf__press(KEY__LeftShift);      \
                                        kf__press(value); }             \
    void keys__release__##name (void) { kf__release(value);             \
                                        kf__release(KEY__LeftShift); }

// TODO: this probably isn't right...
#define  KEYS__CHORD__SETUP(chordname, init, comparison, threshold) \
    bool keys__chord__##chordname (bool pressed) {                  \
        static counter = (init);                                    \
        if (pressed) counter++;                                     \
        if (counter comparison (threshold))                         \
            return true;                                            \
        if (!pressed) counter--;                                    \
    }

// TODO: this probably isn't either
#define KEYS__CHORD(chordname, keyname, value)  \
    void keys__press__##name (void) {           \
        if (keys__chord__##chordname(true))     \
            kf__press(value);                   \
    }                                           \
    void keys__release__##name (void) {         \
        if (keys__chord__##chordname(false))    \
            kf__release(value);                 \
    }

// TODO: dunno if this is how we want to do things (or if it would even work)
#define  KEYS__MACRO(name, pressfunctions, releasefunctions)    \
    void keys__press__##name   (void) { pressfunctions }        \
    void keys__release__##name (void) { releasefunctions }      \

// the whole key
#define  K(name)   { &keys__press__##name, &keys__release__##name }

// just the press function of the key (without the preceding '&')
#define  KP(name)    keys__press__##name

// just the release function of the key (without the preceding '&')
#define  KR(name)    keys__release__##name

// TODO: and we could do a lot better than this too.  lol
void keys__chord__2kcaps(pressed, keycode) {  // TODO: check
    static counter = 0;
    if (pressed) {
        counter++;
        kf__press(keycode);
    }
    if (counter == 2) {
        kf__toggle_capslock();
    }
    if (!pressed) {
        counter--;
        kf__release(keycode);
    }
}
void keys__press__shL2kcaps(void) {
    keys__chord__2kcaps(true);
    kf__press(KEY__LeftShift);
}
void keys__release__shL2kcaps(void) {
    keys__chord__2kcaps(false);
    kf__release(KEY__LeftShift);
}
void keys__press__shR2kcaps(void) {
    keys__chord__2kcaps(true);
    kf__press(KEY__RightShift);
}
void keys__release__shR2kcaps(void) {
    keys__chord__2kcaps(false);
    kf__release(KEY__RightShift);
}



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

