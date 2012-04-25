/* ----------------------------------------------------------------------------
 * ergoDOX layout : QWERTY
 *
 * This is an overly basic implementation.  It needs to be replaced.
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include "lib/_data-types.h"
#include "lib/_usb/keyboard-usage-page--short-names.h"

#include "key-functions.h"

#include "../matrix.h"
#include "../layout.h"


// aliases
#define NA     0     // for keys not available on the matrix
#define NOP    0     // for keys that do nothing
#define f_NA   NULL  // for functions not available on the matrix
#define f_NOP  NULL  // for functions that do nothing
// --- 
#define f_press   &kbfun_press
#define f_release &kbfun_release


// error check; everything below assumes these dimensions
#if KB_LAYERS != 1 || KB_ROWS != 12 || KB_COLUMNS != 7
	#error "Expecting different keyboard dimensions"
#endif


uint8_t kb_layout[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {
{  // layer 0: default
// right hand
/*        ---- 0 ---- ---- 1 ---- ---- 2 ---- ---- 3 ---- ---- 4 ---- ---- 5 ---- ---- 6 ----	*/
/* 0 */ {  NOP       , _6        , _7        , _8        , _9        , _0        , _dash      }, /* 0 */
/* 1 */ {  NOP       , _Y        , _U        , _I        , _O        , _P        , _bracketL  }, /* 1 */
/* 2 */ {  NA        , _H        , _J        , _K        , _L        , _semicolon, _quote     }, /* 2 */
/* 3 */ {  NOP       , _N        , _M        , _comma    , _period   , _slash    , _shiftR    }, /* 3 */
/* 4 */ {  NA        , NA        , _arrowU   , _arrowD   , _backslash, _bracketR , NOP        }, /* 4 */
/* 5 */ {  NA        , _ctrlR    , _altR     , _pageU    , _pageD    , _enter    , _space     }, /* 5 */
/*        ---- 0 ---- ---- 1 ---- ---- 2 ---- ---- 3 ---- ---- 4 ---- ---- 5 ---- ---- 6 ----	*/
// left hand
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

kbfun_funptr_t kb_layout_press[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {
{  // layer 0: default
// right hand
/*        ---- 0 ---- ---- 1 ---- ---- 2 ---- ---- 3 ---- ---- 4 ---- ---- 5 ---- ---- 6 ----	*/
/* 0 */ {  f_NOP     , f_press   , f_press   , f_press   , f_press   , f_press   , f_press    }, /* 0 */
/* 1 */ {  f_NOP     , f_press   , f_press   , f_press   , f_press   , f_press   , f_press    }, /* 1 */
/* 2 */ {  f_NA      , f_press   , f_press   , f_press   , f_press   , f_press   , f_press    }, /* 2 */
/* 3 */ {  f_NOP     , f_press   , f_press   , f_press   , f_press   , f_press   , f_press    }, /* 3 */
/* 4 */ {  f_NA      , f_NA      , f_press   , f_press   , f_press   , f_press   , f_NOP      }, /* 4 */
/* 5 */ {  f_NA      , f_press   , f_press   , f_press   , f_press   , f_press   , f_press    }, /* 5 */
/*        ---- 0 ---- ---- 1 ---- ---- 2 ---- ---- 3 ---- ---- 4 ---- ---- 5 ---- ---- 6 ----	*/
// left hand
/*        ---- 0 ---- ---- 1 ---- ---- 2 ---- ---- 3 ---- ---- 4 ---- ---- 5 ---- ---- 6 ----	*/
/* 6 */ {  f_press   , f_press   , f_press   , f_press   , f_press   , f_press   , f_NOP      }, /* 6 */
/* 7 */ {  f_press   , f_press   , f_press   , f_press   , f_press   , f_press   , f_NOP      }, /* 7 */
/* 8 */ {  f_press   , f_press   , f_press   , f_press   , f_press   , f_press   , f_NA       }, /* 8 */
/* 9 */ {  f_press   , f_press   , f_press   , f_press   , f_press   , f_press   , f_NOP      }, /* 9 */
/* A */ {  f_NOP     , f_press   , f_press   , f_press   , f_press   , f_NA      , f_NA       }, /* A */
/* B */ {  f_press   , f_press   , f_press   , f_press   , f_press   , f_press   , f_NA       }  /* B */
/*        ---- 0 ---- ---- 1 ---- ---- 2 ---- ---- 3 ---- ---- 4 ---- ---- 5 ---- ---- 6 ----	*/
}
};

kbfun_funptr_t kb_layout_release[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {
{  // layer 0: default
// right hand
/*        ---- 0 ---- ---- 1 ---- ---- 2 ---- ---- 3 ---- ---- 4 ---- ---- 5 ---- ---- 6 ----	*/
/* 0 */ {  f_NOP     , f_release , f_release , f_release , f_release , f_release , f_release  }, /* 0 */
/* 1 */ {  f_NOP     , f_release , f_release , f_release , f_release , f_release , f_release  }, /* 1 */
/* 2 */ {  f_NA      , f_release , f_release , f_release , f_release , f_release , f_release  }, /* 2 */
/* 3 */ {  f_NOP     , f_release , f_release , f_release , f_release , f_release , f_release  }, /* 3 */
/* 4 */ {  f_NA      , f_NA      , f_release , f_release , f_release , f_release , f_NOP      }, /* 4 */
/* 5 */ {  f_NA      , f_release , f_release , f_release , f_release , f_release , f_release  }, /* 5 */
/*        ---- 0 ---- ---- 1 ---- ---- 2 ---- ---- 3 ---- ---- 4 ---- ---- 5 ---- ---- 6 ----	*/
// left hand
/*        ---- 0 ---- ---- 1 ---- ---- 2 ---- ---- 3 ---- ---- 4 ---- ---- 5 ---- ---- 6 ----	*/
/* 6 */ {  f_release , f_release , f_release , f_release , f_release , f_release , f_NOP      }, /* 6 */
/* 7 */ {  f_release , f_release , f_release , f_release , f_release , f_release , f_NOP      }, /* 7 */
/* 8 */ {  f_release , f_release , f_release , f_release , f_release , f_release , f_NA       }, /* 8 */
/* 9 */ {  f_release , f_release , f_release , f_release , f_release , f_release , f_NOP      }, /* 9 */
/* A */ {  f_NOP     , f_release , f_release , f_release , f_release , f_NA      , f_NA       }, /* A */
/* B */ {  f_release , f_release , f_release , f_release , f_release , f_release , f_NA       }  /* B */
/*        ---- 0 ---- ---- 1 ---- ---- 2 ---- ---- 3 ---- ---- 4 ---- ---- 5 ---- ---- 6 ----	*/
}
};

