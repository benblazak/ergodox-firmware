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

// the "press" function for "name"
#define  P(name)  keys__press__##name

// the "release" function for "name"
#define  R(name)  keys__release__##name

// the "chord" function for "name"
#define  C(name)  keys__chord__##name

// the "key"; for putting the keys into the layout matrix
#define  K(name)  { &P(name), &R(name) }

// the "function" for "name"
#define F(name)  keys__function__##name

// ----------------------------------------------------------------------------

// note: needed by ".../lib/layout/keys.h"
#define  KEYS__DEFAULT(name, value)             \
    void P(name) (void) { F(press)(value); }    \
    void R(name) (void) { F(release)(value); }

// note: needed by ".../lib/layout/keys.h"
#define  KEYS__SHIFTED(name, value)                         \
    void P(name) (void) { F(press)(KEY__LeftShift);         \
                          F(press)(value); }                \
    void R(name) (void) { F(release)(value);                \
                          F(release)(KEY__LeftShift); }

// note: for implementing chorded layouts such as asetniop (or chordmak)
// TODO: not sure if this is how we want to do this
#define  KEYS__CHORD__CHARACTER(name, threshold, keycode)   \
    void C(char__##name) (bool pressed) {                   \
        static counter = 0;                                 \
        if (pressed) {                                      \
            counter++;                                      \
        }                                                   \
        if (counter == (threshold) && !pressed) {           \
            F(press)(keycode);                              \
            usb__kb__send_report();                         \
            F(release)(keycode);                            \
        }                                                   \
        if (!pressed) {                                     \
            counter--;                                      \
        }                                                   \
    }
// TODO: dunno if this is right at all.....
#define  KEYS__CHORD__COMBINATION(name, threshold, names...)    \
    void C(comb__##name) (bool pressed) {                       \
        static counter = 0;                                     \
        if (pressed) {                                          \
            counter++;                                          \
        }                                                       \
        if (counter == (threshold) && !pressed) {               \
            names                                               \
        }                                                       \
        if (!pressed) {                                         \
            counter--;                                          \
        }                                                       \
    }

// ----------------------------------------------------------------------------

void F(press)   (uint8_t keycode) { usb__kb__set_key(true, keycode); }
void F(release) (uint8_t keycode) { usb__kb__set_key(false, keycode); }

void C(2_keys_caps)(bool pressed, uint8_t keycode) {
    static counter = 0;
    if (pressed) {
        counter++;
        kf__press(keycode);
    }
    if (counter == 2 && pressed) {
        kf__toggle_capslock();
    }
    if (!pressed) {
        counter--;
        kf__release(keycode);
    }
}

// ----------------------------------------------------------------------------

// --- default key definitions ------------------------------------------------

#include "../../../../firmware/lib/layout/keys.h"


// --- special meaning --------------------------------------------------------

// transp : transparent
#define  keys__press__transp    NULL
#define  keys__release__transp  NULL

// nop : no operation
void P(nop) (void) {}
void R(nop) (void) {}


// --- special keycode --------------------------------------------------------

KEYS__DEFAULT( power,    KEY__Power      );
KEYS__DEFAULT( volumeU,  KEY__VolumeUp   );
KEYS__DEFAULT( volumeD,  KEY__VolumeDown );
KEYS__DEFAULT( mute,     KEY__Mute       );


// --- special function -------------------------------------------------------

// shL2kcaps : left shift + toggle capslock (if both shifts are pressed)
void P(shL2kcaps) (void) { C(2_keys_caps)(true, KEY__LeftShift); }
void R(shL2kcaps) (void) { C(2_keys_caps)(false, KEY__LeftShift); }

// shR2kcaps : right shift + toggle capslock (if both shifts are pressed)
void P(shR2kcaps) (void) { C(2_keys_caps)(true, KEY__RightShift); }
void R(shR2kcaps) (void) { C()2_keys_caps(false, KEY__RightShift); }

// btldr : jump to the bootloader
void P(btldr) (void) { kf__jump_to_bootloader(); }
void R(btldr) (void) {}


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__KEYBOARD__ERGODOX__LAYOUT__DEFAULT__KEYS__H

