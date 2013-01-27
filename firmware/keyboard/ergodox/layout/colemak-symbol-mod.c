/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * A Colemak layout (modified from the Kinesis layout).
 *
 * Implements the "layout" section of '.../firmware/keyboard.h'
 *
 * Notes:
 * - This layout *does not* contain a key mapped to the bootloader function.
 *   To reflash from this layout, you will need to physically press the button
 *   on the top right of the Teensy.
 *
 * History:
 * - Originally submitted by Jason Trill [jjt] (https://github.com/jjt) (who
 *   declined to be added to the copyright above).
 * - Transcribed by Ben Blazak when the layout format changed.
 *
 */


#include "../../../../firmware/keyboard/ergodox/matrix.h"
#include "./default/common.h"


// ----------------------------------------------------------------------------
// matrix control
// ----------------------------------------------------------------------------

#include "./default/exec_key.c.h"


// ----------------------------------------------------------------------------
// LED control
// ----------------------------------------------------------------------------

void kb__led__logical_on(char led) {
    switch led {
        case 'N': kb__led__on(1); break;  // numlock
        case 'C': kb__led__on(2); break;  // capslock
        case 'S': kb__led__on(3); break;  // scroll lock
        case 'O':                 break;  // compose
        case 'K':                 break;  // kana
    };
}

void kb__led__logical_off(char led) {
    switch led {
        case 'N': kb__led__off(1); break;  // numlock
        case 'C': kb__led__off(2); break;  // capslock
        case 'S': kb__led__off(3); break;  // scroll lock
        case 'O':                  break;  // compose
        case 'K':                  break;  // kana
    };
}


// ----------------------------------------------------------------------------
// keys
// ----------------------------------------------------------------------------

#include "./default/keys.h"

// layer
key_t L0pu1po  = { &kf__layer__push, 0x0001, &kf__layer__pop, 0x0001 };
key_t L1pu2    = { &kf__layer__push, 0x0102, NULL,                 0 };
key_t L1po     = { &kf__layer__pop,  0x0100, NULL,                 0 };
key_t L1pu2po  = { &kf__layer__push, 0x0102, &kf__layer__pop, 0x0102 };

// --- NumPush
const uint16_t PROGMEM NumPush__press[] = {
    2, &kf__layer__push, 0x0203,
       &kf__press, KEY__LockingNumLock };
key_t NumPush = { &kf__macro__progmem, &NumPush__press,
                  &kf__release, KEY__LockingNumLock };

// --- NumPop
const uint16_t PROGMEM NumPop__press[] = {
    2, &kf__layer__pop, 0x0203,
       &kf__press, KEY__LockingNumLock };
key_t NumPop = { &kf__macro__progmem, &NumPop__press,
                 &kf__release, KEY__LockingNumLock };

// --- NumPuPo
const uint16_t PROGMEM NumPuPo__press[] = {
    3, &kf__layer__push, 0x0203,
       &kf__press,   KEY__LockingNumLock,
       &kf__release, KEY__LockingNumLock };
const uint16_t PROGMEM NumPuPo__release[] = {
    3, &kf__layer__pop, 0x0203,
       &kf__press,   KEY__LockingNumLock,
       &kf__release, KEY__LockingNumLock };
key_t NumPuPo = { &kf__macro__progmem, &NumPuPo__press,
                  &kf__macro__progmem, &NumPuPo__release };


// ----------------------------------------------------------------------------
// layout
// ----------------------------------------------------------------------------

key_t layout[][KB__ROWS][KB__COLUMNS] = {

// ............................................................................

    MATRIX_LAYER(  // layer 0 : default (colemak)

// unused
NA,
// left hand ...... ......... ......... ......... ......... ......... .........
   Equal,       K1,       K2,       K3,       K4,       K5,    L1pu2,
     Tab,        Q,        W,        F,        P,        G,      Esc,
   CtrlL,        A,        R,        S,        T,        D,
Sh2KCapL,        Z,        X,        C,        V,        B,  L1pu2po,
    GUIL,    Grave,  Bkslash,     AltL,  L0pu1po,
                                                               CtrlL,     AltL,
                                                        NA,       NA,     Home,
                                                     Space,    Enter,      End,
// right hand ..... ......... ......... ......... ......... ......... .........
           NumPush,       K6,       K7,       K8,       K9,       K0,     Dash,
               Esc,        J,        L,        U,        Y,  Semicol,  Bkslash,
                           H,        N,        E,        I,        O,    Quote,
           NumPuPo,        K,        M,    Comma,   Period,    Slash, Sh2KCapR,
                               L0pu1po,   ArrowL,   ArrowD,   ArrowU,   ArrowR,
    AltR,    CtrlR,
   PageU,       NA,       NA,
   PageD,      Del,       Bs  ),

// ............................................................................

    MATRIX_LAYER(  // layer 1 : function and symbol keys
// unused
NA,
// left hand ...... ......... ......... ......... ......... ......... .........
  Transp,       F1,       F2,       F3,       F4,       F5,      F11,
  Transp,   BraceL,   BraceR,    BrktL,    BrktR,    Colon,   Transp,
  Transp,  Bkslash,    Slash,   ParenL,   ParenR,  Semicol,
  Transp,   Exclam,       At,    Pound,   Dollar,  Percent,   Transp,
  Transp,   Transp,   Transp,   Transp,   Transp,
                                                              Transp,   Transp,
                                                    Transp,   Transp,   Transp,
                                                    Transp,   Transp,   Transp,
// right hand ..... ......... ......... ......... ......... ......... .........
               F12,       F6,       F7,       F8,       F9,      F10,    Power,
            Transp,       NA,    Equal,     Plus,     Dash,  Undersc,       NA,
                      ArrowL,   ArrowD,   ArrowU,   ArrowR,       NA,       NA,
            Transp,    Caret,      Amp, Asterisk,   ParenL,   ParenR,   Transp,
                                Transp,   Transp,   Transp,   Transp,   Transp,
  Transp,   Transp,
  Transp,   Transp,   Transp,
  Transp,   Transp,   Transp  ),

// ............................................................................

    MATRIX_LAYER(  // layer 2 : QWERTY alphanum
// unused
NA,
// left hand ...... ......... ......... ......... ......... ......... .........
  Transp,       K1,       K2,       K3,       K4,       K5,     L1po,
  Transp,        Q,        W,        E,        R,        T,   Transp,
  Transp,        A,        S,        D,        F,        G,
  Transp,        Z,        X,        C,        V,        B,   Transp,
  Transp,   Transp,   Transp,   Transp,   Transp,   Transp,
                                                              Transp,   Transp,
                                                    Transp,   Transp,   Transp,
                                                    Transp,   Transp,   Transp,
// right hand ..... ......... ......... ......... ......... ......... .........
            Transp,       K6,       K7,       K8,       K9,       K0,   Transp,
            Transp,        Y,        U,        I,        O,        P,   Transp,
                           H,        J,        K,        L,  Semicol,   Transp,
            Transp,        N,        M,    Comma,   Period,    Slash,   Transp,
                                Transp,   Transp,   Transp,   Transp,   Transp,
  Transp,   Transp,
  Transp,   Transp,   Transp,
  Transp,   Transp,   Transp  ),


// ............................................................................

    MATRIX_LAYER(  // layer 3 : numpad
// unused
NA,
// left hand ...... ......... ......... ......... ......... ......... .........
  Transp,   Transp,   Transp,   Transp,   Transp,   Transp,   Transp,
  Transp,   Transp,   Transp,   Transp,   Transp,   Transp,   Transp,
  Transp,   Transp,   Transp,   Transp,   Transp,   Transp,
  Transp,   Transp,   Transp,   Transp,   Transp,   Transp,   Transp,
  Transp,      Ins,   Transp,   Transp,   Transp,
                                                              Transp,   Transp,
                                                    Transp,   Transp,   Transp,
                                                    Transp,   Transp,   Transp,
// right hand ..... ......... ......... ......... ......... ......... .........
            NumPop,   Transp,   NumPop,    Equal,    KPDiv,    KPMul,   Transp,
            Transp,   Transp,      KP7,      KP8,      KP9,    KPSub,   Transp,
                      Transp,      KP4,      KP5,      KP6,    KPAdd,   Transp,
            Transp,   Transp,      KP1,      KP2,      KP3,  KPEnter,   Transp,
                                Transp,   Transp,   Period,  KPEnter,   Transp,
  Transp,   Transp,
  Transp,   Transp,   Transp,
  Transp,   Transp,      KP0  ),

// ............................................................................
};

