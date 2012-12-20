/* ----------------------------------------------------------------------------
 * ergoDOX layout : COLEMAK (modified from the Kinesis layout)
 * 
 * Submitted by Jason Trill [jjt] (https://github.com/jjt)
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include <stdint.h>
#include <stddef.h>
#include <avr/pgmspace.h>
#include "../../../lib/data-types/misc.h"
#include "../../../lib/usb/usage-page/keyboard--short-names.h"
#include "../../../lib/key-functions/public.h"
#include "../matrix.h"
#include "../layout.h"

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

const uint8_t PROGMEM _kb_layout[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {
    // LAYOUT L0: COLEMAK
    KB_MATRIX_LAYER( 0,
    // left hand
    _equal,     _1,         _2,         _3,         _4,         _5,         2,
    _tab,       _Q,         _W,         _F,         _P,         _G,         _esc,
    _ctrlL,     _A,         _R,         _S,         _T,         _D,
    _shiftL,    _Z,         _X,         _C,         _V,         _B,         2,
    _guiL,      _grave,     _backslash, _altL,      1,
    
                                                                _ctrlL,     _altL,
                                                    0,          0,          _home,
                                                    _space,     _enter,     _end,

    // right hand
    3,          _6,         _7,         _8,         _9,         _0,         _dash,
    _esc,       _J,         _L,         _U,         _Y,         _semicolon, _backslash,
                _H,         _N,         _E,         _I,         _O,         _quote,
    3,          _K,         _M,         _comma,     _period,    _slash,     _shiftR,
                            1,          _arrowL,    _arrowD,    _arrowU,    _arrowR,

    _altR,      _ctrlR,
    _pageU,     0,          0,
    _pageD,     _del,       _bs ),


    // LAYOUT L1: function and symbol keys
    KB_MATRIX_LAYER( 0,
    // left hand
    0,          _F1,        _F2,        _F3,        _F4,        _F5,        _F11,
    0,          _bracketL,  _bracketR,  _bracketL,  _bracketR,  _semicolon, 0,
    0,          _backslash, _slash,     _9,         _0,         _semicolon,
    0,          _1,         _2,         _3,         _4,         _5,         0,
    0,          0,          0,          0,          0,

                                                                0,          0,
                                                    0,          0,          0,
                                                    0,          0,          0,
    // right hand
    _F12,       _F6,        _F7,        _F8,        _F9,        _F10,       _power,
    0,          0,          _equal,     _equal,     _dash,      _dash,      0,
                _arrowL,    _arrowD,    _arrowU,    _arrowR,    0,          0,
    0,          _6,         _7,         _8,         _9,         _0,         _mute,
                            0,          0,          0,          0,          0,

    0,          0,
    0,          0,          0,
    0,          0,          0 ),


    // LAYOUT L2: QWERTY alphanum 
    KB_MATRIX_LAYER( 0,
    // left hand
    0,          _1,         _2,         _3,         _4,         _5,         0,
    0,          _Q,         _W,         _E,         _R,         _T,         0,
    0,          _A,         _S,         _D,         _F,         _G,
    0,          _Z,         _X,         _C,         _V,         _B,         0,
    0,          0,          0,          0,          0,

                                                                0,          0,
                                                    0,          0,          0,
                                                    0,          0,          0,
    // right hand
    0,          _6,         _7,         _8,         _9,         _0,         0,
    0,          _Y,         _U,         _I,         _O,         _P,         0, 
                _H,         _J,         _K,         _L,         _semicolon, 0,
    0,          _N,         _M,         _comma,     _period,    _slash,     0,
                            0,          0,          0,          0,          0,
                            
    0,          0,
    0,          0,          0,
    0,          0,          0 ),


    // LAYOUT L3: numpad
    KB_MATRIX_LAYER( 0,
    // left hand
    0,          0,          0,          0,          0,          0,          0,
    0,          0,          0,          0,          0,          0,          0,
    0,          0,          0,          0,          0,          0,
    0,          0,          0,          0,          0,          0,          0,
    0,          _insert,    0,          0,          0,

                                                                0,          0,
                                                    0,          0,          0,
                                                    0,          0,          0,
    // right hand
    3,          0,          3,          _equal_kp,  _div_kp,    _mul_kp,    0,
    0,          0,          _7_kp,      _8_kp,      _9_kp,      _sub_kp,    0,
                0,          _4_kp,      _5_kp,      _6_kp,      _add_kp,    0,
    0,          0,          _1_kp,      _2_kp,      _3_kp,      _enter_kp,  0,
                            0,          0,          _period,    _enter_kp,  0,

    0,          0,
    0,          0,          0,
    0,          0,          _0_kp ),

};

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

// aliases

// basic
#define  kprrel  &kbfun_press_release
#define  ktog    &kbfun_toggle
#define  ktrans  &kbfun_transparent
// --- layer push/pop functions
#define  lpush1   &kbfun_layer_push_1
#define  lpush2   &kbfun_layer_push_2
#define  lpush3   &kbfun_layer_push_3
#define  lpush4   &kbfun_layer_push_4
#define  lpush5   &kbfun_layer_push_5
#define  lpush6   &kbfun_layer_push_6
#define  lpush7   &kbfun_layer_push_7
#define  lpush8   &kbfun_layer_push_8
#define  lpush9   &kbfun_layer_push_9
#define  lpush10  &kbfun_layer_push_10
#define  lpop1    &kbfun_layer_pop_1
#define  lpop2    &kbfun_layer_pop_2
#define  lpop3    &kbfun_layer_pop_3
#define  lpop4    &kbfun_layer_pop_4
#define  lpop5    &kbfun_layer_pop_5
#define  lpop6    &kbfun_layer_pop_6
#define  lpop7    &kbfun_layer_pop_7
#define  lpop8    &kbfun_layer_pop_8
#define  lpop9    &kbfun_layer_pop_9
#define  lpop10   &kbfun_layer_pop_10
// ---

// device
#define  dbtldr  &kbfun_jump_to_bootloader

// special
#define  sshprre  &kbfun_shift_press_release
#define  s2kcap   &kbfun_2_keys_capslock_press_release
#define  slpunum  &kbfun_layer_push_numpad
#define  slponum  &kbfun_layer_pop_numpad

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

const void_funptr_t PROGMEM _kb_layout_press[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {

    // PRESS L0: COLEMAK
    KB_MATRIX_LAYER( NULL,
    // left hand
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     lpush2,
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     
    s2kcap,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     lpush2,
    kprrel,     kprrel,     kprrel,     kprrel,     lpush1,
    
                                                                kprrel,     kprrel,
                                                    NULL,       NULL,       kprrel,
                                                    kprrel,     kprrel,     kprrel,
    // right hand
    slpunum,    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
                kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    slpunum,    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     s2kcap,
                            lpush1,     kprrel,     kprrel,     kprrel,     kprrel,

    kprrel,     kprrel,
    kprrel,     NULL,       NULL,
    kprrel,     kprrel,     kprrel ),
    

    // PRESS L1: function and symbol keys
    KB_MATRIX_LAYER( NULL,
    // left hand
    NULL,       kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     ktrans,
    ktrans,     sshprre,    sshprre,    kprrel,     kprrel,     sshprre,    ktrans,
    ktrans,     kprrel,     kprrel,     sshprre,    sshprre,    kprrel,
    ktrans,     sshprre,    sshprre,    sshprre,    sshprre,    sshprre,    ktrans,
    ktrans,     ktrans,     ktrans,     ktrans,     ktrans,

                                                                ktrans,     ktrans,
                                                    ktrans,     ktrans,     ktrans,
                                                    ktrans,     ktrans,     ktrans,
    // right hand
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    ktrans,     kprrel,     kprrel,     sshprre,    kprrel,     sshprre,    kprrel,
                kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    ktrans,     sshprre,    sshprre,    sshprre,    sshprre,    sshprre,    ktrans,
                            ktrans,     ktrans,     ktrans,     ktrans,     ktrans,

    ktrans,     ktrans,
    ktrans,     ktrans,     ktrans,
    ktrans,     ktrans,     ktrans ),

    
    // PRESS L2: QWERTY 
    KB_MATRIX_LAYER( NULL,
    // left hand
    ktrans,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     lpop2,
    ktrans,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     ktrans,
    ktrans,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     
    ktrans,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     ktrans,
    ktrans,     ktrans,     ktrans,     ktrans,     ktrans,

                                                                ktrans,     ktrans,     
                                                    ktrans,     ktrans,     ktrans,
                                                    ktrans,     ktrans,     ktrans,
    // right hand
    ktrans,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     ktrans,
    ktrans,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     ktrans,
                kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     ktrans,
    ktrans,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     ktrans,
                            ktrans,     ktrans,     ktrans,     ktrans,     ktrans,

    ktrans,     ktrans,     
    ktrans,     ktrans,     ktrans,
    ktrans,     ktrans,     ktrans ),


    // PRESS L3: numpad
    KB_MATRIX_LAYER( NULL,
    // left hand
    ktrans,     ktrans,     ktrans,     ktrans,     ktrans,     ktrans,     ktrans,
    ktrans,     ktrans,     ktrans,     ktrans,     ktrans,     ktrans,     ktrans,
    ktrans,     ktrans,     ktrans,     ktrans,     ktrans,     ktrans,     
    ktrans,     ktrans,     ktrans,     ktrans,     ktrans,     ktrans,     ktrans,
    ktrans,     kprrel,     ktrans,     ktrans,     ktrans,

                                                                ktrans,     ktrans,     
                                                    ktrans,     ktrans,     ktrans,
                                                    ktrans,     ktrans,     ktrans,
    // right hand
    slponum,    ktrans,     slponum,    kprrel,     kprrel,     kprrel,     ktrans,
    ktrans,     ktrans,     kprrel,     kprrel,     kprrel,     kprrel,     ktrans,
                ktrans,     kprrel,     kprrel,     kprrel,     kprrel,     ktrans,
    ktrans,     ktrans,     kprrel,     kprrel,     kprrel,     kprrel,     ktrans,
                            ktrans,     ktrans,     kprrel,     kprrel,     ktrans,
                
    ktrans,     ktrans,
    ktrans,     ktrans,     ktrans,
    ktrans,     ktrans,     kprrel ),

};

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

const void_funptr_t PROGMEM _kb_layout_release[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {

    // RELEASE L0: COLEMAK
    KB_MATRIX_LAYER( NULL,
    // left hand
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     NULL,
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    s2kcap,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     lpop2,
    kprrel,     kprrel,     kprrel,     kprrel,     lpop1,

                                                                kprrel,     kprrel,
                                                    NULL,       NULL,       kprrel,
                                                    kprrel,     kprrel,     kprrel,
    // right hand
    NULL,       kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
                kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    slponum,    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     s2kcap,
                            lpop1,      kprrel,     kprrel,     kprrel,     kprrel,

    kprrel,     kprrel,
    kprrel,     NULL,       NULL,
    kprrel,     kprrel,     kprrel ),


    // RELEASE L1: function and symbol keys
    KB_MATRIX_LAYER( NULL,
    // left hand
    NULL,       kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    ktrans,     sshprre,    sshprre,    kprrel,     kprrel,     sshprre,    ktrans,
    ktrans,     kprrel,     kprrel,     sshprre,    sshprre,    kprrel,
    ktrans,     sshprre,    sshprre,    sshprre,    sshprre,    sshprre,    ktrans,
    ktrans,     ktrans,     ktrans,     ktrans,     ktrans,

                                                                ktrans,     ktrans,
                                                    ktrans,     ktrans,     ktrans,
                                                    ktrans,     ktrans,     ktrans,
    // right hand
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    ktrans,     kprrel,     kprrel,     sshprre,    kprrel,     sshprre,    kprrel,
                kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    ktrans,     sshprre,    sshprre,    sshprre,    sshprre,    sshprre,    ktrans,
                            ktrans,     ktrans,     ktrans,     ktrans,     ktrans,
                            
    ktrans,     ktrans,
    ktrans,     ktrans,     ktrans,
    ktrans,     ktrans,     ktrans ),


    // RELEASE L2: QWERTY
    KB_MATRIX_LAYER( NULL,
    // left hand
    ktrans,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     NULL,
    ktrans,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     ktrans,
    ktrans,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    ktrans,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     ktrans,
    ktrans,     ktrans,     ktrans,     ktrans,     ktrans,

                                                                ktrans,     ktrans,
                                                    ktrans,     ktrans,     ktrans,
                                                    ktrans,     ktrans,     ktrans,
    // right hand
    ktrans,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     ktrans,
    ktrans,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     ktrans,
                kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     ktrans,
    ktrans,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     ktrans,
                            ktrans,     ktrans,     ktrans,     ktrans,     ktrans,

    ktrans,     ktrans,
    ktrans,     ktrans,     ktrans,
    ktrans,     ktrans,     ktrans ),


    // RELEASE L3: numpad
    KB_MATRIX_LAYER( NULL,
    // left hand
    ktrans,     ktrans,     ktrans,     ktrans,     ktrans,     ktrans,     ktrans,
    ktrans,     ktrans,     ktrans,     ktrans,     ktrans,     ktrans,     ktrans,
    ktrans,     ktrans,     ktrans,     ktrans,     ktrans,     ktrans,
    ktrans,     ktrans,     ktrans,     ktrans,     ktrans,     ktrans,     ktrans,
    ktrans,     kprrel,     ktrans,     ktrans,     ktrans,

                                                                ktrans,     ktrans,
                                                    ktrans,     ktrans,     ktrans,
                                                    ktrans,     ktrans,     ktrans,
    // right hand
    NULL,       ktrans,     NULL,       kprrel,     kprrel,     kprrel,     ktrans,
    ktrans,     ktrans,     kprrel,     kprrel,     kprrel,     kprrel,     ktrans,
                ktrans,     kprrel,     kprrel,     kprrel,     kprrel,     ktrans,
    lpop3,      ktrans,     kprrel,     kprrel,     kprrel,     kprrel,     ktrans,
                            ktrans,     ktrans,     kprrel,     kprrel,     ktrans,

    ktrans,     ktrans,
    ktrans,     ktrans,     ktrans,
    ktrans,     ktrans,     kprrel ),


    // RELEASE L3: nothing (just making sure unused
    // functions don't get compiled out)
    KB_MATRIX_LAYER( NULL,
    // other
    kprrel, lpush8, lpop8,  NULL,   NULL,   NULL,   NULL,   NULL,
    ktog,   lpush9, lpop9,  NULL,   NULL,   NULL,   NULL,   NULL,
    ktrans, lpush10,lpop10, NULL,   NULL,   NULL,   NULL,   NULL,
    lpush1, lpop1,  NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
    lpush2, lpop2,  dbtldr, NULL,   NULL,   NULL,   NULL,   NULL,
    lpush3, lpop3,  NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
    lpush4, lpop4,  s2kcap, NULL,   NULL,   NULL,   NULL,   NULL,
    lpush5, lpop5,  slpunum,NULL,   NULL,   NULL,   NULL,   NULL,
    lpush6, lpop6,  slponum,NULL,   NULL,   NULL,   NULL,   NULL,
    lpush7, lpop7,  NULL,   NULL,   NULL,   NULL,   NULL,   NULL )

};

