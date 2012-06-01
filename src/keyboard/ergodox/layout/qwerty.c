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

#define KEYBOARD_INCLUDE_PRIVATE
#include "../matrix.h"
#include "../layout.h"


// error check: everything below assumes these dimensions
#if KB_LAYERS != 1 || KB_ROWS != 12 || KB_COLUMNS != 7
	#error "Expecting different keyboard dimensions"
#endif


uint8_t PROGMEM _kb_layout[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {
	LAYER(  // layer 0: default
// unused
0,
// left hand
_grave,    _1,      _2,      _3,      _4,      _5,  _equal,
_tab,      _Q,      _W,      _E,      _R,      _T,  _esc,
_capsLock, _A,      _S,      _D,      _F,      _G,
_shiftL,   _Z,      _X,      _C,      _V,      _B,  _ctrlL,
_guiL,     _arrowL, _arrowU, _arrowD, _arrowR,
                                                 _bs,
                                                 _del,     _ctrlL,
                                              _end, _home, _altL,
// right hand
         _backslash, _6, _7,      _8,      _9,      _0,         _dash,
         _bracketL,  _Y, _U,      _I,      _O,      _P,         _bracketR,
                     _H, _J,      _K,      _L,      _semicolon, _quote,
         _ctrlR,     _N, _M,      _comma,  _period, _slash,     _shiftR,
                         _arrowL, _arrowD, _arrowU, _arrowR,    _guiR,
            _space,
_ctrlR,     _enter,
_altR,  _pageU, _pageD )
};


kbfun_funptr_t PROGMEM _kb_layout_press[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {
	LAYER_SET_ALL(NULL, &kbfun_press)  // layer 0: default
};


kbfun_funptr_t PROGMEM _kb_layout_release[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {
	LAYER_SET_ALL(NULL, &kbfun_release)  // layer 0: default
};

