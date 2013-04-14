/* ----------------------------------------------------------------------------
* ergoDOX layout : COLEMAK JC Sticky Keys Mod
*     created by Ryan Prince
* Description: This layout is designed for programming with a focus on
*     minimizing/elimnating the need to take the hands out of home-row position
*     to reach other keys. Layer sticky keys are used to reduce the average
*     number of keystrokes required to access keys in other layers. Some
*     redundancy of navigation and spacing keys is added to the left hand to
*     allow for greater one-handed access when using a mouse with the right
*     hand.
*   The alpha key layout is COLEMAK with sticky layer keys on the thumb
*     switches for a symbol layer and a ten-key/function
*     layer.
*   Modifiers are symetric on each hand with the exception of the Alt
*     key because my primary machine is a Mac which utilizes command and ctrl
*     for chorded shortcuts more frequenty than ctrl and alt. The layer sticky
*     keys compliment standard modifier sticky keys (for shift, ctrl, command,
*     alt) to allow fast touch typing with minimal chording in favor of
*     sequential keying (preferably on alternate hands) for multi-key shortcuts
*     as chording introduces strain and fatigue and takes your hands out of
*     home row position increasing the likelihood of mistyping.
*   Sticky keys for standard modifiers are used as an operating system setting
*     for the benefit of key state visualization, though this can interfere
*     with the kbfun_shift_press_release() behavior which implicitly adds the
*     shift down modifier to output symbols that require it without knowledge
*     of the virtual sticky state maintained by the operating system.
*   The ErgoDox Layout Configurator layout that best approximates the layout
*     defined in this file is available here:
*     https://www.massdrop.com/ext/ergodox/?referer=EAZJPJ&hash=f26761358ba99e21ae937173da512849
*     The differences are mainly the use of layer toggles instead of sticky
*     layer keys and many of the symbols add the kbfun_shift_press_release()
*     which is not accessible for all keys in the cofigurator (as of
*     2013-04-10).
* -----------------------------------------------------------------------------
* Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>,
*    2013 Ryan Prince <judascleric@gmail.com>
* Released under The MIT License (MIT) (see "license.md")
* Project located at <https://github.com/benblazak/ergodox-firmware>
* -------------------------------------------------------------------------- */
#include <stdint.h>
#include <stddef.h>
#include <avr/pgmspace.h>
#include "../../../lib/data-types/misc.h"
#include "../../../lib/usb/usage-page/keyboard--short-names.h"
#include "../../../lib/key-functions/public.h"
#include "../matrix.h"
#include "../layout.h"
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

// DEFINITIONS ----------------------------------------------------------------
#define  kprrel   &kbfun_press_release
#define  kprpst   &kbfun_press_release_preserve_sticky
#define  mprrel   &kbfun_mediakey_press_release
#define  ktrans   &kbfun_transparent
#define  lpush1   &kbfun_layer_push_1
#define  lpush2   &kbfun_layer_push_2
#define  lsticky1   &kbfun_layer_sticky_1
#define  lsticky2   &kbfun_layer_sticky_2
#define  lpop     &kbfun_layer_pop_all
#define  lpop1    &kbfun_layer_pop_1
#define  lpop2    &kbfun_layer_pop_2
#define  dbtldr   &kbfun_jump_to_bootloader
#define  sshprre  &kbfun_shift_press_release
// ----------------------------------------------------------------------------

// LAYOUT ---------------------------------------------------------------------
const uint8_t PROGMEM _kb_layout[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {
// LAYER 0
KB_MATRIX_LAYER(
	// unused
	0,	
	// left hand
	KEY_GraveAccent_Tilde,	KEY_1_Exclamation,	KEY_2_At,	KEY_3_Pound,	KEY_4_Dollar,	KEY_5_Percent,	KEY_LeftBracket_LeftBrace,	
	KEY_LeftControl,	KEY_q_Q,	KEY_w_W,	KEY_f_F,	KEY_p_P,	KEY_g_G,	KEY_Equal_Plus,	
	KEY_LeftShift,	KEY_a_A,	KEY_r_R,	KEY_s_S,	KEY_t_T,	KEY_d_D,	
	KEY_LeftGUI,	KEY_z_Z,	KEY_x_X,	KEY_c_C,	KEY_v_V,	KEY_b_B,	0,	
	KEY_Home,	KEY_End,	KEY_PageUp,	KEY_PageDown,	1,
	KEY_Tab,	KEY_Spacebar,	
	0,	0,	KEY_ReturnEnter,	
	KEY_Escape,	2,	KEY_LeftAlt,	
	// right hand
	KEY_RightBracket_RightBrace,	KEY_6_Caret,	KEY_7_Ampersand,	KEY_8_Asterisk,	KEY_9_LeftParenthesis,	KEY_0_RightParenthesis,	KEY_Backslash_Pipe,	
	KEY_Dash_Underscore,	KEY_j_J,	KEY_l_L,	KEY_u_U,	KEY_y_Y,	KEY_Semicolon_Colon,	KEY_RightControl,	
	KEY_h_H,	KEY_n_N,	KEY_e_E,	KEY_i_I,	KEY_o_O,	KEY_RightShift,	
	2,	KEY_k_K,	KEY_m_M,	KEY_Comma_LessThan,	KEY_Period_GreaterThan,	KEY_Slash_Question,	KEY_RightGUI,	
	1,	KEY_DownArrow,	KEY_UpArrow,	KEY_LeftArrow,	KEY_RightArrow,
	KEY_Insert,	KEY_DeleteForward,	
	0,	0,	0,	
	KEY_DeleteBackspace,	KEY_ReturnEnter,	KEY_Spacebar	
),
// LAYER 1
KB_MATRIX_LAYER(
	// unused
	0,	
	// left hand
	0,	0,	0,	0,	0,	0,	0,	
	0,	KEY_1_Exclamation,	KEY_2_At,	KEY_3_Pound,	KEY_4_Dollar,	KEY_5_Percent,	0,	
	0,	KEY_SingleQuote_DoubleQuote,	0x34,	0x2F,	0x30,	KEY_Equal_Plus,	
	0,	0x31,	KEY_Backslash_Pipe,	KEY_Dash_Underscore,	KEY_DeleteBackspace,	KEY_Tab,	0,	
	KEY_LeftArrow,	KEY_RightArrow,	KEY_UpArrow,	KEY_DownArrow,	0,	
	0,	0,	
	0,	0,	0,	
	0,	0,	0,	
	// right hand
	0,	0,	MEDIAKEY_PREV_TRACK,	MEDIAKEY_PLAY_PAUSE,	MEDIAKEY_NEXT_TRACK,	0,	0,	
	0,	KEY_6_Caret,	KEY_7_Ampersand,	KEYPAD_Asterisk,	KEYPAD_Minus,	KEY_GraveAccent_Tilde,	0,	
	KEYPAD_Plus,	KEY_9_LeftParenthesis,	KEY_0_RightParenthesis,	KEY_LeftBracket_LeftBrace,	KEY_RightBracket_RightBrace,	0,	
	0,	KEY_GraveAccent_Tilde,	KEY_DownArrow,	KEY_UpArrow,	KEY_LeftArrow,	KEY_RightArrow,	0,	
	0,	0,	0,	0,	0,	
	0,	0,	
	0,	0,	0,	
	0,	0,	0	
),
// LAYER 2
KB_MATRIX_LAYER(
	// unused
	0,	
	// left hand
	0,	0,	0,	0,	0,	0,	0,	
	0,	KEY_F9,	KEY_F10,	KEY_F11,	KEY_F12,	KEY_VolumeUp,	0,	
	0,	KEY_F5,	KEY_F6,	KEY_F7,	KEY_F8,	KEY_VolumeDown,	
	0,	KEY_F1,	KEY_F2,	KEY_F3,	KEY_F4,	KEY_Mute,	0,	
	0,	0,	0,	0,	0,	
	0,	0,	
	0,	0,	0,	
	0,	0,	0,	
	// right hand
	0,	0,	KEYPAD_NumLock_Clear,	KEYPAD_Asterisk,	KEYPAD_Slash,	KEY_5_Percent,	0,	
	0,	KEYPAD_Minus,	KEYPAD_7_Home,	KEYPAD_8_UpArrow,	KEYPAD_9_PageUp,	KEYPAD_Plus,	0,	
	KEYPAD_Equal,	KEYPAD_4_LeftArrow,	KEYPAD_5,	KEYPAD_6_RightArrow,	KEYPAD_0_Insert,	0,	
	0,	KEY_Comma_LessThan,	KEYPAD_1_End,	KEYPAD_2_DownArrow,	KEYPAD_3_PageDown,	KEYPAD_Period_Delete,	0,	
	0,	0,	0,	0,	0,	
	0,	0,	
	0,	0,	0,	
	0,	0,	0	
),
};
// ----------------------------------------------------------------------------

// PRESS ----------------------------------------------------------------------
const void_funptr_t PROGMEM _kb_layout_press[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {
// LAYER 0
KB_MATRIX_LAYER(
	// unused
	NULL,	
	// left hand
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	lpop,	
	kprrel,	kprrel,	kprrel,	kprrel,	lsticky1,	
	kprrel,	kprrel,	
	NULL,	NULL,	kprrel,	
	kprrel,	lsticky2,	kprrel,	
	// right hand
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	
	lsticky2,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	
	lsticky1,	kprrel,	kprrel,	kprrel,	kprrel,	
	kprrel,	kprrel,	
	lpop,	NULL,	NULL,	
	kprrel,	kprrel,	kprrel	
),
// LAYER 1
KB_MATRIX_LAYER(
	// unused
	NULL,	
	// left hand
	ktrans,	ktrans,	ktrans,	ktrans,	ktrans,	ktrans,	ktrans,	
	ktrans,	sshprre,	sshprre,	sshprre,	sshprre,	sshprre,	ktrans,	
	ktrans,	kprrel,	sshprre,	sshprre,	sshprre,	kprrel,	
	ktrans,	sshprre,	kprrel,	sshprre,	kprrel,	kprrel,	ktrans,	
	kprrel,	kprrel,	kprrel,	kprrel,	ktrans,	
	ktrans,	ktrans,	
	NULL,	NULL,	ktrans,	
	ktrans,	ktrans,	ktrans,	
	// right hand
	ktrans,	ktrans,	mprrel,	mprrel,	mprrel,	ktrans,	ktrans,	
	ktrans,	sshprre,	sshprre,	kprrel,	kprrel,	kprrel,	ktrans,	
	kprrel,	sshprre,	sshprre,	kprrel,	kprrel,	ktrans,	
	ktrans,	sshprre,	kprrel,	kprrel,	kprrel,	kprrel,	ktrans,	
	ktrans,	ktrans,	ktrans,	ktrans,	ktrans,	
	ktrans,	ktrans,	
	ktrans,	NULL,	NULL,	
	ktrans,	ktrans,	ktrans	
),
// LAYER 2
KB_MATRIX_LAYER(
	// unused
	NULL,	
	// left hand
	ktrans,	ktrans,	ktrans,	ktrans,	ktrans,	ktrans,	ktrans,	
	ktrans,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	ktrans,	
	ktrans,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	
	ktrans,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	ktrans,	
	ktrans,	ktrans,	ktrans,	ktrans,	ktrans,	
	ktrans,	ktrans,	
	NULL,	NULL,	ktrans,	
	ktrans,	ktrans,	ktrans,	
	// right hand
	dbtldr,	kprrel,	kprrel,	kprrel,	kprrel,	sshprre,	ktrans,	
	ktrans,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	ktrans,	
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	ktrans,	
	ktrans,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	ktrans,	
	ktrans,	ktrans,	ktrans,	ktrans,	ktrans,	
	ktrans,	ktrans,	
	ktrans,	NULL,	NULL,	
	ktrans,	ktrans,	ktrans	
),
};
// ----------------------------------------------------------------------------

// RELEASE --------------------------------------------------------------------
const void_funptr_t PROGMEM _kb_layout_release[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {
// LAYER 0
KB_MATRIX_LAYER(
	// unused
	NULL,	
	// left hand
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	NULL,	
	kprrel,	kprrel,	kprrel,	kprrel,	lsticky1,	
	kprrel,	kprrel,	
	NULL,	NULL,	kprrel,	
	kprrel,	lsticky2,	kprrel,	
	// right hand
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	
	lsticky2,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	
	lsticky1,	kprrel,	kprrel,	kprrel,	kprrel,	
	kprrel,	kprrel,	
	NULL,	NULL,	NULL,	
	kprrel,	kprrel,	kprrel	
),
// LAYER 1
KB_MATRIX_LAYER(
	// unused
	NULL,	
	// left hand
	ktrans,	ktrans,	ktrans,	ktrans,	ktrans,	ktrans,	ktrans,	
	ktrans,	sshprre,	sshprre,	sshprre,	sshprre,	sshprre,	ktrans,	
	ktrans,	kprrel,	sshprre,	sshprre,	sshprre,	kprrel,	
	kprrel,	sshprre,	kprrel,	sshprre,	kprrel,	kprrel,	ktrans,	
	kprrel,	kprrel,	kprrel,	kprrel,	ktrans,	
	ktrans,	ktrans,	
	NULL,	NULL,	ktrans,	
	ktrans,	ktrans,	ktrans,	
	// right hand
	ktrans,	ktrans,	mprrel,	mprrel,	mprrel,	ktrans,	ktrans,	
	ktrans,	sshprre,	sshprre,	kprrel,	kprrel,	kprrel,	ktrans,	
	kprrel,	sshprre,	sshprre,	kprrel,	kprrel,	ktrans,	
	ktrans,	sshprre,	kprrel,	kprrel,	kprrel,	kprrel,	ktrans,	
	ktrans,	ktrans,	ktrans,	ktrans,	ktrans,	
	ktrans,	ktrans,	
	ktrans,	NULL,	NULL,	
	ktrans,	ktrans,	ktrans	
),
// LAYER 2
KB_MATRIX_LAYER(
	// unused
	NULL,	
	// left hand
	ktrans,	ktrans,	ktrans,	ktrans,	ktrans,	ktrans,	ktrans,	
	ktrans,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	ktrans,	
	ktrans,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	ktrans,	
	ktrans,	ktrans,	ktrans,	ktrans,	ktrans,	
	ktrans,	ktrans,	
	NULL,	NULL,	ktrans,	
	kprrel,	ktrans,	ktrans,	
	// right hand
	NULL,	kprrel,	kprrel,	kprrel,	kprrel,	sshprre,	ktrans,	
	ktrans,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	ktrans,	
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	ktrans,	
	ktrans,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	
	ktrans,	ktrans,	ktrans,	ktrans,	ktrans,	
	ktrans,	ktrans,	
	ktrans,	NULL,	NULL,	
	ktrans,	ktrans,	ktrans	
),
};
// ----------------------------------------------------------------------------
