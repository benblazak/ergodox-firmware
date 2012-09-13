/* ----------------------------------------------------------------------------
 * ergoDOX layout : QWERTY
 *
 * This is an overly basic implementation.  It needs to be replaced.
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include <avr/pgmspace.h>
#include "lib/data-types.h"
#include "lib/usb/usage-page/keyboard--short-names.h"
#include "lib/key-functions.h"

#include "../matrix.h"
#include "../layout.h"


// aliases
#define f_prrel &kbfun_press_release
#define f_toggl &kbfun_toggle
#define f_l_inc &kbfun_layer_inc
#define f_l_dec &kbfun_layer_dec
#define f_l_iex &kbfun_layer_inc_exec
#define f_l_dex &kbfun_layer_dec_exec
#define f_2kcap &kbfun_2_keys_capslock_press_release
#define f_np_to &kbfun_layermask_numpad_toggle
#define f_np_on &kbfun_layermask_numpad_on
#define f_np_of &kbfun_layermask_numpad_off
#define f_btldr &kbfun_jump_to_bootloader



uint8_t PROGMEM _kb_layout[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {
// ----------------------------------------------------------------------------
	MATRIX_LAYER(  // layer 0: default
// unused
0,
// left hand
   _grave,      _1,      _2,      _3,      _4,      _5, _equal,
_bracketL,      _Q,      _W,      _E,      _R,      _T,   _esc,
     _tab,      _A,      _S,      _D,      _F,      _G,
  _shiftL,      _Z,      _X,      _C,      _V,      _B,      1,
    _guiL, _arrowL, _arrowU, _arrowD, _arrowR,
                                                       _bs,
                                                      _del,    _ctrlL,
                                                  _end, _home,  _altL,
// right hand
   _backslash,      _6,      _7,      _8,      _9,         _0,     _dash,
    _bracketL,      _Y,      _U,      _I,      _O,         _P, _bracketR,
                    _H,      _J,      _K,      _L, _semicolon,    _quote,
            1,      _N,      _M,  _comma, _period,     _slash,   _shiftR,
               _arrowL, _arrowD, _arrowU, _arrowR,      _guiR,
            _space,
_ctrlR,     _enter,
 _altR, _pageU, _pageD ),
// ----------------------------------------------------------------------------
	MATRIX_LAYER(  // layer 1: function and symbol keys
// unused
0,
// left hand
-1,        _F1,        _F2,       _F3,       _F4,       _F5, _F11,
 0, _braceL_kp, _braceR_kp, _bracketL, _bracketR,         0, _esc,
 0, _semicolon,     _slash,     _dash,         0, _colon_kp,
 2,          0,          0,         0,         0,         0,    0,
 0,    _arrowL,    _arrowU,   _arrowD,   _arrowR,
                                                            _bs,
                                                           _del,    _ctrlL,
                                                       _end, _home,  _altL,
// right hand
      _F12,        _F6,     _F7,        _F8,        _F9,          _F10, 0,
         2,          0,   _dash,     _lt_kp,     _gt_kp, _currencyUnit, 0,
            _backslash,       0, _parenL_kp, _parenR_kp,        _equal, 0,
         0,    _mul_kp,       0,          0,          0,             0, 0,
                        _arrowL,    _arrowD,    _arrowU,       _arrowR, 0,
           _space,
_ctrlR,    _enter,
 _altR, _pageU, _pageD ),
// ----------------------------------------------------------------------------
	MATRIX_LAYER(  // layer 2: numpad
// unused
0,
// left hand
0,       0,       0,       0,       0,       0,       0, 
0,       0,       0,       0,       0,       0,       0, 
0,       0,       0,       0,       0,       0, 
0,       0,       0,       0,       0,       0,       0, 
0,       0,       0,       0,       0, 
                                                  0, 
                                                  0,           0, 
                                             0,       0,       0, 
// right hand
//------- ------- ------- ------- ------- ------- ------- 
         0,       0,   _7_kp,   _8_kp,   _9_kp, _div_kp,       0, 
         0,       0,   _4_kp,   _5_kp,   _6_kp, _mul_kp,       0, 
                  0,   _1_kp,   _2_kp,   _3_kp, _sub_kp,       0, 
         0,       0,   _0_kp, _period,       0, _add_kp,       0, 
                  0,       0,       0,       0,       0, 
              0, 
0,            0, 
0,       0,       0 )
// ----------------------------------------------------------------------------
};


kbfun_funptr_t PROGMEM _kb_layout_press[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {
// ----------------------------------------------------------------------------
	MATRIX_LAYER(  // layer 0: default
// unused
NULL,
// left hand
f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,
f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,
f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,
f_2kcap,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_l_inc,
f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,
                                           f_prrel,
                                           f_prrel,  f_prrel,
                                       f_prrel,f_prrel,f_prrel,
// right hand
       f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,
       f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,
               f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,
       f_l_inc,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_2kcap,
                       f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,
          f_prrel,
f_prrel,  f_prrel,
f_prrel,f_prrel,f_prrel ),
// ----------------------------------------------------------------------------
	MATRIX_LAYER(  // layer 1: function and symbol keys
// unused
NULL,
// left hand
f_btldr,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,
f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,
f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,
f_np_on,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,   NULL,
f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,
                                           f_prrel,
                                           f_prrel,  f_prrel,
                                       f_prrel,f_prrel,f_prrel,
// right hand
       f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,
       f_np_to,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,
               f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,
          NULL,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,
                       f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,
          f_prrel,
f_prrel,  f_prrel,
f_prrel,f_prrel,f_prrel ),
// ----------------------------------------------------------------------------
	MATRIX_LAYER(  // layer 2: numpad
// unused
NULL,
// left hand
   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
   NULL,   NULL,   NULL,   NULL,   NULL,
                                              NULL,
                                              NULL,     NULL,
                                          NULL,   NULL,   NULL,
// right hand
          NULL,   NULL,f_prrel,f_prrel,f_prrel,f_prrel,   NULL,
          NULL,   NULL,f_prrel,f_prrel,f_prrel,f_prrel,   NULL,
                  NULL,f_prrel,f_prrel,f_prrel,f_prrel,   NULL,
          NULL,   NULL,f_prrel,f_prrel,f_prrel,f_prrel,   NULL,
                          NULL,   NULL,   NULL,   NULL,   NULL,
             NULL,
   NULL,     NULL,
   NULL,   NULL,   NULL )
// ----------------------------------------------------------------------------
};


kbfun_funptr_t PROGMEM _kb_layout_release[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {
// ----------------------------------------------------------------------------
	MATRIX_LAYER(  // layer 0: default
// unused
NULL,
// left hand
f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,
f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,
f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,
f_2kcap,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_l_dec,
f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,
                                           f_prrel,
                                           f_prrel,  f_prrel,
                                       f_prrel,f_prrel,f_prrel,
// right hand
       f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,
       f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,
               f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,
       f_l_dec,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_2kcap,
                       f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,
          f_prrel,
f_prrel,  f_prrel,
f_prrel,f_prrel,f_prrel ),
// ----------------------------------------------------------------------------
	MATRIX_LAYER(  // layer 1: function and symbol keys
// unused
NULL,
// left hand
   NULL,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,
f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,
f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,
f_np_of,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,   NULL,
f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,
                                           f_prrel,
                                           f_prrel,  f_prrel,
                                       f_prrel,f_prrel,f_prrel,
// right hand
       f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,
          NULL,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,
               f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,
          NULL,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,
                       f_prrel,f_prrel,f_prrel,f_prrel,f_prrel,
          f_prrel,
f_prrel,  f_prrel,
f_prrel,f_prrel,f_prrel ),
// ----------------------------------------------------------------------------
	MATRIX_LAYER(  // layer 2: numpad
// unused
NULL,
// left hand
   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
   NULL,   NULL,   NULL,   NULL,   NULL,
                                              NULL,
                                              NULL,     NULL,
                                          NULL,   NULL,   NULL,
// right hand
          NULL,   NULL,f_prrel,f_prrel,f_prrel,f_prrel,   NULL,
          NULL,   NULL,f_prrel,f_prrel,f_prrel,f_prrel,   NULL,
                  NULL,f_prrel,f_prrel,f_prrel,f_prrel,   NULL,
          NULL,   NULL,f_prrel,f_prrel,f_prrel,f_prrel,   NULL,
                          NULL,   NULL,   NULL,   NULL,   NULL,
             NULL,
   NULL,     NULL,
   NULL,   NULL,   NULL ),
// ----------------------------------------------------------------------------
	MATRIX_LAYER(  // layer 3: nothing (just making sure unused functions
		       //   don't get compiled out)
// unused
NULL,
// other
f_prrel,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
f_toggl,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
f_l_inc,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
f_l_dec,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
f_l_iex,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
f_l_dex,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
f_2kcap,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
f_np_to,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
f_np_on,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
f_np_of,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
f_btldr,   NULL,   NULL,   NULL,   NULL,   NULL          )
// ----------------------------------------------------------------------------
};

