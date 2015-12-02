/*
 * Implements an ergodox layout defined with the ERGODOX_LAYOUT macro.
 *
 * Created by lotem <chen.sst@gmail.com>  2015-12-01
 *
 * Usage:
 * Create a header file named "your-ergodox-layout.h", with the following
 * layout definition:
 *
 *     ERGODOX_LAYOUT = {
 *       ERGODOX_LAYER(
 *         // Define all the keys in the ergodox keyboard.
 *       ),
 *       // Repeat the ERGODOX_LAYER macro to add more layers.
 *     };
 *
 * Then in "your-ergodox-mod.c":
 *
 *     #include "ergodox-layout-impl.h"
 *     #include "your-ergodox-layout.h"
 *
 *     #include "ergodox-layout-impl-press.h"
 *     #include "your-ergodox-layout.h"
 *
 *     #include "ergodox-layout-impl-release.h"
 *     #include "your-ergodox-layout.h"
 */

/* Defines a keyboard layer. */
#define ERGODOX_LAYER( \
  /* left hand, spatial positions */ \
  k50,k51,k52,k53,k54,k55,k56, \
  k40,k41,k42,k43,k44,k45,k46, \
  k30,k31,k32,k33,k34,k35, \
  k20,k21,k22,k23,k24,k25,k26, \
  k10,k11,k12,k13,k14, \
                      k05,k06, \
                          k04, \
                  k03,k02,k01, \
 \
  /* right hand, spatial positions */ \
  k57,k58,k59,k5A,k5B,k5C,k5D, \
  k47,k48,k49,k4A,k4B,k4C,k4D, \
      k38,k39,k3A,k3B,k3C,k3D, \
  k27,k28,k29,k2A,k2B,k2C,k2D, \
          k19,k1A,k1B,k1C,k1D, \
  k07,k08, \
  k09, \
  k0C,k0B,k0A) \
/* matrix */ \
{ \
  { 0,  k01,k02,k03,k04,k05,k06,k07,k08,k09,k0A,k0B,k0C,0   }, \
  { k10,k11,k12,k13,k14,0,  0,  0,  0,  k19,k1A,k1B,k1C,k1D }, \
  { k20,k21,k22,k23,k24,k25,k26,k27,k28,k29,k2A,k2B,k2C,k2D }, \
  { k30,k31,k32,k33,k34,k35,0,  0,  k38,k39,k3A,k3B,k3C,k3D }, \
  { k40,k41,k42,k43,k44,k45,k46,k47,k48,k49,k4A,k4B,k4C,k4D }, \
  { k50,k51,k52,k53,k54,k55,k56,k57,k58,k59,k5A,k5B,k5C,k5D } \
}

/*
 * Macros used in the layout file to define individual keys.
 *
 * The following key macros are used as parameters to ERGODOX_LAYER to fill
 * the key code table.
 * They will be redefined later to implement the key press and release tables
 * respectively.
 *
 *     UNUSED      Unused key.
 *     __          Transparent; fallback to the previous layer.
 *     _(x)        Normal key.
 *     M(x)        Media key. Shorten the key name for easier alignment.
 *     S(x)        Key that automatically has the Shift modifier on.
 *     S2CAP(x)    Key that yields caps lock when two of the same keys are pressed.
 *     STICKY(n)   Stikey layer key.
 *     CHORD(n)    Chorded layer key.
 *     PUSH(n)     Push the specified layer.
 *     POP(n)      Pop the specified layer.
 *     PUSHNUM(n)  Push numpad layer.
 *     POPNUM(n)   Pop numpad layer.
 *     POPALL      Pop all layers.
 *     BOOTLOADER  Trigger bootloader.
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

#define  UNUSED     0
#define  __         0
#define  _(x)       x
#define  M(x)       MEDIAKEY_##x
#define  S(x)       x
#define  S2CAP(x)   x
#define  STICKY(n)  n
#define  CHORD(n)   n
#define  PUSH(n)    n
#define  POP(n)     n
#define  PUSHNUM(n) n
#define  POPNUM(n)  n
#define  POPALL     0
#define  BOOTLOADER 0

/* Defines the key code table. */
#define ERGODOX_LAYOUT const uint8_t PROGMEM _kb_layout[KB_LAYERS][KB_ROWS][KB_COLUMNS]

