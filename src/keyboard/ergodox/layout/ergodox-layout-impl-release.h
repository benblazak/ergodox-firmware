/*
 * Redefines macros to implement the table of key release functions.
 *
 * Created by lotem <chen.sst@gmail.com>  2015-12-01
 *
 * Immediately following this file, again #include "your-ergodox-layout.h"
 */

#undef  CHORD
#undef  PUSH
#undef  POP
#undef  PUSHNUM
#undef  POPNUM
#undef  POPALL
#undef  BOOTLOADER

#define  CHORD(n)   &kbfun_layer_pop_##n
#define  PUSH(n)    NULL
#define  POP(n)     NULL
#define  PUSHNUM(n) NULL
#define  POPNUM(n)  NULL
#define  POPALL     NULL
#define  BOOTLOADER NULL

#undef ERGODOX_LAYOUT
#define ERGODOX_LAYOUT const void_funptr_t PROGMEM _kb_layout_release[KB_LAYERS][KB_ROWS][KB_COLUMNS]
