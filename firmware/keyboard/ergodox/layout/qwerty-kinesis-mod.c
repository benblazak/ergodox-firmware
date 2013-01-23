/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**
 * - description: |
 *   A QWERTY layout adapted from the default Kinesis layout.  The position of
 *   the symbol keys on the function layer was taken from the Arensito layout.
 *
 *   Implements the "layout" section of '.../firmware/keyboard.h'
 */


#include "./default/common.h"
#include "./default/matrix.h"


// ----------------------------------------------------------------------------
// matrix control
// ----------------------------------------------------------------------------

#include "./default/exec_key.c.h"


// ----------------------------------------------------------------------------
// LED control
// ----------------------------------------------------------------------------

void kb__led__logical_on(char led) {
    switch(led) {
        case 'N': kb__led__on(1); break;  // numlock
        case 'C': kb__led__on(2); break;  // capslock
        case 'S': kb__led__on(3); break;  // scroll lock
        case 'O':                 break;  // compose
        case 'K':                 break;  // kana
    };
}

void kb__led__logical_off(char led) {
    switch(led) {
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
key_t L0pu1    = { &kf__layer__push, 0x0001, NULL,               0 };
key_t L0po     = { &kf__layer__pop,  0x00,   NULL,               0 };
key_t L0pu1po  = { &kf__layer__push, 0x0001, &kf__layer__pop, 0x00 };
key_t L1pu2po  = { &kf__layer__push, 0x0102, &kf__layer__pop, 0x01 };

// --- NumPush
const uint16_t PROGMEM NumPush__press[] = {
    2, &kf__layer__push, 0x0203,
       &kf__press, KEY__LockingNumLock };
key_t NumPush = { &kf__macro__progmem, &NumPush__press,
                  &kf__release, KEY__LockingNumLock };

// --- NumPop
const uint16_t PROGMEM NumPop__press[] = {
    2, &kf__layer__pop, 0x02,
       &kf__press, KEY__LockingNumLock };
key_t NumPop = { &kf__macro__progmem, &NumPop__press,
                 &kf__release, KEY__LockingNumLock };


// ----------------------------------------------------------------------------
// layout
// ----------------------------------------------------------------------------

key_t layout[][KB__ROWS][KB__COLUMNS] = {

// ............................................................................

    MATRIX_LAYER(  // layer 0 : default

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
                           H,        J,        K,        L,  Semicol,    Quote,
           L0pu1po,        N,        M,    Comma,   Period,    Slash, Sh2KCapR,
                                ArrowL,   ArrowD,   ArrowU,   ArrowR,     GUIR,
    AltR,    CtrlR,
   PageU,       NA,       NA,
   PageD,    Enter,    Space  ),

// ............................................................................

    MATRIX_LAYER(  // layer 1 : function and symbol keys
// unused
NA,
// left hand ...... ......... ......... ......... ......... ......... .........
      NA,       F1,       F2,       F3,       F4,       F5,      F11,
  Transp,   BraceL,   BraceR,    BrktL,    BrktR,       NA,     L0po,
  Transp,  Semicol,    Slash,     Dash,      KP0,    Colon,
  Transp,      KP6,      KP7,      KP8,      KP9,     Plus,  L1pu2po,
  Transp,   Transp,   Transp,   Transp,   Transp,
                                                              Transp,   Transp,
                                                    Transp,   Transp,   Transp,
                                                    Transp,   Transp,   Transp,
// right hand ..... ......... ......... ......... ......... ......... .........
               F12,       F6,       F7,       F8,       F9,      F10,    Power,
            Transp,       NA,  Undersc, LessThan, GrtrThan,   Dollar,  VolumeU,
                     Bkslash,      KP1,   ParenL,   ParenR,    Equal,  VolumeD,
           L1pu2po, Asterisk,      KP2,      KP3,      KP4,      KP5,     Mute,
                                Transp,   Transp,   Transp,   Transp,   Transp,
  Transp,   Transp,
  Transp,   Transp,   Transp,
  Transp,   Transp,   Transp  ),

// ............................................................................

    MATRIX_LAYER(  // layer 2 : keyboard functions
// unused
NA,
// left hand ...... ......... ......... ......... ......... ......... .........
   Btldr,       NA,       NA,       NA,       NA,       NA,       NA,
      NA,       NA,       NA,       NA,       NA,       NA,       NA,
      NA,       NA,       NA,       NA,       NA,       NA,
      NA,       NA,       NA,       NA,       NA,       NA,       NA,
      NA,       NA,       NA,       NA,       NA,
                                                                  NA,       NA,
                                                        NA,       NA,       NA,
                                                        NA,       NA,       NA,
// right hand ..... ......... ......... ......... ......... ......... .........
                NA,       NA,       NA,       NA,       NA,       NA,       NA,
                NA,       NA,       NA,       NA,       NA,       NA,       NA,
                          NA,       NA,       NA,       NA,       NA,       NA,
                NA,       NA,       NA,       NA,       NA,       NA,       NA,
                                    NA,       NA,       NA,       NA,       NA,
      NA,       NA,
      NA,       NA,       NA,
      NA,       NA,       NA  ),

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
            NumPop,   Transp,   NumPop,    Equal,    KPDiv,    KPMul,         
            Transp,   Transp,      KP7,      KP8,      KP9,    KPSub,   Transp,
                      Transp,      KP4,      KP5,      KP6,    KPAdd,   Transp,
            Transp,   Transp,      KP1,      KP2,      KP3,  KPEnter,   Transp,
                                Transp,   Transp,   Period,  KPEnter,   Transp,
  Transp,   Transp,
  Transp,   Transp,   Transp,
  Transp,   Transp,      KP0  ),

// ............................................................................
};

