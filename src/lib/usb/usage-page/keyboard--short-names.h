/* ----------------------------------------------------------------------------
 * USB Keyboard Key Codes : short names
 *
 * These are for convenience (and to help with formatting, keeping stuff from
 * getting too long).  See "keyboard-usage-page.h" for definitions and
 * everything.
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef USB_USAGE_PAGE_KEYBOARD_SHORT_NAMES_h
	#define USB_USAGE_PAGE_KEYBOARD_SHORT_NAMES_h
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


#include "./keyboard.h"


// ----------------------------------------------------------------------------
// protocol
// ----------------------------------------------------------------------------

// error
#define _ErrRollover        KEY_ErrorRollOver
#define _PostFail           KEY_POSTFail
#define _ErrUndef           KEY_ErrorUndefined


// ----------------------------------------------------------------------------
// main keyboard
// ----------------------------------------------------------------------------

// letters
#define _A                  KEY_a_A
#define _B                  KEY_b_B
#define _C                  KEY_c_C
#define _D                  KEY_d_D
#define _E                  KEY_e_E
#define _F                  KEY_f_F
#define _G                  KEY_g_G
#define _H                  KEY_h_H
#define _I                  KEY_i_I
#define _J                  KEY_j_J
#define _K                  KEY_k_K
#define _L                  KEY_l_L
#define _M                  KEY_m_M
#define _N                  KEY_n_N
#define _O                  KEY_o_O
#define _P                  KEY_p_P
#define _Q                  KEY_q_Q
#define _R                  KEY_r_R
#define _S                  KEY_s_S
#define _T                  KEY_t_T
#define _U                  KEY_u_U
#define _V                  KEY_v_V
#define _W                  KEY_w_W
#define _X                  KEY_x_X
#define _Y                  KEY_y_Y
#define _Z                  KEY_z_Z

// numbers
#define _0                  KEY_0_RightParenthesis
#define _1                  KEY_1_Exclamation
#define _2                  KEY_2_At
#define _3                  KEY_3_Pound
#define _4                  KEY_4_Dollar
#define _5                  KEY_5_Percent
#define _6                  KEY_6_Caret
#define _7                  KEY_7_Ampersand
#define _8                  KEY_8_Asterisk
#define _9                  KEY_9_LeftParenthesis

// function
#define _F1                 KEY_F1
#define _F2                 KEY_F2
#define _F3                 KEY_F3
#define _F4                 KEY_F4
#define _F5                 KEY_F5
#define _F6                 KEY_F6
#define _F7                 KEY_F7
#define _F8                 KEY_F8
#define _F9                 KEY_F9
#define _F10                KEY_F10
#define _F11                KEY_F11
#define _F12                KEY_F12
#define _F13                KEY_F13
#define _F14                KEY_F14
#define _F15                KEY_F15
#define _F16                KEY_F16
#define _F17                KEY_F17
#define _F18                KEY_F18
#define _F19                KEY_F19
#define _F20                KEY_F20
#define _F21                KEY_F21
#define _F22                KEY_F22
#define _F23                KEY_F23
#define _F24                KEY_F24

// whitespace and symbols
#define _enter              KEY_ReturnEnter
#define _space              KEY_Spacebar
#define _tab                KEY_Tab
// ---
#define _backslash          KEY_Backslash_Pipe
#define _bracketL           KEY_LeftBracket_LeftBrace
#define _bracketR           KEY_RightBracket_RightBrace
#define _comma              KEY_Comma_LessThan
#define _dash               KEY_Dash_Underscore
#define _equal              KEY_Equal_Plus
#define _grave              KEY_GraveAccent_Tilde
#define _period             KEY_Period_GreaterThan
#define _quote              KEY_SingleQuote_DoubleQuote
#define _semicolon          KEY_Semicolon_Colon
#define _slash              KEY_Slash_Question
// ---
#define _sep_dec            KEY_DecimalSeparator
#define _sep_thousands      KEY_ThousandsSeparator
#define _currencyUnit       KEY_CurrencyUnit
#define _currencySubunit    KEY_CurrencySubunit

// international and language
#define _int1               KEY_International1
#define _int2               KEY_International2
#define _int3               KEY_International3
#define _int4               KEY_International4
#define _int5               KEY_International5
#define _int6               KEY_International6
#define _int7               KEY_International7
#define _int8               KEY_International8
#define _int9               KEY_International9
// ---
#define _lang1              KEY_LANG1
#define _lang2              KEY_LANG2
#define _lang3              KEY_LANG3
#define _lang4              KEY_LANG4
#define _lang5              KEY_LANG5
#define _lang6              KEY_LANG6
#define _lang7              KEY_LANG7
#define _lang8              KEY_LANG8
#define _lang9              KEY_LANG9
// ---
#define _backslash_nonUS    KEY_NonUS_Backslash_Pipe
#define _pound_nonUS        KEY_NonUS_Pound_Tilde

// text control
#define _bs                 KEY_DeleteBackspace
#define _del                KEY_DeleteForward
#define _home               KEY_Home
#define _end                KEY_End
#define _pageU              KEY_PageUp
#define _pageD              KEY_PageDown
#define _arrowU             KEY_UpArrow
#define _arrowD             KEY_DownArrow
#define _arrowL             KEY_LeftArrow
#define _arrowR             KEY_RightArrow
#define _esc                KEY_Escape
#define _insert             KEY_Insert

// modifier
#define _altL               KEY_LeftAlt
#define _altR               KEY_RightAlt
#define _ctrlL              KEY_LeftControl
#define _ctrlR              KEY_RightControl
#define _guiL               KEY_LeftGUI
#define _guiR               KEY_RightGUI
#define _shiftL             KEY_LeftShift
#define _shiftR             KEY_RightShift

// lock
#define _capsLock           KEY_CapsLock
#define _scrollLock         KEY_ScrollLock
// (numlock is under keypad)
// --- not generally used
#define _capsLock_locking   KEY_LockingCapsLock
#define _numLock_locking    KEY_LockingNumLock
#define _scrollLock_locking KEY_LockingScrollLock

// special function
#define _pause              KEY_Pause
#define _print              KEY_PrintScreen
// ---
#define _application        KEY_Application
#define _execute            KEY_Execute
#define _power              KEY_Power
// ---
#define _help               KEY_Help
#define _menu               KEY_Menu
// ---
#define _cut                KEY_Cut
#define _copy               KEY_Copy
#define _paste              KEY_Paste
#define _find               KEY_Find
#define _select             KEY_Select
#define _stop               KEY_Stop
#define _undo               KEY_Undo
// ---
#define _mute               KEY_Mute
#define _volumeU            KEY_VolumeUp
#define _volumeD            KEY_VolumeDown
// ---
#define _altErase           KEY_AlternateErase
// ---
#define _again              KEY_Again
#define _cancel             KEY_Cancel
#define _clear_again        KEY_Clear_Again
#define _clear              KEY_Clear
#define _oper               KEY_Oper
#define _out                KEY_Out
#define _prior              KEY_Prior
#define _return             KEY_Return
#define _separator          KEY_Separator
// ---
#define _crSel              KEY_CrSel_Props
#define _exSel              KEY_ExSel
#define _sysReq             KEY_SysReq_Attention


// ----------------------------------------------------------------------------
// keypad
// ----------------------------------------------------------------------------

// numbers and hex letters
#define _1_kp               KEYPAD_1_End
#define _2_kp               KEYPAD_2_DownArrow
#define _3_kp               KEYPAD_3_PageDown
#define _4_kp               KEYPAD_4_LeftArrow
#define _5_kp               KEYPAD_5
#define _6_kp               KEYPAD_6_RightArrow
#define _7_kp               KEYPAD_7_Home
#define _8_kp               KEYPAD_8_UpArrow
#define _9_kp               KEYPAD_9_PageUp
#define _0_kp               KEYPAD_0_Insert
#define _A_kp               KEYPAD_A
#define _B_kp               KEYPAD_B
#define _C_kp               KEYPAD_C
#define _D_kp               KEYPAD_D
#define _E_kp               KEYPAD_E
#define _F_kp               KEYPAD_F
// ---
#define _00_kp              KEYPAD_00
#define _000_kp             KEYPAD_000

// whitespace and symbols
#define _tab_kp             KEYPAD_Tab
#define _space_kp           KEYPAD_Space
#define _enter_kp           KEYPAD_ENTER
// ---
#define _dec_del_kp         KEYPAD_Period_Delete
#define _comma_kp           KEYPAD_Comma
#define _equal_kp           KEYPAD_Equal
#define _equalSign_kp       KEYPAD_EqualSign
#define _parenL_kp          KEYPAD_LeftParenthesis
#define _parenR_kp          KEYPAD_RightParenthesis
#define _braceL_kp          KEYPAD_LeftBrace
#define _braceR_kp          KEYPAD_RightBrace

// operations
// --- basic
#define _add_kp             KEYPAD_Plus
#define _sub_kp             KEYPAD_Minus
#define _mul_kp             KEYPAD_Asterisk
#define _div_kp             KEYPAD_Slash
#define _plusMinus_kp       KEYPAD_PlusMinus
// --- logical
#define _lt_kp              KEYPAD_LessThan
#define _gt_kp              KEYPAD_GreaterThan
#define _xor_kp             KEYPAD_XOR
#define _and_kp             KEYPAD_Ampersand
#define _andand_kp          KEYPAD_AmpersandAmpersand
#define _pipe_kp            KEYPAD_Pipe
#define _pipepipe_kp        KEYPAD_PipePipe
#define _caret_kp           KEYPAD_Caret
#define _exclamation_kp     KEYPAD_Exclamation
// --- other
#define _at_kp              KEYPAD_At
#define _colon_kp           KEYPAD_Colon
#define _percent_kp         KEYPAD_Percent
#define _pound_kp           KEYPAD_Pound

// radix
#define _bin_kp             KEYPAD_Binary
#define _oct_kp             KEYPAD_Octal
#define _dec_kp             KEYPAD_Decimal
#define _hex_kp             KEYPAD_Hexadecimal

// text control
#define _bs_kp              KEYPAD_Backspace
#define _clear_kp           KEYPAD_Clear
#define _clearEntry_kp      KEYPAD_ClearEntry

// lock
#define _numLock_kp         KEYPAD_NumLock_Clear

// memory control
#define _memStore_kp        KEYPAD_MemoryStore
#define _memRecall_kp       KEYPAD_MemoryRecall
#define _memClear_kp        KEYPAD_MemoryClear
#define _memAdd_kp          KEYPAD_MemoryAdd
#define _memSub_kp          KEYPAD_MemorySubtract
#define _memMul_kp          KEYPAD_MemoryMultiply
#define _memDiv_kp          KEYPAD_MemoryDivide


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif

