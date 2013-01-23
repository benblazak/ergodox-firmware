/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**
 * - description: |
 *     Partial key descriptions for the "Boot Keyboard Required" keys (see
 *     <../../../firmware/lib/usb/usage-page/keyboard.h>).
 *
 *     Prefixes: `KEYS__`, [none]
 *
 *     Usage: `#define` `KEYS__DEFAULT` before `#include`ing.
 *
 *     Note: This header is meant to be included, not as an interface to
 *     anything, but in order to centralize a bit of code that would otherwise
 *     be duplicated by most layouts.
 */


#ifndef ERGODOX_FIRMWARE__FIRMWARE__LIB__LAYOUT__KEYS__H
#define ERGODOX_FIRMWARE__FIRMWARE__LIB__LAYOUT__KEYS__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


#include "../../../firmware/lib/usb/usage-page/keyboard.h"

// ----------------------------------------------------------------------------

#ifndef KEYS__DEFAULT
    #error "You must define `KEYS__DEFAULT`"
#endif
#ifndef KEYS__SHIFTED
    #error "You must define `KEYS__SHIFTED`"
#endif

// ----------------------------------------------------------------------------

// letters
KEYS__DEFAULT(    A,              KEY__a_A                        );
KEYS__DEFAULT(    B,              KEY__b_B                        );
KEYS__DEFAULT(    C,              KEY__c_C                        );
KEYS__DEFAULT(    D,              KEY__d_D                        );
KEYS__DEFAULT(    E,              KEY__e_E                        );
KEYS__DEFAULT(    F,              KEY__f_F                        );
KEYS__DEFAULT(    G,              KEY__g_G                        );
KEYS__DEFAULT(    H,              KEY__h_H                        );
KEYS__DEFAULT(    I,              KEY__i_I                        );
KEYS__DEFAULT(    J,              KEY__j_J                        );
KEYS__DEFAULT(    K,              KEY__k_K                        );
KEYS__DEFAULT(    L,              KEY__l_L                        );
KEYS__DEFAULT(    M,              KEY__m_M                        );
KEYS__DEFAULT(    N,              KEY__n_N                        );
KEYS__DEFAULT(    O,              KEY__o_O                        );
KEYS__DEFAULT(    P,              KEY__p_P                        );
KEYS__DEFAULT(    Q,              KEY__q_Q                        );
KEYS__DEFAULT(    R,              KEY__r_R                        );
KEYS__DEFAULT(    S,              KEY__s_S                        );
KEYS__DEFAULT(    T,              KEY__t_T                        );
KEYS__DEFAULT(    U,              KEY__u_U                        );
KEYS__DEFAULT(    V,              KEY__v_V                        );
KEYS__DEFAULT(    W,              KEY__w_W                        );
KEYS__DEFAULT(    X,              KEY__x_X                        );
KEYS__DEFAULT(    Y,              KEY__y_Y                        );
KEYS__DEFAULT(    Z,              KEY__z_Z                        );
// --- (shifted) ---
KEYS__SHIFTED(    CA,             KEY__a_A                        );
KEYS__SHIFTED(    CB,             KEY__b_B                        );
KEYS__SHIFTED(    CC,             KEY__c_C                        );
KEYS__SHIFTED(    CD,             KEY__d_D                        );
KEYS__SHIFTED(    CE,             KEY__e_E                        );
KEYS__SHIFTED(    CF,             KEY__f_F                        );
KEYS__SHIFTED(    CG,             KEY__g_G                        );
KEYS__SHIFTED(    CH,             KEY__h_H                        );
KEYS__SHIFTED(    CI,             KEY__i_I                        );
KEYS__SHIFTED(    CJ,             KEY__j_J                        );
KEYS__SHIFTED(    CK,             KEY__k_K                        );
KEYS__SHIFTED(    CL,             KEY__l_L                        );
KEYS__SHIFTED(    CM,             KEY__m_M                        );
KEYS__SHIFTED(    CN,             KEY__n_N                        );
KEYS__SHIFTED(    CO,             KEY__o_O                        );
KEYS__SHIFTED(    CP,             KEY__p_P                        );
KEYS__SHIFTED(    CQ,             KEY__q_Q                        );
KEYS__SHIFTED(    CR,             KEY__r_R                        );
KEYS__SHIFTED(    CS,             KEY__s_S                        );
KEYS__SHIFTED(    CT,             KEY__t_T                        );
KEYS__SHIFTED(    CU,             KEY__u_U                        );
KEYS__SHIFTED(    CV,             KEY__v_V                        );
KEYS__SHIFTED(    CW,             KEY__w_W                        );
KEYS__SHIFTED(    CX,             KEY__x_X                        );
KEYS__SHIFTED(    CY,             KEY__y_Y                        );
KEYS__SHIFTED(    CZ,             KEY__z_Z                        );

// numbers
KEYS__DEFAULT(    K0,             KEY__0_RightParenthesis         );
KEYS__DEFAULT(    K1,             KEY__1_Exclamation              );
KEYS__DEFAULT(    K2,             KEY__2_At                       );
KEYS__DEFAULT(    K3,             KEY__3_Pound                    );
KEYS__DEFAULT(    K4,             KEY__4_Dollar                   );
KEYS__DEFAULT(    K5,             KEY__5_Percent                  );
KEYS__DEFAULT(    K6,             KEY__6_Caret                    );
KEYS__DEFAULT(    K7,             KEY__7_Ampersand                );
KEYS__DEFAULT(    K8,             KEY__8_Asterisk                 );
KEYS__DEFAULT(    K9,             KEY__9_LeftParenthesis          );
// --- (shifted) ---
KEYS__SHIFTED(    ParenR,         KEY__0_RightParenthesis         );
KEYS__SHIFTED(    Exclam,         KEY__1_Exclamation              );
KEYS__SHIFTED(    At,             KEY__2_At                       );
KEYS__SHIFTED(    Pound,          KEY__3_Pound                    );
KEYS__SHIFTED(    Dollar,         KEY__4_Dollar                   );
KEYS__SHIFTED(    Percent,        KEY__5_Percent                  );
KEYS__SHIFTED(    Caret,          KEY__6_Caret                    );
KEYS__SHIFTED(    Amp,            KEY__7_Ampersand                );
KEYS__SHIFTED(    Asterisk,       KEY__8_Asterisk                 );
KEYS__SHIFTED(    ParenL,         KEY__9_LeftParenthesis          );
// --- (keypad) ---
KEYS__DEFAULT(    KP0,            KEYPAD__0_Insert                );
KEYS__DEFAULT(    KP1,            KEYPAD__1_End                   );
KEYS__DEFAULT(    KP2,            KEYPAD__2_DownArrow             );
KEYS__DEFAULT(    KP3,            KEYPAD__3_PageDown              );
KEYS__DEFAULT(    KP4,            KEYPAD__4_LeftArrow             );
KEYS__DEFAULT(    KP5,            KEYPAD__5                       );
KEYS__DEFAULT(    KP6,            KEYPAD__6_RightArrow            );
KEYS__DEFAULT(    KP7,            KEYPAD__7_Home                  );
KEYS__DEFAULT(    KP8,            KEYPAD__8_UpArrow               );
KEYS__DEFAULT(    KP9,            KEYPAD__9_PageUp                );

// function
KEYS__DEFAULT(    F1,             KEY__F1                         );
KEYS__DEFAULT(    F2,             KEY__F2                         );
KEYS__DEFAULT(    F3,             KEY__F3                         );
KEYS__DEFAULT(    F4,             KEY__F4                         );
KEYS__DEFAULT(    F5,             KEY__F5                         );
KEYS__DEFAULT(    F6,             KEY__F6                         );
KEYS__DEFAULT(    F7,             KEY__F7                         );
KEYS__DEFAULT(    F8,             KEY__F8                         );
KEYS__DEFAULT(    F9,             KEY__F9                         );
KEYS__DEFAULT(    F10,            KEY__F10                        );
KEYS__DEFAULT(    F11,            KEY__F11                        );
KEYS__DEFAULT(    F12,            KEY__F12                        );

// whitespace and symbols
KEYS__DEFAULT(    Enter,          KEY__ReturnEnter                );
KEYS__DEFAULT(    Space,          KEY__Spacebar                   );
KEYS__DEFAULT(    Tab,            KEY__Tab                        );
// ---
KEYS__DEFAULT(    Bkslash,        KEY__Backslash_Pipe             );
KEYS__DEFAULT(    BrktL,          KEY__LeftBracket_LeftBrace      );
KEYS__DEFAULT(    BrktR,          KEY__RightBracket_RightBrace    );
KEYS__DEFAULT(    Comma,          KEY__Comma_LessThan             );
KEYS__DEFAULT(    Dash,           KEY__Dash_Underscore            );
KEYS__DEFAULT(    Equal,          KEY__Equal_Plus                 );
KEYS__DEFAULT(    Grave,          KEY__GraveAccent_Tilde          );
KEYS__DEFAULT(    Period,         KEY__Period_GreaterThan         );
KEYS__DEFAULT(    Quote,          KEY__SingleQuote_DoubleQuote    );
KEYS__DEFAULT(    Semicol,        KEY__Semicolon_Colon            );
KEYS__DEFAULT(    Slash,          KEY__Slash_Question             );
// --- (shifted) ---
KEYS__SHIFTED(    Pipe,           KEY__Backslash_Pipe             );
KEYS__SHIFTED(    BraceL,         KEY__LeftBracket_LeftBrace      );
KEYS__SHIFTED(    BraceR,         KEY__RightBracket_RightBrace    );
KEYS__SHIFTED(    LessThan,       KEY__Comma_LessThan             );
KEYS__SHIFTED(    Undersc,        KEY__Dash_Underscore            );
KEYS__SHIFTED(    Plus,           KEY__Equal_Plus                 );
KEYS__SHIFTED(    Tilde,          KEY__GraveAccent_Tilde          );
KEYS__SHIFTED(    GrtrThan,       KEY__Period_GreaterThan         );
KEYS__SHIFTED(    DblQuote,       KEY__SingleQuote_DoubleQuote    );
KEYS__SHIFTED(    Colon,          KEY__Semicolon_Colon            );
KEYS__SHIFTED(    Question,       KEY__Slash_Question             );
// --- (keypad) ---
KEYS__DEFAULT(    KPEnter,        KEYPAD__Enter                   );
// ---
KEYS__DEFAULT(    KPDec,          KEYPAD__Period_Delete           );
// ---
KEYS__DEFAULT(    KPAdd,          KEYPAD__Plus                    );
KEYS__DEFAULT(    KPSub,          KEYPAD__Minus                   );
KEYS__DEFAULT(    KPMul,          KEYPAD__Asterisk                );
KEYS__DEFAULT(    KPDiv,          KEYPAD__Slash                   );

// text control
KEYS__DEFAULT(    ArrowU,         KEY__UpArrow                    );
KEYS__DEFAULT(    ArrowD,         KEY__DownArrow                  );
KEYS__DEFAULT(    ArrowL,         KEY__LeftArrow                  );
KEYS__DEFAULT(    ArrowR,         KEY__RightArrow                 );
KEYS__DEFAULT(    Bs,             KEY__DeleteBackspace            );
KEYS__DEFAULT(    Del,            KEY__DeleteForward              );
KEYS__DEFAULT(    End,            KEY__End                        );
KEYS__DEFAULT(    Esc,            KEY__Escape                     );
KEYS__DEFAULT(    Home,           KEY__Home                       );
KEYS__DEFAULT(    Ins,            KEY__Insert                     );
KEYS__DEFAULT(    PageU,          KEY__PageUp                     );
KEYS__DEFAULT(    PageD,          KEY__PageDown                   );

// modifier
KEYS__DEFAULT(    AltR,           KEY__RightAlt                   );
KEYS__DEFAULT(    AltL,           KEY__LeftAlt                    );
KEYS__DEFAULT(    CtrlL,          KEY__LeftControl                );
KEYS__DEFAULT(    CtrlR,          KEY__RightControl               );
KEYS__DEFAULT(    GUIL,           KEY__LeftGUI                    );
KEYS__DEFAULT(    GUIR,           KEY__RightGUI                   );
KEYS__DEFAULT(    ShiftL,         KEY__LeftShift                  );
KEYS__DEFAULT(    ShiftR,         KEY__RightShift                 );

// lock
KEYS__DEFAULT(    Caps,           KEY__CapsLock                   );
KEYS__DEFAULT(    Scrl,           KEY__ScrollLock                 );
// --- (keypad) ---
KEYS__DEFAULT(    Num,            KEYPAD__NumLock_Clear           );

// special function
KEYS__DEFAULT(    App,            KEY__Application                );
KEYS__DEFAULT(    Pause,          KEY__Pause                      );
KEYS__DEFAULT(    PrScr,          KEY__PrintScreen                );

// international and language
KEYS__DEFAULT(    NonUSBackslash, KEY__NonUS_Backslash_Pipe       );
KEYS__DEFAULT(    NonUSPound,     KEY__NonUS_Pound_Tilde          );


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__FIRMWARE__LIB__LAYOUT__KEYS__H

