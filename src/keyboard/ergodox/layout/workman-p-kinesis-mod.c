/* ----------------------------------------------------------------------------
* ergoDOX layout : Workman-P (modified from the Kinesis layout)
* -----------------------------------------------------------------------------
* Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
* Released under The MIT License (MIT) (see "license.md")
* Project located at <https://github.com/benblazak/ergodox-firmware>
* -------------------------------------------------------------------------- */

// TODO: there is a bug where if you hit an inverted key and a normal key, at
// the same time, when the 6 key buffer and modifier states are sent the
// inverted key's shift state can be used for the non-inverted key.
// Example: hit 1 and q at the same time in workman-p, you may end up with "!Q"
// instead of "!q".  Not sure how to fix this at present, but it may require
// sending two frames of updates to properly denote an order (shifted in one
// update, unshifted added in another, as though shift was released).

#include <stdint.h>
#include <stddef.h>
#include <avr/pgmspace.h>
#include "../../../lib/data-types/misc.h"
#include "../../../lib/usb/usage-page/keyboard--short-names.h"
#include "../../../lib/key-functions/public.h"
#include "../matrix.h"
#include "../layout.h"
#include "../../../main.h"

#define USING_WORKMAN_P // undef to use standard workman

// convenience macros
#define  LAYER         main_arg_layer
#define  LAYER_OFFSET  main_arg_layer_offset
#define  ROW           main_arg_row
#define  COL           main_arg_col
#define  IS_PRESSED    main_arg_is_pressed
#define  WAS_PRESSED   main_arg_was_pressed

// FUNCTIONS ------------------------------------------------------------------
void kbfun_layer_pop_all(void) {
  kbfun_layer_pop_1();
  kbfun_layer_pop_2();
  kbfun_layer_pop_3();
  kbfun_layer_pop_4();
  kbfun_layer_pop_5();
  kbfun_layer_pop_6();
  kbfun_layer_pop_7();
  kbfun_layer_pop_8();
  kbfun_layer_pop_9();
  kbfun_layer_pop_10();
}



static uint8_t inverted_keys_pressed;
static bool physical_lshift_pressed;
static bool physical_rshift_pressed;

void invert_shift_state() {
  // make lshift's state the inverted shift stated
  _kbfun_press_release(!(physical_lshift_pressed|physical_rshift_pressed), KEY_LeftShift);
  // release rshift
  _kbfun_press_release(false, KEY_RightShift);
}
void restore_shift_state() {
  // restore the state of left and right shift
  _kbfun_press_release(physical_lshift_pressed, KEY_LeftShift);
  _kbfun_press_release(physical_rshift_pressed, KEY_RightShift);
}

/*
 * [name]
 *   Invert shift + press|release
 *
 * [description]
 *   Generate a 'shift' press or release before the normal keypress or
 *   key release if shift is not pressed.  Generate a normal keypress or
 *   key release if shift is pressed.
 */
void kbfun_invert_shift_press_release(void) {
  if (IS_PRESSED) {
    ++inverted_keys_pressed;
    invert_shift_state();
  }

  kbfun_press_release();

  if (!IS_PRESSED) {
    // if this is the last key we're releasing
    if (inverted_keys_pressed == 1) {
      restore_shift_state();
    }
    // avoid underflow
    if (inverted_keys_pressed) {
      --inverted_keys_pressed;
    }
  }
}

/*
 * [name]
 *   Shift state fix + press|release
 *
 * [description]
 *   If no inverted keys are pressed, simply perform a press and release.
 *   If inverted keys are pressed, fix the shift state back to that of the
 *   physical keys before pressing the key.
 */
void kbfun_fix_shifted_press_release(void) {
  uint8_t keycode = kb_layout_get(LAYER, ROW, COL);
  switch (keycode) {
    // shift state toggles
    case KEY_LeftShift:
      physical_lshift_pressed = IS_PRESSED;
      break;
    case KEY_RightShift:
      physical_rshift_pressed = IS_PRESSED;
      break;
    // Keys which don't break it
    case KEY_CapsLock:
    case KEYPAD_NumLock_Clear:
      kbfun_press_release();
      return;
    default:
      // If we're not just changing the modifier, we need our true shift state.
      if (inverted_keys_pressed) {
        inverted_keys_pressed = 0;
        restore_shift_state();
      }
      kbfun_press_release();
      return;
  }
  // We only get here if we pressed left or right shift
  if (inverted_keys_pressed) {
    invert_shift_state();
  } else {
    kbfun_press_release();
  }
}

// DEFINITIONS ----------------------------------------------------------------
// basic
#define  mprrel   &kbfun_mediakey_press_release
#define  ktog     &kbfun_toggle
#define  ktrans   &kbfun_transparent
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
#define  lpop     &kbfun_layer_pop_all
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
// device
#define  dbtldr   &kbfun_jump_to_bootloader

// special
#define  sshprre  &kbfun_shift_press_release
#define  s2kcap   &kbfun_2_keys_capslock_press_release
#define  slpunum  &kbfun_layer_push_numpad
#define  slponum  &kbfun_layer_pop_numpad

// custom
#ifdef USING_WORKMAN_P
#define  sinvert  &kbfun_invert_shift_press_release
#define  kprrel   &kbfun_fix_shifted_press_release
#else
#define  kprrel   &kbfun_press_release
#define  sinvert  &kbfun_press_release
#endif
// ----------------------------------------------------------------------------

// LAYOUT ---------------------------------------------------------------------
const uint8_t PROGMEM _kb_layout[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {
// LAYER 0
KB_MATRIX_LAYER(
  // unused
  0 /*no key*/,
  // left hand
  KEY_Equal_Plus, KEY_1_Exclamation,     KEY_2_At,           KEY_3_Pound,   KEY_4_Dollar,   KEY_5_Percent, KEY_Application,  
  KEY_Tab,        KEY_q_Q,               KEY_d_D,            KEY_r_R,       KEY_w_W,        KEY_b_B,       1,  
  KEY_Escape,     KEY_a_A,               KEY_s_S,            KEY_h_H,       KEY_t_T,        KEY_g_G,       /*no key*/
  KEY_LeftShift,  KEY_z_Z,               KEY_x_X,            KEY_m_M,       KEY_c_C,        KEY_v_V,       KEY_LeftAlt,  
  KEY_LeftGUI,    KEY_GraveAccent_Tilde, KEY_Backslash_Pipe, KEY_LeftArrow, KEY_RightArrow, /*no key*/    /*no key*/
  // left thumb                                                                                                                        
  /*no key*/           KEY_LeftControl,   KEY_PrintScreen,  
  0 /*no key*/,        0 /*no key*/,      KEY_Home,  
  KEY_DeleteBackspace, KEY_DeleteForward, KEY_End,  

  // right hand
  2,            KEY_6_Caret, KEY_7_Ampersand, KEY_8_Asterisk,     KEY_9_LeftParenthesis,     KEY_0_RightParenthesis,      KEY_Dash_Underscore,
  1,            KEY_j_J,     KEY_f_F,         KEY_u_U,            KEY_p_P,                   KEY_Semicolon_Colon,         KEY_Backslash_Pipe,  
  /*no key*/    KEY_y_Y,     KEY_n_N,         KEY_e_E,            KEY_o_O,                   KEY_i_I,                     KEY_SingleQuote_DoubleQuote,  
  KEY_RightAlt, KEY_k_K,     KEY_l_L,         KEY_Comma_LessThan, KEY_Period_GreaterThan,    KEY_Slash_Question,          KEY_RightShift,  
  /*no key*/    /*no key*/   KEY_UpArrow,     KEY_DownArrow,      KEY_LeftBracket_LeftBrace, KEY_RightBracket_RightBrace, KEY_RightGUI,  
  // right thumb
  KEY_Pause,    KEY_RightControl, /*no key*/ 
  KEY_PageUp,   0 /*no key*/,     0 /*no key*/,
  KEY_PageDown, KEY_ReturnEnter,  KEY_Spacebar  
),
// LAYER 1
KB_MATRIX_LAYER(
  // unused
  0 /*no key*/,  
  // left hand
  KEY_CapsLock,  KEY_F1, KEY_F2, KEY_F3,              KEY_F4,              KEY_F5,    KEY_F11,  
  0,             0,      0,      0,                   0,                   0,         0,  
  0,             0,      0,      0,                   0,                   0,         /*no key*/
  0,             0,      0,      0,                   0,                   0,         0,  
  0,             0,      0,      MEDIAKEY_PREV_TRACK, MEDIAKEY_NEXT_TRACK, /*no key*/ /*no key*/ 
  // left thumb
  /* no key*/    0,            0,  
  0 /*no key*/,  0 /*no key*/, 0,  
  MEDIAKEY_STOP, 0,            0,  

  // right hand
  KEY_F12,   KEY_F6,    KEY_F7,                KEY_F8,                  KEY_F9,              KEY_F10, KEY_ScrollLock,  
  0,         0,         0,                     0,                       0,                   0,       0,  
  /*no key*/ 0,         0,                     0,                       0,                   0,       0,  
  0,         0,         0,                     0,                       0,                   0,       0,  
  /*no key*/ /*no key*/ MEDIAKEY_AUDIO_VOL_UP, MEDIAKEY_AUDIO_VOL_DOWN, MEDIAKEY_AUDIO_MUTE, 0,       3,  
  // right thumb
  0, 0,            /*no key*/ 
  0, 0 /*no key*/, 0 /*no key*/,  
  0, 0,            MEDIAKEY_PLAY_PAUSE 
),
// LAYER 2
KB_MATRIX_LAYER(
  // unused
  0 /*no key*/,
  // left hand
  0, 0, 0,          0, 0, 0,         0,  
  0, 0, 0,          0, 0, 0,         0,  
  0, 0, 0,          0, 0, 0,         /*no key*/ 
  0, 0, 0,          0, 0, 0,         0,  
  0, 0, KEY_Insert, 0, 0, /*no key*/ /*no key*/ 
  // left thumb
  /*no key*/    0,            0,  
  0 /*no key*/, 0 /*no key*/, 0,  
  0,            0,            0,  

  // right hand
  2,         0,         KEYPAD_NumLock_Clear, KEYPAD_Equal,       KEYPAD_Slash,         KEYPAD_Asterisk, 0,  
  0,         0,         KEYPAD_7_Home,        KEYPAD_8_UpArrow,   KEYPAD_9_PageUp,      KEYPAD_Minus,    0,  
  /*no key*/ 0,         KEYPAD_4_LeftArrow,   KEYPAD_5,           KEYPAD_6_RightArrow,  KEYPAD_Plus,     0,  
  0,         0,         KEYPAD_1_End,         KEYPAD_2_DownArrow, KEYPAD_3_PageDown,    KEY_ReturnEnter, 0,  
  /*no key*/ /*no key*/ 0,                    0,                  KEYPAD_Period_Delete, KEY_ReturnEnter, 0,  
  // right thumb
  0, 0,            /*no key*/ 
  0, 0 /*no key*/, 0 /*no key*/,  
  0, 0,            KEYPAD_0_Insert  
),
// LAYER 3
KB_MATRIX_LAYER(
  // unused
  0 /*no key*/,  
  // left hand
  0, 0,       0,       0,       0,       0,         0,  
  0, KEY_q_Q, KEY_w_W, KEY_e_E, KEY_r_R, KEY_t_T,   0,  
  0, KEY_a_A, KEY_s_S, KEY_d_D, KEY_f_F, KEY_g_G,   /*no key*/ 
  0, KEY_z_Z, KEY_x_X, KEY_c_C, KEY_v_V, KEY_b_B,   0,  
  0, 0,       0,       0,       0,       /*no key*/ /*no key*/
  // left thumb
  /*no key*/    0,            0,  
  0 /*no key*/, 0 /*no key*/, 0,  
  0,            0,            0,  

  // right hand
  0,         0,         0,       0,       0,       0,                   0,  
  0,         KEY_y_Y,   KEY_u_U, KEY_i_I, KEY_o_O, KEY_p_P,             0,  
  /*no key*/ KEY_h_H,   KEY_j_J, KEY_k_K, KEY_l_L, KEY_Semicolon_Colon, 0,  
  0,         KEY_n_N,   KEY_m_M, 0,       0,       0,                   0,  
  /*no key*/ /*no key*/ 0,       0,       0,       0,                   0,  
  // right thumb
  0, 0,            /*no key*/ 
  0, 0 /*no key*/, 0 /*no key*/,  
  0, 0,            0  
),
// LAYER 4
KB_MATRIX_LAYER(
  // unused
  0 /*no key*/,  
  // left hand
  0,  0,  0,  0,  0,  0,         0,  
  0,  0,  0,  0,  0,  0,         0,  
  0,  0,  0,  0,  0,  0,         /*no key*/
  0,  0,  0,  0,  0,  0,         0,  
  0,  0,  0,  0,  0,  /*no key*/ /*no key*/
  // left thumb
  /*no key*/    0,            0,  
  0 /*no key*/, 0 /*no key*/, 0,  
  0,            0,            0,  

  // right hand
  0,         0,         0, 0, 0, 0, 0,  
  0,         0,         0, 0, 0, 0, 0,  
  /*no key*/ 0,         0, 0, 0, 0, 0,  
  0,         0,         0, 0, 0, 0, 0,  
  /*no key*/ /*no key*/ 0, 0, 0, 0, 0,  
  // right thumb
  0, 0,            /*no key*/ 
  0, 0 /*no key*/, 0 /*no key*/,  
  0, 0,            0  
),
// LAYER 5
KB_MATRIX_LAYER(
  // unused
  0 /*no key*/,  
  // left hand
  0,  0,  0,  0,  0,  0,         0,  
  0,  0,  0,  0,  0,  0,         0,  
  0,  0,  0,  0,  0,  0,         /*no key*/
  0,  0,  0,  0,  0,  0,         0,  
  0,  0,  0,  0,  0,  /*no key*/ /*no key*/
  // left thumb
  /*no key*/    0,            0,  
  0 /*no key*/, 0 /*no key*/, 0,  
  0,            0,            0,  

  // right hand
  0,         0,         0, 0, 0, 0, 0,  
  0,         0,         0, 0, 0, 0, 0,  
  /*no key*/ 0,         0, 0, 0, 0, 0,  
  0,         0,         0, 0, 0, 0, 0,  
  /*no key*/ /*no key*/ 0, 0, 0, 0, 0,  
  // right thumb
  0, 0,            /*no key*/ 
  0, 0 /*no key*/, 0 /*no key*/,  
  0, 0,            0  
),
// LAYER 6
KB_MATRIX_LAYER(
  // unused
  0 /*no key*/,  
  // left hand
  0,  0,  0,  0,  0,  0,         0,  
  0,  0,  0,  0,  0,  0,         0,  
  0,  0,  0,  0,  0,  0,         /*no key*/
  0,  0,  0,  0,  0,  0,         0,  
  0,  0,  0,  0,  0,  /*no key*/ /*no key*/
  // left thumb
  /*no key*/    0,            0,  
  0 /*no key*/, 0 /*no key*/, 0,  
  0,            0,            0,  

  // right hand
  0,         0,         0, 0, 0, 0, 0,  
  0,         0,         0, 0, 0, 0, 0,  
  /*no key*/ 0,         0, 0, 0, 0, 0,  
  0,         0,         0, 0, 0, 0, 0,  
  /*no key*/ /*no key*/ 0, 0, 0, 0, 0,  
  // right thumb
  0, 0,            /*no key*/ 
  0, 0 /*no key*/, 0 /*no key*/,  
  0, 0,            0  
),
// LAYER 7
KB_MATRIX_LAYER(
  // unused
  0 /*no key*/,  
  // left hand
  0,  0,  0,  0,  0,  0,         0,  
  0,  0,  0,  0,  0,  0,         0,  
  0,  0,  0,  0,  0,  0,         /*no key*/
  0,  0,  0,  0,  0,  0,         0,  
  0,  0,  0,  0,  0,  /*no key*/ /*no key*/
  // left thumb
  /*no key*/    0,            0,  
  0 /*no key*/, 0 /*no key*/, 0,  
  0,            0,            0,  

  // right hand
  0,         0,         0, 0, 0, 0, 0,  
  0,         0,         0, 0, 0, 0, 0,  
  /*no key*/ 0,         0, 0, 0, 0, 0,  
  0,         0,         0, 0, 0, 0, 0,  
  /*no key*/ /*no key*/ 0, 0, 0, 0, 0,  
  // right thumb
  0, 0,            /*no key*/ 
  0, 0 /*no key*/, 0 /*no key*/,  
  0, 0,            0  
),
// LAYER 8
KB_MATRIX_LAYER(
  // unused
  0 /*no key*/,  
  // left hand
  0,  0,  0,  0,  0,  0,         0,  
  0,  0,  0,  0,  0,  0,         0,  
  0,  0,  0,  0,  0,  0,         /*no key*/
  0,  0,  0,  0,  0,  0,         0,  
  0,  0,  0,  0,  0,  /*no key*/ /*no key*/
  // left thumb
  /*no key*/    0,            0,  
  0 /*no key*/, 0 /*no key*/, 0,  
  0,            0,            0,  

  // right hand
  0,         0,         0, 0, 0, 0, 0,  
  0,         0,         0, 0, 0, 0, 0,  
  /*no key*/ 0,         0, 0, 0, 0, 0,  
  0,         0,         0, 0, 0, 0, 0,  
  /*no key*/ /*no key*/ 0, 0, 0, 0, 0,  
  // right thumb
  0, 0,            /*no key*/ 
  0, 0 /*no key*/, 0 /*no key*/,  
  0, 0,            0  
),
// LAYER 9
KB_MATRIX_LAYER(
  // unused
  0 /*no key*/,  
  // left hand
  0,  0,  0,  0,  0,  0,         0,  
  0,  0,  0,  0,  0,  0,         0,  
  0,  0,  0,  0,  0,  0,         /*no key*/
  0,  0,  0,  0,  0,  0,         0,  
  0,  0,  0,  0,  0,  /*no key*/ /*no key*/
  // left thumb
  /*no key*/    0,            0,  
  0 /*no key*/, 0 /*no key*/, 0,  
  0,            0,            0,  

  // right hand
  0,         0,         0, 0, 0, 0, 0,  
  0,         0,         0, 0, 0, 0, 0,  
  /*no key*/ 0,         0, 0, 0, 0, 0,  
  0,         0,         0, 0, 0, 0, 0,  
  /*no key*/ /*no key*/ 0, 0, 0, 0, 0,  
  // right thumb
  0, 0,            /*no key*/ 
  0, 0 /*no key*/, 0 /*no key*/,  
  0, 0,            0  
),
};
// ----------------------------------------------------------------------------

// PRESS ----------------------------------------------------------------------
const void_funptr_t PROGMEM _kb_layout_press[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {
// LAYER 0
KB_MATRIX_LAYER(
  // unused
  NULL /*no key*/,  
  // left hand
  kprrel, sinvert, sinvert, sinvert, sinvert, sinvert,   kprrel,  
  kprrel, kprrel,  kprrel,  kprrel,  kprrel,  kprrel,    lpush1,  
  kprrel, kprrel,  kprrel,  kprrel,  kprrel,  kprrel,    /*no key*/ 
  kprrel, kprrel,  kprrel,  kprrel,  kprrel,  kprrel,    kprrel,  
  kprrel, kprrel,  kprrel,  kprrel,  kprrel,  /*no key*/ /*no key*/ 
  // left thumb
  /*no key*/       kprrel,          kprrel,  
  NULL /*no key*/, NULL /*no key*/, kprrel,  
  kprrel,          kprrel,          kprrel,  

  // right hand
  lpush2,    sinvert,   sinvert, sinvert, sinvert, sinvert, kprrel,  
  lpush1,    kprrel,    kprrel,  kprrel,  kprrel,  kprrel,  kprrel,  
  /*no key*/ kprrel,    kprrel,  kprrel,  kprrel,  kprrel,  kprrel,  
  kprrel,    kprrel,    kprrel,  kprrel,  kprrel,  kprrel,  kprrel,  
  /*no key*/ /*no key*/ kprrel,  kprrel,  kprrel,  kprrel,  kprrel,  
  // right thumb
  kprrel, kprrel,          /*no key*/ 
  kprrel, NULL /*no key*/, NULL /*no key*/,  
  kprrel, kprrel,          kprrel  
),
// LAYER 1
KB_MATRIX_LAYER(
  // unused
  NULL /*no key*/,  
  // left hand
  kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,    kprrel,  
  ktrans, ktrans, ktrans, ktrans, ktrans, ktrans,    ktrans,  
  ktrans, ktrans, ktrans, ktrans, ktrans, ktrans,    /*no key*/
  ktrans, ktrans, ktrans, ktrans, ktrans, ktrans,    ktrans,  
  lpop,   ktrans, ktrans, mprrel, mprrel, /*no key*/ /*no key*/ 
  // left thumb
  /*no key*/       ktrans,          ktrans,  
  NULL /*no key*/, NULL /*no key*/, ktrans,  
  mprrel,          ktrans,          ktrans,  

  // right hand
  kprrel,    kprrel,    kprrel, kprrel, kprrel, kprrel, kprrel,  
  ktrans,    ktrans,    ktrans, ktrans, ktrans, ktrans, ktrans,  
  /*no key*/ ktrans,    ktrans, ktrans, ktrans, ktrans, ktrans,  
  ktrans,    ktrans,    ktrans, ktrans, ktrans, ktrans, ktrans,  
  /*no key*/ /*no key*/ mprrel, mprrel, mprrel, ktrans, lpush3,  
  // right thumb
  ktrans, ktrans,          /*no key*/ 
  ktrans, NULL /*no key*/, NULL /*no key*/,  
  ktrans, ktrans,          mprrel  
),
// LAYER 2
KB_MATRIX_LAYER(
  // unused
  NULL /*no key*/,  
  // left hand
  ktrans, ktrans, ktrans, ktrans, ktrans, ktrans,    ktrans,  
  ktrans, ktrans, ktrans, ktrans, ktrans, ktrans,    ktrans,  
  ktrans, ktrans, ktrans, ktrans, ktrans, ktrans,    /*no key*/
  ktrans, ktrans, ktrans, ktrans, ktrans, ktrans,    ktrans,  
  ktrans, ktrans, kprrel, ktrans, ktrans, /*no key*/ /*no key*/
  // left thumb
  /*no key*/       ktrans,          ktrans,  
  NULL /*no key*/, NULL /*no key*/, ktrans,  
  ktrans,          ktrans,          ktrans,  

  // right hand
  lpop2,     ktrans,    kprrel, kprrel, kprrel, kprrel, ktrans,  
  ktrans,    ktrans,    kprrel, kprrel, kprrel, kprrel, ktrans,  
  /*no key*/ ktrans,    kprrel, kprrel, kprrel, kprrel, ktrans, 
  ktrans,    ktrans,    kprrel, kprrel, kprrel, kprrel, ktrans,  
  /*no key*/ /*no key*/ ktrans, ktrans, kprrel, kprrel, ktrans,  
  // right thumb
  ktrans, ktrans,          /*no key*/ 
  ktrans, NULL /*no key*/, NULL /*no key*/,  
  ktrans, ktrans,          kprrel  
),
// LAYER 3
KB_MATRIX_LAYER(
  // unused
  NULL /*no key*/,  
  // left hand
  ktrans, ktrans, ktrans, ktrans, ktrans, ktrans,    ktrans,  
  ktrans, kprrel, kprrel, kprrel, kprrel, kprrel,    ktrans,  
  ktrans, kprrel, kprrel, kprrel, kprrel, kprrel,    /*no key*/
  ktrans, kprrel, kprrel, kprrel, kprrel, kprrel,    ktrans,  
  ktrans, ktrans, ktrans, ktrans, ktrans, /*no key*/ /*no key*/
  // left thumb
  /*no key*/       ktrans,          ktrans,  
  NULL /*no key*/, NULL /*no key*/, ktrans,  
  ktrans,          ktrans,          ktrans,  

  // right hand
  ktrans,    ktrans,    ktrans, ktrans, ktrans, ktrans, ktrans,  
  ktrans,    kprrel,    kprrel, kprrel, kprrel, kprrel, ktrans,  
  /*no key*/ kprrel,    kprrel, kprrel, kprrel, kprrel, ktrans,  
  ktrans,    kprrel,    kprrel, ktrans, ktrans, ktrans, ktrans,  
  /*no key*/ /*no key*/ ktrans, ktrans, ktrans, ktrans, ktrans,  
  // right thumb
  ktrans, ktrans,          /*no key*/ 
  ktrans, NULL /*no key*/, NULL /*no key*/,  
  ktrans, ktrans,          ktrans  
),
// LAYER 4
KB_MATRIX_LAYER(
  // unused
  NULL /*no key*/,  
  // left hand
  NULL, NULL, NULL, NULL, NULL, NULL,      NULL,  
  NULL, NULL, NULL, NULL, NULL, NULL,      NULL,  
  NULL, NULL, NULL, NULL, NULL, NULL,      /*no key*/ 
  NULL, NULL, NULL, NULL, NULL, NULL,      NULL,  
  NULL, NULL, NULL, NULL, NULL, /*no key*/ /*no key*/
  // left thumb
  /*no key*/       NULL,            NULL,  
  NULL /*no key*/, NULL /*no key*/, NULL,  
  NULL,            NULL,            NULL,  

  // right hand
  NULL,      NULL,      NULL, NULL, NULL, NULL, NULL,  
  NULL,      NULL,      NULL, NULL, NULL, NULL, NULL,  
  /*no key*/ NULL,      NULL, NULL, NULL, NULL, NULL,  
  NULL,      NULL,      NULL, NULL, NULL, NULL, NULL,  
  /*no key*/ /*no key*/ NULL, NULL, NULL, NULL, NULL,  
  // right thumb
  NULL, NULL,            /*no key*/ 
  NULL, NULL /*no key*/, NULL /*no key*/,  
  NULL, NULL,            NULL  
),
// LAYER 5
KB_MATRIX_LAYER(
  // unused
  NULL /*no key*/,  
  // left hand
  NULL, NULL, NULL, NULL, NULL, NULL,      NULL,  
  NULL, NULL, NULL, NULL, NULL, NULL,      NULL,  
  NULL, NULL, NULL, NULL, NULL, NULL,      /*no key*/ 
  NULL, NULL, NULL, NULL, NULL, NULL,      NULL,  
  NULL, NULL, NULL, NULL, NULL, /*no key*/ /*no key*/
  // left thumb
  /*no key*/       NULL,            NULL,  
  NULL /*no key*/, NULL /*no key*/, NULL,  
  NULL,            NULL,            NULL,  

  // right hand
  NULL,      NULL,      NULL, NULL, NULL, NULL, NULL,  
  NULL,      NULL,      NULL, NULL, NULL, NULL, NULL,  
  /*no key*/ NULL,      NULL, NULL, NULL, NULL, NULL,  
  NULL,      NULL,      NULL, NULL, NULL, NULL, NULL,  
  /*no key*/ /*no key*/ NULL, NULL, NULL, NULL, NULL,  
  // right thumb
  NULL, NULL,            /*no key*/ 
  NULL, NULL /*no key*/, NULL /*no key*/,  
  NULL, NULL,            NULL  
),
// LAYER 6
KB_MATRIX_LAYER(
  // unused
  NULL /*no key*/,  
  // left hand
  NULL, NULL, NULL, NULL, NULL, NULL,      NULL,  
  NULL, NULL, NULL, NULL, NULL, NULL,      NULL,  
  NULL, NULL, NULL, NULL, NULL, NULL,      /*no key*/ 
  NULL, NULL, NULL, NULL, NULL, NULL,      NULL,  
  NULL, NULL, NULL, NULL, NULL, /*no key*/ /*no key*/
  // left thumb
  /*no key*/       NULL,            NULL,  
  NULL /*no key*/, NULL /*no key*/, NULL,  
  NULL,            NULL,            NULL,  

  // right hand
  NULL,      NULL,      NULL, NULL, NULL, NULL, NULL,  
  NULL,      NULL,      NULL, NULL, NULL, NULL, NULL,  
  /*no key*/ NULL,      NULL, NULL, NULL, NULL, NULL,  
  NULL,      NULL,      NULL, NULL, NULL, NULL, NULL,  
  /*no key*/ /*no key*/ NULL, NULL, NULL, NULL, NULL,  
  // right thumb
  NULL, NULL,            /*no key*/ 
  NULL, NULL /*no key*/, NULL /*no key*/,  
  NULL, NULL,            NULL  
),
// LAYER 7
KB_MATRIX_LAYER(
  // unused
  NULL /*no key*/,  
  // left hand
  NULL, NULL, NULL, NULL, NULL, NULL,      NULL,  
  NULL, NULL, NULL, NULL, NULL, NULL,      NULL,  
  NULL, NULL, NULL, NULL, NULL, NULL,      /*no key*/ 
  NULL, NULL, NULL, NULL, NULL, NULL,      NULL,  
  NULL, NULL, NULL, NULL, NULL, /*no key*/ /*no key*/
  // left thumb
  /*no key*/       NULL,            NULL,  
  NULL /*no key*/, NULL /*no key*/, NULL,  
  NULL,            NULL,            NULL,  

  // right hand
  NULL,      NULL,      NULL, NULL, NULL, NULL, NULL,  
  NULL,      NULL,      NULL, NULL, NULL, NULL, NULL,  
  /*no key*/ NULL,      NULL, NULL, NULL, NULL, NULL,  
  NULL,      NULL,      NULL, NULL, NULL, NULL, NULL,  
  /*no key*/ /*no key*/ NULL, NULL, NULL, NULL, NULL,  
  // right thumb
  NULL, NULL,            /*no key*/ 
  NULL, NULL /*no key*/, NULL /*no key*/,  
  NULL, NULL,            NULL  
),
// LAYER 8
KB_MATRIX_LAYER(
  // unused
  NULL /*no key*/,  
  // left hand
  NULL, NULL, NULL, NULL, NULL, NULL,      NULL,  
  NULL, NULL, NULL, NULL, NULL, NULL,      NULL,  
  NULL, NULL, NULL, NULL, NULL, NULL,      /*no key*/ 
  NULL, NULL, NULL, NULL, NULL, NULL,      NULL,  
  NULL, NULL, NULL, NULL, NULL, /*no key*/ /*no key*/
  // left thumb
  /*no key*/       NULL,            NULL,  
  NULL /*no key*/, NULL /*no key*/, NULL,  
  NULL,            NULL,            NULL,  

  // right hand
  NULL,      NULL,      NULL, NULL, NULL, NULL, NULL,  
  NULL,      NULL,      NULL, NULL, NULL, NULL, NULL,  
  /*no key*/ NULL,      NULL, NULL, NULL, NULL, NULL,  
  NULL,      NULL,      NULL, NULL, NULL, NULL, NULL,  
  /*no key*/ /*no key*/ NULL, NULL, NULL, NULL, NULL,  
  // right thumb
  NULL, NULL,            /*no key*/ 
  NULL, NULL /*no key*/, NULL /*no key*/,  
  NULL, NULL,            NULL  
),
// LAYER 9
KB_MATRIX_LAYER(
  // unused
  NULL /*no key*/,  
  // left hand
  NULL, NULL, NULL, NULL, NULL, NULL,      NULL,  
  NULL, NULL, NULL, NULL, NULL, NULL,      NULL,  
  NULL, NULL, NULL, NULL, NULL, NULL,      /*no key*/ 
  NULL, NULL, NULL, NULL, NULL, NULL,      NULL,  
  NULL, NULL, NULL, NULL, NULL, /*no key*/ /*no key*/
  // left thumb
  /*no key*/       NULL,            NULL,  
  NULL /*no key*/, NULL /*no key*/, NULL,  
  NULL,            NULL,            NULL,  

  // right hand
  NULL,      NULL,      NULL, NULL, NULL, NULL, NULL,  
  NULL,      NULL,      NULL, NULL, NULL, NULL, NULL,  
  /*no key*/ NULL,      NULL, NULL, NULL, NULL, NULL,  
  NULL,      NULL,      NULL, NULL, NULL, NULL, NULL,  
  /*no key*/ /*no key*/ NULL, NULL, NULL, NULL, NULL,  
  // right thumb
  NULL, NULL,            /*no key*/ 
  NULL, NULL /*no key*/, NULL /*no key*/,  
  NULL, NULL,            NULL  
),
};
// ----------------------------------------------------------------------------

// RELEASE --------------------------------------------------------------------
const void_funptr_t PROGMEM _kb_layout_release[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {
// LAYER 0
KB_MATRIX_LAYER(
  // unused
  NULL /*no key*/,  
  // left hand
  kprrel, sinvert, sinvert, sinvert, sinvert, sinvert,   kprrel,  
  kprrel, kprrel,  kprrel,  kprrel,  kprrel,  kprrel,    lpop1,  
  kprrel, kprrel,  kprrel,  kprrel,  kprrel,  kprrel,    /*no key*/ 
  kprrel, kprrel,  kprrel,  kprrel,  kprrel,  kprrel,    kprrel,  
  kprrel, kprrel,  kprrel,  kprrel,  kprrel,  /*no key*/ /*no key*/
  // left thumb
  /*no key*/       kprrel,          kprrel,  
  NULL /*no key*/, NULL /*no key*/, kprrel,  
  kprrel,          kprrel,          kprrel,  

  // right hand
  NULL,      sinvert,   sinvert, sinvert, sinvert, sinvert, kprrel,  
  lpop1,     kprrel,    kprrel,  kprrel,  kprrel,  kprrel,  kprrel,  
  /*no key*/ kprrel,    kprrel,  kprrel,  kprrel,  kprrel,  kprrel,  
  kprrel,    kprrel,    kprrel,  kprrel,  kprrel,  kprrel,  kprrel,  
  /*no key*/ /*no key*/ kprrel,  kprrel,  kprrel,  kprrel,  kprrel,  
  // right thumb
  kprrel, kprrel,          /*no key*/ 
  kprrel, NULL /*no key*/, NULL /*no key*/,  
  kprrel, kprrel,          kprrel  
),
// LAYER 1
KB_MATRIX_LAYER(
  // unused
  NULL /*no key*/,  
  // left hand
  kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,    kprrel,  
  ktrans, ktrans, ktrans, ktrans, ktrans, ktrans,    ktrans,  
  ktrans, ktrans, ktrans, ktrans, ktrans, ktrans,    /*no key*/ 
  ktrans, ktrans, ktrans, ktrans, ktrans, ktrans,    ktrans,  
  NULL,   ktrans, ktrans, mprrel, mprrel, /*no key*/ /*no key*/ 
  // left thumb
  /*no key*/       ktrans,          ktrans,  
  NULL /*no key*/, NULL /*no key*/, ktrans,  
  mprrel,          ktrans,          ktrans,  

  // right hand
  kprrel,    kprrel,    kprrel, kprrel, kprrel, kprrel, kprrel,  
  ktrans,    ktrans,    ktrans, ktrans, ktrans, ktrans, ktrans,  
  /*no key*/ ktrans,    ktrans, ktrans, ktrans, ktrans, ktrans,  
  ktrans,    ktrans,    ktrans, ktrans, ktrans, ktrans, ktrans,  
  /*no key*/ /*no key*/ mprrel, mprrel, mprrel, ktrans, NULL,  
  // right thumb
  ktrans, ktrans,          /*no key*/ 
  ktrans, NULL /*no key*/, NULL /*no key*/,  
  ktrans, ktrans,          mprrel  
),
// LAYER 2
KB_MATRIX_LAYER(
  // unused
  NULL /*no key*/,  
  // left hand
  ktrans, ktrans, ktrans, ktrans, ktrans, ktrans,    ktrans,  
  ktrans, ktrans, ktrans, ktrans, ktrans, ktrans,    ktrans,  
  ktrans, ktrans, ktrans, ktrans, ktrans, ktrans,    /*no key*/ 
  ktrans, ktrans, ktrans, ktrans, ktrans, ktrans,    ktrans,  
  ktrans, ktrans, kprrel, ktrans, ktrans, /*no key*/ /*no key*/
  // left thumb
  /*no key*/       ktrans,          ktrans,  
  NULL /*no key*/, NULL /*no key*/, ktrans,  
  ktrans,          ktrans,          ktrans,  

  // right hand
  NULL,      ktrans,    kprrel, kprrel, kprrel, kprrel, ktrans,  
  ktrans,    ktrans,    kprrel, kprrel, kprrel, kprrel, ktrans,  
  /*no key*/ ktrans,    kprrel, kprrel, kprrel, kprrel, ktrans,  
  ktrans,    ktrans,    kprrel, kprrel, kprrel, kprrel, ktrans,  
  /*no key*/ /*no key*/ ktrans, ktrans, kprrel, kprrel, ktrans,  
  // right thumb
  ktrans, ktrans,          /*no key*/ 
  ktrans, NULL /*no key*/, NULL /*no key*/,  
  ktrans, ktrans,          kprrel  
),
// LAYER 3
KB_MATRIX_LAYER(
  // unused
  NULL /*no key*/,  
  // left hand
  ktrans, ktrans, ktrans, ktrans, ktrans, ktrans,    ktrans,  
  ktrans, kprrel, kprrel, kprrel, kprrel, kprrel,    ktrans,  
  ktrans, kprrel, kprrel, kprrel, kprrel, kprrel,    /*no key*/ 
  ktrans, kprrel, kprrel, kprrel, kprrel, kprrel,    ktrans,  
  ktrans, ktrans, ktrans, ktrans, ktrans, /*no key*/ /*no key*/
  // left thumb
  /*no key*/       ktrans,          ktrans,  
  NULL /*no key*/, NULL /*no key*/, ktrans,  
  ktrans,          ktrans,          ktrans,  

  // right hand
  ktrans,    ktrans,    ktrans, ktrans, ktrans, ktrans, ktrans,  
  ktrans,    kprrel,    kprrel, kprrel, kprrel, kprrel, ktrans,  
  /*no key*/ kprrel,    kprrel, kprrel, kprrel, kprrel, ktrans,  
  ktrans,    kprrel,    kprrel, ktrans, ktrans, ktrans, ktrans,  
  /*no key*/ /*no key*/ ktrans, ktrans, ktrans, ktrans, ktrans,  
  // right thumb
  ktrans, ktrans,          /*no key*/ 
  ktrans, NULL /*no key*/, NULL /*no key*/,  
  ktrans, ktrans,          ktrans  
),
// LAYER 4
KB_MATRIX_LAYER(
  // unused
  NULL /*no key*/,  
  // left hand
  NULL, NULL, NULL, NULL, NULL, NULL,      NULL,  
  NULL, NULL, NULL, NULL, NULL, NULL,      NULL,  
  NULL, NULL, NULL, NULL, NULL, NULL,      /*no key*/ 
  NULL, NULL, NULL, NULL, NULL, NULL,      NULL,  
  NULL, NULL, NULL, NULL, NULL, /*no key*/ /*no key*/ 
  // left thumb
  /*no key*/       NULL,            NULL,  
  NULL /*no key*/, NULL /*no key*/, NULL,  
  NULL,            NULL,            NULL,  

  // right hand
  NULL,      NULL,      NULL, NULL, NULL, NULL, NULL,  
  NULL,      NULL,      NULL, NULL, NULL, NULL, NULL,  
  /*no key*/ NULL,      NULL, NULL, NULL, NULL, NULL,  
  NULL,      NULL,      NULL, NULL, NULL, NULL, NULL,  
  /*no key*/ /*no key*/ NULL, NULL, NULL, NULL, NULL,  
  // right thumb
  NULL, NULL,            /*no key*/ 
  NULL, NULL /*no key*/, NULL /*no key*/,  
  NULL, NULL,            NULL  
),
// LAYER 5
KB_MATRIX_LAYER(
  // unused
  NULL /*no key*/,  
  // left hand
  NULL, NULL, NULL, NULL, NULL, NULL,      NULL,  
  NULL, NULL, NULL, NULL, NULL, NULL,      NULL,  
  NULL, NULL, NULL, NULL, NULL, NULL,      /*no key*/ 
  NULL, NULL, NULL, NULL, NULL, NULL,      NULL,  
  NULL, NULL, NULL, NULL, NULL, /*no key*/ /*no key*/ 
  // left thumb
  /*no key*/       NULL,            NULL,  
  NULL /*no key*/, NULL /*no key*/, NULL,  
  NULL,            NULL,            NULL,  

  // right hand
  NULL,      NULL,      NULL, NULL, NULL, NULL, NULL,  
  NULL,      NULL,      NULL, NULL, NULL, NULL, NULL,  
  /*no key*/ NULL,      NULL, NULL, NULL, NULL, NULL,  
  NULL,      NULL,      NULL, NULL, NULL, NULL, NULL,  
  /*no key*/ /*no key*/ NULL, NULL, NULL, NULL, NULL,  
  // right thumb
  NULL, NULL,            /*no key*/ 
  NULL, NULL /*no key*/, NULL /*no key*/,  
  NULL, NULL,            NULL  
),
// LAYER 6
KB_MATRIX_LAYER(
  // unused
  NULL /*no key*/,  
  // left hand
  NULL, NULL, NULL, NULL, NULL, NULL,      NULL,  
  NULL, NULL, NULL, NULL, NULL, NULL,      NULL,  
  NULL, NULL, NULL, NULL, NULL, NULL,      /*no key*/ 
  NULL, NULL, NULL, NULL, NULL, NULL,      NULL,  
  NULL, NULL, NULL, NULL, NULL, /*no key*/ /*no key*/ 
  // left thumb
  /*no key*/       NULL,            NULL,  
  NULL /*no key*/, NULL /*no key*/, NULL,  
  NULL,            NULL,            NULL,  

  // right hand
  NULL,      NULL,      NULL, NULL, NULL, NULL, NULL,  
  NULL,      NULL,      NULL, NULL, NULL, NULL, NULL,  
  /*no key*/ NULL,      NULL, NULL, NULL, NULL, NULL,  
  NULL,      NULL,      NULL, NULL, NULL, NULL, NULL,  
  /*no key*/ /*no key*/ NULL, NULL, NULL, NULL, NULL,  
  // right thumb
  NULL, NULL,            /*no key*/ 
  NULL, NULL /*no key*/, NULL /*no key*/,  
  NULL, NULL,            NULL  
),
// LAYER 7
KB_MATRIX_LAYER(
  // unused
  NULL /*no key*/,  
  // left hand
  NULL, NULL, NULL, NULL, NULL, NULL,      NULL,  
  NULL, NULL, NULL, NULL, NULL, NULL,      NULL,  
  NULL, NULL, NULL, NULL, NULL, NULL,      /*no key*/ 
  NULL, NULL, NULL, NULL, NULL, NULL,      NULL,  
  NULL, NULL, NULL, NULL, NULL, /*no key*/ /*no key*/ 
  // left thumb
  /*no key*/       NULL,            NULL,  
  NULL /*no key*/, NULL /*no key*/, NULL,  
  NULL,            NULL,            NULL,  

  // right hand
  NULL,      NULL,      NULL, NULL, NULL, NULL, NULL,  
  NULL,      NULL,      NULL, NULL, NULL, NULL, NULL,  
  /*no key*/ NULL,      NULL, NULL, NULL, NULL, NULL,  
  NULL,      NULL,      NULL, NULL, NULL, NULL, NULL,  
  /*no key*/ /*no key*/ NULL, NULL, NULL, NULL, NULL,  
  // right thumb
  NULL, NULL,            /*no key*/ 
  NULL, NULL /*no key*/, NULL /*no key*/,  
  NULL, NULL,            NULL  
),
// LAYER 8
KB_MATRIX_LAYER(
  // unused
  NULL /*no key*/,  
  // left hand
  NULL, NULL, NULL, NULL, NULL, NULL,      NULL,  
  NULL, NULL, NULL, NULL, NULL, NULL,      NULL,  
  NULL, NULL, NULL, NULL, NULL, NULL,      /*no key*/ 
  NULL, NULL, NULL, NULL, NULL, NULL,      NULL,  
  NULL, NULL, NULL, NULL, NULL, /*no key*/ /*no key*/ 
  // left thumb
  /*no key*/       NULL,            NULL,  
  NULL /*no key*/, NULL /*no key*/, NULL,  
  NULL,            NULL,            NULL,  

  // right hand
  NULL,      NULL,      NULL, NULL, NULL, NULL, NULL,  
  NULL,      NULL,      NULL, NULL, NULL, NULL, NULL,  
  /*no key*/ NULL,      NULL, NULL, NULL, NULL, NULL,  
  NULL,      NULL,      NULL, NULL, NULL, NULL, NULL,  
  /*no key*/ /*no key*/ NULL, NULL, NULL, NULL, NULL,  
  // right thumb
  NULL, NULL,            /*no key*/ 
  NULL, NULL /*no key*/, NULL /*no key*/,  
  NULL, NULL,            NULL  
),
// LAYER 9
KB_MATRIX_LAYER(
  // unused
  NULL /*no key*/,  
  // left hand
  NULL, NULL, NULL, NULL, NULL, NULL,      NULL,  
  NULL, NULL, NULL, NULL, NULL, NULL,      NULL,  
  NULL, NULL, NULL, NULL, NULL, NULL,      /*no key*/ 
  NULL, NULL, NULL, NULL, NULL, NULL,      NULL,  
  NULL, NULL, NULL, NULL, NULL, /*no key*/ /*no key*/ 
  // left thumb
  /*no key*/       NULL,            NULL,  
  NULL /*no key*/, NULL /*no key*/, NULL,  
  NULL,            NULL,            NULL,  

  // right hand
  NULL,      NULL,      NULL, NULL, NULL, NULL, NULL,  
  NULL,      NULL,      NULL, NULL, NULL, NULL, NULL,  
  /*no key*/ NULL,      NULL, NULL, NULL, NULL, NULL,  
  NULL,      NULL,      NULL, NULL, NULL, NULL, NULL,  
  /*no key*/ /*no key*/ NULL, NULL, NULL, NULL, NULL,  
  // right thumb
  NULL, NULL,            /*no key*/ 
  NULL, NULL /*no key*/, NULL /*no key*/,  
  NULL, NULL,            NULL  
),
};
// ----------------------------------------------------------------------------
