/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**
 * - description: |
 *   A QWERTY layout adapted from the default Kinesis layout.
 */


#include <stddef.h>
#include <avr/pgmspace.h>
#include "../../../../firmware/lib/layout/key-functions.h"
#include "../../../../firmware/lib/usb/usage-page/keyboard.h"
#include "../../../../firmware/keyboard.h"
#include "../../../../firmware/keyboard/ergodox/matrix.h"


// ----------------------------------------------------------------------------
// layout
// ----------------------------------------------------------------------------

#define  KEY_T  const kb__key_t * const PROGMEM

// needed by ".../lib/layout/keys.h"
#define  KEYS__DEFAULT(name, value)             \
        KEY_T name = {                          \
            .press_function   = &kf__press,     \
            .press_value      = value,          \
            .release_function = &kf__release,   \
            .release_value    = value,          \
        }

// needed by ".../lib/layout/keys.h"
#define  KEYS__SHIFTED(name, value)                     \
        const uint16_t PROGMEM name##__press[] = { 2,   \
            &kf__press, KEY__LeftShift,                 \
            &kf__press, value };                        \
        const uint16_t PROGMEM name##__release[] = { 2, \
            &kf__release, KEY__LeftShift,               \
            &kf__release, value };                      \
        KEY_T name = { &kf__macro, &name##__press,      \
                       &kf__macro, &name##__release }

// ----------------------------------------------------------------------------

// TODO
// - finish transcribing layout

// include default key definitions
#include "../../../../firmware/lib/layout/keys.h"

// special meaning
KEY_T Transp   = NULL;  // transparent
KEY_T NA       = { NULL, 0, NULL, 0 };  // do nothing
// special keycode
KEYS__DEFAULT( Power,    KEY__Power      );
KEYS__DEFAULT( VolumeU,  KEY__VolumeUp   );
KEYS__DEFAULT( VolumeD,  KEY__VolumeDown );
KEYS__DEFAULT( Mute,     KEY__Mute       );
// special function
#define  TWO_KEYS_CAPSLOCK  kf__two_keys_capslock_press_release
KEY_T Sh2KCapL = { &TWO_KEYS_CAPSLOCK, (1<<8)|KEY__LeftShift,
                   &TWO_KEYS_CAPSLOCK, (0<<8)|KEY__LeftShift };
KEY_T Sh2KCapR = { &TWO_KEYS_CAPSLOCK, (1<<8)|KEY__RightShift,
                   &TWO_KEYS_CAPSLOCK, (0<<8)|KEY__RightShift };
#undef  TWO_KEYS_CAPSLOCK
KEY_T Btldr    = { &kf__jump_to_bootloader, 0, NULL, 0 };
// TODO
KEY_T NumPush  = { &kf__layer__push, 0x23, NULL,              0 };
KEY_T NumPop   = { &kf__layer__pop,  0x2,  NULL,              0 };
// /TODO
// layer
KEY_T L0pu1    = { &kf__layer__push, 0x01, NULL,              0 };
KEY_T L0po     = { &kf__layer__pop,  0x0,  NULL,              0 };
KEY_T L0pu1po  = { &kf__layer__push, 0x01, &kf__layer__pop, 0x0 };
KEY_T L1pu2po  = { &kf__layer__push, 0x12, &kf__layer__pop, 0x1 };


// ----------------------------------------------------------------------------

KEY_T layout[][KB__ROWS][KB__COLUMNS] = {
// ----------------------------------------------------------------------------
    MATRIX__LAYER(  // layer 0 : default
// unused
NA,
// left hand ...... ......... ......... ......... ......... ......... .........
   Equal,       K1,       K2,       K3,       K4,       K5,      Esc,
 Bkslash,        Q,        W,        E,        R,        T,    L0pu1,
     Tab,        A,        S,        D,        F,        G,
Sh2KCapL,        Z,        X,        C,        V,        B,  L0pu1po,
    GUIL,    Grave,  Bkslash,   ArrowL,   ArrowR,
                                                               CtrlL,     AltL,
                                                        NA,       NA,     Home,
                                                        Bs,      Del,      End,
// right hand ..... ......... ......... ......... ......... ......... .........
           NumPush,       K6,       K7,       K8,       K9,       K0,     Dash,
             BrktL,        Y,        U,        I,        O,        P,    BrktR,
                           H,        J,        K,        L,  Semicol,    Slash,
           L0pu1po,        N,        M,    Comma,   Period,    Slash, Sh2KCapR,
                                ArrowL,   ArrowD,   ArrowU,   ArrowR,     GUIR,
    AltR,    CtrlR,
   PageU,  Nothing,       NA,
   PageD,    Enter,    Space  ),
// ----------------------------------------------------------------------------
    MATRIX__LAYER(  // layer 1 : function and symbol keys
// TODO: still checking this, especially for shifted keys
// unused
NA,
// left hand ...... ......... ......... ......... ......... ......... .........
      NA,       F1,       F2,       F3,       F4,       F5,      F11,
  Transp,   BraceL,   BraceR,    BrktL,    BrktR,       NA,     L0po,
  Transp,  Semicol,    Slash,     Dash,      KP0,  Semicol,
  Transp,      KP6,      KP7,      KP8,      KP9,    Equal,  L1pu2po,
  Transp,   Transp,   Transp,   Transp,   Transp,
                                                              Transp,   Transp,
                                                    Transp,   Transp,   Transp,
                                                    Transp,   Transp,   Transp,
// right hand ..... ......... ......... ......... ......... ......... .........
               F12,       F6,       F7,       F8,       F9,      F10,   Power,
            Transp,       NA,     Dash,    Comma,   Period,   Dollar,  VolumeU,
                     Bkslash,      KP1,   ParenL,   ParenR,    Equal,  VolumeD,
           L1pu2po, Asterisk,      KP2,      KP3,      KP4,      KP5,     Mute,
                                Transp,   Transp,   Transp,   Transp,   Transp,
  Transp,   Transp,
  Transp,   Transp,   Transp,
  Transp,   Transp,   Transp  ),
};


// ----------------------------------------------------------------------------
// LED control
// ----------------------------------------------------------------------------

// TODO
// - also, should this be moved to its own file?


// ----------------------------------------------------------------------------
// matrix control
// ----------------------------------------------------------------------------

// TODO
// - also, should this be moved to its own file?

