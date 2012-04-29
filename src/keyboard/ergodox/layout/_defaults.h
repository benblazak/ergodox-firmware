/* ----------------------------------------------------------------------------
 * ergoDOX layout : default layers and aliases
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef _DEFAULTS_h
	#define _DEFAULTS_h
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


// aliases
#define NA     0     // for keys not available on the matrix
#define NOP    0     // for keys that do nothing
#define f_NA   NULL  // for functions not available on the matrix
#define f_NOP  NULL  // for functions that do nothing
// --- require "lib/key-functions.h"
#define f_press   &kbfun_press
#define f_release &kbfun_release


#define DEFAULT_LAYER_PRESS \
{ \
/* right hand */ \
/*        ---- 0 ---- ---- 1 ---- ---- 2 ---- ---- 3 ---- ---- 4 ---- ---- 5 ---- ---- 6 ----	*/ \
/* 0 */ {  f_press   , f_press   , f_press   , f_press   , f_press   , f_press   , f_press    }, /* 0 */ \
/* 1 */ {  f_press   , f_press   , f_press   , f_press   , f_press   , f_press   , f_press    }, /* 1 */ \
/* 2 */ {  f_NA      , f_press   , f_press   , f_press   , f_press   , f_press   , f_press    }, /* 2 */ \
/* 3 */ {  f_press   , f_press   , f_press   , f_press   , f_press   , f_press   , f_press    }, /* 3 */ \
/* 4 */ {  f_NA      , f_NA      , f_press   , f_press   , f_press   , f_press   , f_press    }, /* 4 */ \
/* 5 */ {  f_NA      , f_press   , f_press   , f_press   , f_press   , f_press   , f_press    }, /* 5 */ \
/*        ---- 0 ---- ---- 1 ---- ---- 2 ---- ---- 3 ---- ---- 4 ---- ---- 5 ---- ---- 6 ----	*/ \
/* left hand */ \
/*        ---- 0 ---- ---- 1 ---- ---- 2 ---- ---- 3 ---- ---- 4 ---- ---- 5 ---- ---- 6 ----	*/ \
/* 6 */ {  f_press   , f_press   , f_press   , f_press   , f_press   , f_press   , f_press    }, /* 6 */ \
/* 7 */ {  f_press   , f_press   , f_press   , f_press   , f_press   , f_press   , f_press    }, /* 7 */ \
/* 8 */ {  f_press   , f_press   , f_press   , f_press   , f_press   , f_press   , f_NA       }, /* 8 */ \
/* 9 */ {  f_press   , f_press   , f_press   , f_press   , f_press   , f_press   , f_press    }, /* 9 */ \
/* A */ {  f_press   , f_press   , f_press   , f_press   , f_press   , f_NA      , f_NA       }, /* A */ \
/* B */ {  f_press   , f_press   , f_press   , f_press   , f_press   , f_press   , f_NA       }  /* B */ \
/*        ---- 0 ---- ---- 1 ---- ---- 2 ---- ---- 3 ---- ---- 4 ---- ---- 5 ---- ---- 6 ----	*/ \
}

#define DEFAULT_LAYER_RELEASE \
{ \
/* right hand */ \
/*        ---- 0 ---- ---- 1 ---- ---- 2 ---- ---- 3 ---- ---- 4 ---- ---- 5 ---- ---- 6 ----	*/ \
/* 0 */ {  f_release , f_release , f_release , f_release , f_release , f_release , f_release  }, /* 0 */ \
/* 1 */ {  f_release , f_release , f_release , f_release , f_release , f_release , f_release  }, /* 1 */ \
/* 2 */ {  f_NA      , f_release , f_release , f_release , f_release , f_release , f_release  }, /* 2 */ \
/* 3 */ {  f_release , f_release , f_release , f_release , f_release , f_release , f_release  }, /* 3 */ \
/* 4 */ {  f_NA      , f_NA      , f_release , f_release , f_release , f_release , f_release  }, /* 4 */ \
/* 5 */ {  f_NA      , f_release , f_release , f_release , f_release , f_release , f_release  }, /* 5 */ \
/*        ---- 0 ---- ---- 1 ---- ---- 2 ---- ---- 3 ---- ---- 4 ---- ---- 5 ---- ---- 6 ----	*/ \
/* left hand */ \
/*        ---- 0 ---- ---- 1 ---- ---- 2 ---- ---- 3 ---- ---- 4 ---- ---- 5 ---- ---- 6 ----	*/ \
/* 6 */ {  f_release , f_release , f_release , f_release , f_release , f_release , f_release  }, /* 6 */ \
/* 7 */ {  f_release , f_release , f_release , f_release , f_release , f_release , f_release  }, /* 7 */ \
/* 8 */ {  f_release , f_release , f_release , f_release , f_release , f_release , f_NA       }, /* 8 */ \
/* 9 */ {  f_release , f_release , f_release , f_release , f_release , f_release , f_release  }, /* 9 */ \
/* A */ {  f_release , f_release , f_release , f_release , f_release , f_NA      , f_NA       }, /* A */ \
/* B */ {  f_release , f_release , f_release , f_release , f_release , f_release , f_NA       }  /* B */ \
/*        ---- 0 ---- ---- 1 ---- ---- 2 ---- ---- 3 ---- ---- 4 ---- ---- 5 ---- ---- 6 ----	*/ \
}


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif

