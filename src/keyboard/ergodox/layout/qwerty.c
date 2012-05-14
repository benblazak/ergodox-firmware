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
#include "_defaults.h"  // for default layers and aliases


// error check; everything below assumes these dimensions
#if KB_LAYERS != 1 || KB_ROWS != 12 || KB_COLUMNS != 7
	#error "Expecting different keyboard dimensions"
#endif


uint8_t PROGMEM _kb_layout[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {
{  /* layer 0: default */
/* right hand */
/*        ---- 0 ---- ---- 1 ---- ---- 2 ---- ---- 3 ---- ---- 4 ---- ---- 5 ---- ---- 6 ----	*/
/* 0 */ {  NOP       , _6        , _7        , _8        , _9        , _0        , _dash      }, /* 0 */
/* 1 */ {  NOP       , _Y        , _U        , _I        , _O        , _P        , _bracketL  }, /* 1 */
/* 2 */ {  NA        , _H        , _J        , _K        , _L        , _semicolon, _quote     }, /* 2 */
/* 3 */ {  NOP       , _N        , _M        , _comma    , _period   , _slash    , _shiftR    }, /* 3 */
/* 4 */ {  NA        , NA        , _arrowU   , _arrowD   , _backslash, _bracketR , NOP        }, /* 4 */
/* 5 */ {  NA        , _ctrlR    , _altR     , _pageU    , _pageD    , _enter    , _space     }, /* 5 */
/*        ---- 0 ---- ---- 1 ---- ---- 2 ---- ---- 3 ---- ---- 4 ---- ---- 5 ---- ---- 6 ----	*/
/* left hand */
/*        ---- 0 ---- ---- 1 ---- ---- 2 ---- ---- 3 ---- ---- 4 ---- ---- 5 ---- ---- 6 ----	*/
/* 6 */ {  _equal    , _1        , _2        , _3        , _4        , _5        , NOP        }, /* 6 */
/* 7 */ {  _tab      , _Q        , _W        , _E        , _R        , _T        , NOP        }, /* 7 */
/* 8 */ {  _capsLock , _A        , _S        , _D        , _F        , _G        , NA         }, /* 8 */
/* 9 */ {  _shiftL   , _Z        , _X        , _C        , _V        , _B        , NOP        }, /* 9 */
/* A */ {  NOP       , _grave    , _backslash, _arrowL   , _arrowR   , NA        , NA         }, /* A */
/* B */ {  _bs       , _del      , _end      , _home     , _altL     , _ctrlL    , NA         }  /* B */
/*        ---- 0 ---- ---- 1 ---- ---- 2 ---- ---- 3 ---- ---- 4 ---- ---- 5 ---- ---- 6 ----	*/
}
};

kbfun_funptr_t PROGMEM _kb_layout_press[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {
/* layer 0: default */ DEFAULT_LAYER_PRESS
};

kbfun_funptr_t PROGMEM _kb_layout_release[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {
/* layer 0: default */ DEFAULT_LAYER_RELEASE
};

