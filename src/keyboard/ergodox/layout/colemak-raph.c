/* ----------------------------------------------------------------------------
 * ergoDOX layout : COLEMAK (modified from the Kinesis layout)
 *
 * Submitted by Jason Trill [jjt] (https://github.com/jjt)
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


/*
generate json from source :
./gen-ui-info.py --current-date "2015-10-14 14:36:51+02:00" --git-commit-date "2015-10-14 14:36:51+02:00" --git-commit-id '6bdd71b' --map-file-path '../src/firmware.map' --source-code-path '../src/' --matrix-file-path '../src/keyboard/ergodox/matrix.h' --layout-file-path '../src/keyboard/ergodox/layout/colemak-raph.c' > layout.json

generate html from json : must be called in root
./build-scripts/gen-layout.py --ui-info-file ./build-scripts/layout.json > layout.html
*/


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
    // LAYOUT L0: SOFT CODED COLEMAK (OS IN colemak)
    KB_MATRIX_LAYER( 0,
    // left hand
    _esc,      _1,         _2,         _3,         _4,         _5,         _grave,
    _tab,      _Q,         _W,         _E,         _R,         _T,         0,
    0,         _A,         _S,         _D,         _F,         _G,
    _shiftL,   _Z,         _X,         _C,         _V,         _B,         0,
    _bracketL, _bracketR,  _ctrlL,     _altL,      _guiL,

                                                               0,          0,
                                                   0,          0,          0,
                                                   _space,     _enter,     0,

    // right hand
    _equal,     _6,         _7,         _8,         _9,         _0,         _dash,
    0,          _Y,         _U,         _I,         _O,         _P,         _backslash,
                _H,         _J,         _K,         _L,         _semicolon, _quote,
    0,          _N,         _M,         _comma,     _period,    _slash,     _shiftR,
                            _arrowL,    _arrowU,    _arrowD,    _arrowR,    0,

    _arrowU,    _arrowR,
    _arrowD,    0,          0,
    _arrowL,    _del,       _bs ),
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

    // LAYOUT L0: SOFT CODED COLEMAK (OS IN colemak)
    KB_MATRIX_LAYER( NULL,
    // left hand
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     NULL,
    NULL,       kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     NULL,
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,

                                                                NULL,       NULL,
                                                    NULL,       NULL,       NULL,
                                                    kprrel,     kprrel,     NULL,
    // right hand
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    NULL,       kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
                kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    NULL,       kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
                            kprrel,     kprrel,     kprrel,     kprrel,     NULL,

    kprrel,     kprrel,
    kprrel,     NULL,       NULL,
    kprrel,     kprrel,     kprrel ),
};

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

const void_funptr_t PROGMEM _kb_layout_release[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {

    // LAYOUT L0: SOFT CODED COLEMAK (OS IN colemak)
    KB_MATRIX_LAYER( NULL,
    // left hand
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     NULL,
    NULL,       kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     NULL,
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,

                                                                NULL,       NULL,
                                                    NULL,       NULL,       NULL,
                                                    kprrel,     kprrel,     NULL,
    // right hand
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    NULL,       kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
                kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    NULL,       kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
                            kprrel,     kprrel,     kprrel,     kprrel,     NULL,

    kprrel,     kprrel,
    kprrel,     NULL,       NULL,
    kprrel,     kprrel,     kprrel ),
};
