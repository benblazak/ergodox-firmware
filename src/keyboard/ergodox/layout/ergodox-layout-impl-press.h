/*
 * Redefines macros to implement the table of key press functions.
 *
 * Created by lotem <chen.sst@gmail.com>  2015-12-01
 *
 * Immediately following this file, again #include "your-ergodox-layout.h"
 */

#undef  UNUSED
#undef  __
#undef  _
#undef  M
#undef  S
#undef  S2CAP
#undef  STICKY
#undef  CHORD
#undef  PUSH
#undef  POP
#undef  PUSHNUM
#undef  POPNUM
#undef  POPALL
#undef  BOOTLOADER

#define  UNUSED     NULL
#define  __         &kbfun_transparent
#define  _(x)       &kbfun_press_release
#define  M(x)       &kbfun_mediakey_press_release
#define  S(x)       &kbfun_shift_press_release
#define  S2CAP(x)   &kbfun_2_keys_capslock_press_release
#define  STICKY(n)  &kbfun_layer_sticky_##n
#define  CHORD(n)   &kbfun_layer_push_##n
#define  PUSH(n)    &kbfun_layer_push_##n
#define  POP(n)     &kbfun_layer_pop_##n
#define  PUSHNUM(n) &kbfun_layer_push_numpad
#define  POPNUM(n)  &kbfun_layer_pop_numpad
#define  POPALL     &kbfun_layer_pop_all
#define  BOOTLOADER &kbfun_jump_to_bootloader

#undef ERGODOX_LAYOUT
#define ERGODOX_LAYOUT const void_funptr_t PROGMEM _kb_layout_press[KB_LAYERS][KB_ROWS][KB_COLUMNS]

