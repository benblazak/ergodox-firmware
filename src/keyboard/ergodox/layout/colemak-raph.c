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
#include "../../../main.h"

void kbfun_command_press_release(void) {
	_kbfun_press_release(main_arg_is_pressed, KEY_LeftGUI);
	kbfun_press_release();
}

void kbfun_command_alt_press_release(void) {
	_kbfun_press_release(main_arg_is_pressed, KEY_LeftGUI);
  _kbfun_press_release(main_arg_is_pressed, KEY_LeftAlt);
	kbfun_press_release();
}

void kbfun_command_alt_shift_press_release(void) {
	_kbfun_press_release(main_arg_is_pressed, KEY_LeftGUI);
  _kbfun_press_release(main_arg_is_pressed, KEY_LeftAlt);
  _kbfun_press_release(main_arg_is_pressed, KEY_LeftShift);
	kbfun_press_release();
}

void kbfun_command_shift_press_release(void) {
	_kbfun_press_release(main_arg_is_pressed, KEY_LeftGUI);
  _kbfun_press_release(main_arg_is_pressed, KEY_LeftShift);
	kbfun_press_release();
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

const uint8_t PROGMEM _kb_layout[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {
    // LAYOUT L0: SOFT CODED COLEMAK (OS IN colemak)
    KB_MATRIX_LAYER( 0,
    // left hand
    _esc,      _1,         _2,         _3,         _4,         _5,         _grave,
    _tab,      _Q,         _W,         _E,         _R,         _T,         1,
    _bs,       _A,         _S,         _D,         _F,         _G,
    _shiftL,   _Z,         _X,         _C,         _V,         _B,         0,
    2,         _ctrlL,     _altL,      _guiL,      1,

                                                               0,          0,
                                                   0,          0,          0,
                                                   _space,     _del,       0,

    // right hand
    _equal,     _6,         _7,         _8,         _9,         _0,         _dash,
    0,          _Y,         _U,         _I,         _O,         _P,         _backslash,
                _H,         _J,         _K,         _L,         _semicolon, _quote,
    0,          _N,         _M,         _comma,     _period,    _slash,     _shiftR,
                            _arrowL,    _arrowU,    _arrowD,    _arrowR,    0,

    _arrowU,    _arrowR,
    _arrowD,    0,          0,
    _arrowL,    _bs,        _enter),

    // LAYOUT L1: Programing (OS IN colemak)
    KB_MATRIX_LAYER( 0,
    // left hand
    0,      0,         0,         0,         0,         0,         0,
    0,      0,         0,         0,         0,         0,         0,
    0,      0,         0,         0,         0,         0,
    0,      0,         0,         0,         0,         0,         0,
    0,      0,         0,         0,         0,

                                                        0,         0,
                                             0,         0,         0,
                                             0,         0,         0,

    // right hand
    0,      0,         0,         0,         0,         0,         0,
    0,      _dash,     _bracketL, _bracketR, 0,         0,         0,
            _dash,     _bracketL, _bracketR, 0,         0,         0,
    0,      _equal,         _9,        _0,        0,         0,         0,
                       0,         0,         0,         0,         0,

    0,      0,
    0,      0,         0,
    0,      0,         0 ),

    // LAYOUT L2: Arrows/Xcode (OS IN colemak)
    KB_MATRIX_LAYER( 0,
    // left hand
    0,      0,         0,         0,         0,         0,         0,
    0,      0,         0,         0,         0,         0,         0,
    0,      0,         0,         0,         0,         0,
    0,      0,         0,         0,         0,         0,         0,
    0,      0,         0,         0,         0,

                                                        0,         0,
                                             0,         0,         0,
                                             0,         0,         0,

    // right hand
    0,      0,         0,         0,         0,         0,         0,
    0,      0,         0,         _arrowU,   0,         0,         0,
            0,         _arrowL,   _arrowD,   _arrowR,   0,         0,
    0,      0,         0,         0,         0,         0,         0,
                       KEY_F6,    KEY_F7,    KEY_F8,    0,         0,

    _enter, _O,
    _enter, 0,         0,
    _enter, _0,        _0),
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

// custom
#define ccoprre     &kbfun_command_press_release
#define ccoalprre   &kbfun_command_alt_press_release
#define ccoalshprre &kbfun_command_alt_shift_press_release
#define ccoshprre   &kbfun_command_shift_press_release

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

const void_funptr_t PROGMEM _kb_layout_press[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {

    // LAYOUT L0: SOFT CODED COLEMAK (OS IN colemak)
    KB_MATRIX_LAYER( NULL,
    // left hand
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     lpush1,
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     NULL,
    lpush2,     kprrel,     kprrel,     kprrel,     lpush1,

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

    // LAYOUT L1: Programing (OS IN colemak)
    KB_MATRIX_LAYER( NULL,
    // left hand
    NULL,     NULL,     NULL,     NULL,     NULL,     NULL,     NULL,
    NULL,     NULL,     NULL,     NULL,     NULL,     NULL,     NULL,
    NULL,     NULL,     NULL,     NULL,     NULL,     NULL,
    NULL,     NULL,     NULL,     NULL,     NULL,     NULL,     NULL,
    NULL,     NULL,     NULL,     NULL,     NULL,

                                                      NULL,     NULL,
                                            NULL,     NULL,     NULL,
                                            NULL,     NULL,     NULL,
    // right hand
    NULL,     NULL,     NULL,     NULL,     NULL,     NULL,     NULL,
    NULL,     sshprre,  sshprre,  sshprre,  NULL,     NULL,     NULL,
              kprrel,   kprrel,   kprrel,   NULL,     NULL,     NULL,
    NULL,     kprrel,   sshprre,  sshprre,  NULL,     NULL,     NULL,
                        NULL,     NULL,     NULL,     NULL,     NULL,

    NULL,     NULL,
    NULL,     NULL,     NULL,
    NULL,     NULL,     NULL ),

    // LAYOUT L2: Arrows/Xcode (OS IN colemak)
    KB_MATRIX_LAYER( NULL,
    // left hand
    NULL,     NULL,     NULL,     NULL,     NULL,     NULL,     NULL,
    NULL,     NULL,     NULL,     NULL,     NULL,     NULL,     NULL,
    NULL,     NULL,     NULL,     NULL,     NULL,     NULL,
    ktrans,   NULL,     NULL,     NULL,     NULL,     NULL,     NULL,
    NULL,     ktrans,   ktrans,   ktrans,   NULL,

                                                      NULL,     NULL,
                                            NULL,     NULL,     NULL,
                                            NULL,     NULL,     NULL,
    // right hand
    NULL,     NULL,     NULL,     NULL,     NULL,     NULL,     NULL,
    NULL,     NULL,     NULL,     kprrel,   NULL,     NULL,     NULL,
              NULL,     kprrel,   kprrel,   kprrel,   NULL,     NULL,
    NULL,     NULL,     NULL,     NULL,     NULL,     NULL,     ktrans,
                        kprrel,   kprrel,   kprrel,   NULL,     NULL,

    ccoprre,     ccoshprre,
    ccoalprre,   NULL,     NULL,
    ccoalshprre, ccoprre,  ccoalprre),
};

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

const void_funptr_t PROGMEM _kb_layout_release[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {

    // LAYOUT L0: SOFT CODED COLEMAK (OS IN colemak)
    KB_MATRIX_LAYER( NULL,
    // left hand
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     lpop1,
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     NULL,
    lpop2,       kprrel,     kprrel,     kprrel,     lpop1,

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

    // LAYOUT L1: Programing (OS IN colemak)
    KB_MATRIX_LAYER( NULL,
    // left hand
    NULL,     NULL,     NULL,     NULL,     NULL,     NULL,     NULL,
    NULL,     NULL,     NULL,     NULL,     NULL,     NULL,     NULL,
    NULL,     NULL,     NULL,     NULL,     NULL,     NULL,
    NULL,     NULL,     NULL,     NULL,     NULL,     NULL,     NULL,
    NULL,     NULL,     NULL,     NULL,     NULL,

                                                      NULL,     NULL,
                                            NULL,     NULL,     NULL,
                                            NULL,     NULL,     NULL,
    // right hand
    NULL,     NULL,     NULL,     NULL,     NULL,     NULL,     NULL,
    NULL,     sshprre,  sshprre,  sshprre,  NULL,     NULL,     NULL,
              kprrel,   kprrel,   kprrel,   NULL,     NULL,     NULL,
    NULL,     kprrel,   sshprre,  sshprre,  NULL,     NULL,     NULL,
                        NULL,     NULL,     NULL,     NULL,     NULL,

    NULL,     NULL,
    NULL,     NULL,     NULL,
    NULL,     NULL,     NULL ),

    // LAYOUT L2: Arrows/Xcode (OS IN colemak)
    KB_MATRIX_LAYER( NULL,
    // left hand
    NULL,     NULL,     NULL,     NULL,     NULL,     NULL,     NULL,
    NULL,     NULL,     NULL,     NULL,     NULL,     NULL,     NULL,
    NULL,     NULL,     NULL,     NULL,     NULL,     NULL,
    ktrans,   NULL,     NULL,     NULL,     NULL,     NULL,     NULL,
    NULL,     ktrans,   ktrans,   ktrans,   NULL,

                                                      NULL,     NULL,
                                            NULL,     NULL,     NULL,
                                            NULL,     NULL,     NULL,
    // right hand
    NULL,     NULL,     NULL,     NULL,     NULL,     NULL,     NULL,
    NULL,     NULL,     NULL,     kprrel,   NULL,     NULL,     NULL,
              NULL,     kprrel,   kprrel,   kprrel,   NULL,     NULL,
    NULL,     NULL,     NULL,     NULL,     NULL,     NULL,     ktrans,
                        kprrel,   kprrel,   kprrel,   NULL,     NULL,

    ccoprre,     ccoshprre,
    ccoalprre,   NULL,     NULL,
    ccoalshprre, ccoprre,  ccoalprre),
};
