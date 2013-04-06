/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Partial key descriptions for the "Boot Keyboard Required" keys (see
 * <../../../firmware/lib/usb/usage-page/keyboard.h>).
 *
 * This header is meant to be included, not as an interface to anything, but in
 * order to centralize a bit of code that would otherwise be duplicated by most
 * layouts.
 *
 * Prefixes: `keys__`, [none]
 *
 * Usage: `#define` `KEYS__DEFAULT` and `KEYS__SHIFTED` before `#include`ing.
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
KEYS__DEFAULT(    a,              KEY__a_A                        );
KEYS__DEFAULT(    b,              KEY__b_B                        );
KEYS__DEFAULT(    c,              KEY__c_C                        );
KEYS__DEFAULT(    d,              KEY__d_D                        );
KEYS__DEFAULT(    e,              KEY__e_E                        );
KEYS__DEFAULT(    f,              KEY__f_F                        );
KEYS__DEFAULT(    g,              KEY__g_G                        );
KEYS__DEFAULT(    h,              KEY__h_H                        );
KEYS__DEFAULT(    i,              KEY__i_I                        );
KEYS__DEFAULT(    j,              KEY__j_J                        );
KEYS__DEFAULT(    k,              KEY__k_K                        );
KEYS__DEFAULT(    l,              KEY__l_L                        );
KEYS__DEFAULT(    m,              KEY__m_M                        );
KEYS__DEFAULT(    n,              KEY__n_N                        );
KEYS__DEFAULT(    o,              KEY__o_O                        );
KEYS__DEFAULT(    p,              KEY__p_P                        );
KEYS__DEFAULT(    q,              KEY__q_Q                        );
KEYS__DEFAULT(    r,              KEY__r_R                        );
KEYS__DEFAULT(    s,              KEY__s_S                        );
KEYS__DEFAULT(    t,              KEY__t_T                        );
KEYS__DEFAULT(    u,              KEY__u_U                        );
KEYS__DEFAULT(    v,              KEY__v_V                        );
KEYS__DEFAULT(    w,              KEY__w_W                        );
KEYS__DEFAULT(    x,              KEY__x_X                        );
KEYS__DEFAULT(    y,              KEY__y_Y                        );
KEYS__DEFAULT(    z,              KEY__z_Z                        );
// --- (shifted) ---
KEYS__SHIFTED(    A,              KEY__a_A                        );
KEYS__SHIFTED(    B,              KEY__b_B                        );
KEYS__SHIFTED(    C,              KEY__c_C                        );
KEYS__SHIFTED(    D,              KEY__d_D                        );
KEYS__SHIFTED(    E,              KEY__e_E                        );
KEYS__SHIFTED(    F,              KEY__f_F                        );
KEYS__SHIFTED(    G,              KEY__g_G                        );
KEYS__SHIFTED(    H,              KEY__h_H                        );
KEYS__SHIFTED(    I,              KEY__i_I                        );
KEYS__SHIFTED(    J,              KEY__j_J                        );
KEYS__SHIFTED(    K,              KEY__k_K                        );
KEYS__SHIFTED(    L,              KEY__l_L                        );
KEYS__SHIFTED(    M,              KEY__m_M                        );
KEYS__SHIFTED(    N,              KEY__n_N                        );
KEYS__SHIFTED(    O,              KEY__o_O                        );
KEYS__SHIFTED(    P,              KEY__p_P                        );
KEYS__SHIFTED(    Q,              KEY__q_Q                        );
KEYS__SHIFTED(    R,              KEY__r_R                        );
KEYS__SHIFTED(    S,              KEY__s_S                        );
KEYS__SHIFTED(    T,              KEY__t_T                        );
KEYS__SHIFTED(    U,              KEY__u_U                        );
KEYS__SHIFTED(    V,              KEY__v_V                        );
KEYS__SHIFTED(    W,              KEY__w_W                        );
KEYS__SHIFTED(    X,              KEY__x_X                        );
KEYS__SHIFTED(    Y,              KEY__y_Y                        );
KEYS__SHIFTED(    Z,              KEY__z_Z                        );

// numbers
KEYS__DEFAULT(    0,              KEY__0_RightParenthesis         );
KEYS__DEFAULT(    1,              KEY__1_Exclamation              );
KEYS__DEFAULT(    2,              KEY__2_At                       );
KEYS__DEFAULT(    3,              KEY__3_Pound                    );
KEYS__DEFAULT(    4,              KEY__4_Dollar                   );
KEYS__DEFAULT(    5,              KEY__5_Percent                  );
KEYS__DEFAULT(    6,              KEY__6_Caret                    );
KEYS__DEFAULT(    7,              KEY__7_Ampersand                );
KEYS__DEFAULT(    8,              KEY__8_Asterisk                 );
KEYS__DEFAULT(    9,              KEY__9_LeftParenthesis          );
// --- (shifted) ---
KEYS__SHIFTED(    parenR,         KEY__0_RightParenthesis         );
KEYS__SHIFTED(    exclam,         KEY__1_Exclamation              );
KEYS__SHIFTED(    at,             KEY__2_At                       );
KEYS__SHIFTED(    pound,          KEY__3_Pound                    );
KEYS__SHIFTED(    dollar,         KEY__4_Dollar                   );
KEYS__SHIFTED(    percent,        KEY__5_Percent                  );
KEYS__SHIFTED(    caret,          KEY__6_Caret                    );
KEYS__SHIFTED(    amp,            KEY__7_Ampersand                );
KEYS__SHIFTED(    asterisk,       KEY__8_Asterisk                 );
KEYS__SHIFTED(    parenL,         KEY__9_LeftParenthesis          );
// --- (keypad) ---
KEYS__DEFAULT(    kp0,            KEYPAD__0_Insert                );
KEYS__DEFAULT(    kp1,            KEYPAD__1_End                   );
KEYS__DEFAULT(    kp2,            KEYPAD__2_DownArrow             );
KEYS__DEFAULT(    kp3,            KEYPAD__3_PageDown              );
KEYS__DEFAULT(    kp4,            KEYPAD__4_LeftArrow             );
KEYS__DEFAULT(    kp5,            KEYPAD__5                       );
KEYS__DEFAULT(    kp6,            KEYPAD__6_RightArrow            );
KEYS__DEFAULT(    kp7,            KEYPAD__7_Home                  );
KEYS__DEFAULT(    kp8,            KEYPAD__8_UpArrow               );
KEYS__DEFAULT(    kp9,            KEYPAD__9_PageUp                );

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
KEYS__DEFAULT(    enter,          KEY__ReturnEnter                );
KEYS__DEFAULT(    space,          KEY__Spacebar                   );
KEYS__DEFAULT(    tab,            KEY__Tab                        );
// ---
KEYS__DEFAULT(    bkslash,        KEY__Backslash_Pipe             );
KEYS__DEFAULT(    brktL,          KEY__LeftBracket_LeftBrace      );
KEYS__DEFAULT(    brktR,          KEY__RightBracket_RightBrace    );
KEYS__DEFAULT(    comma,          KEY__Comma_LessThan             );
KEYS__DEFAULT(    dash,           KEY__Dash_Underscore            );
KEYS__DEFAULT(    equal,          KEY__Equal_Plus                 );
KEYS__DEFAULT(    grave,          KEY__GraveAccent_Tilde          );
KEYS__DEFAULT(    period,         KEY__Period_GreaterThan         );
KEYS__DEFAULT(    quote,          KEY__SingleQuote_DoubleQuote    );
KEYS__DEFAULT(    semicol,        KEY__Semicolon_Colon            );
KEYS__DEFAULT(    slash,          KEY__Slash_Question             );
// --- (shifted) ---
KEYS__SHIFTED(    pipe,           KEY__Backslash_Pipe             );
KEYS__SHIFTED(    braceL,         KEY__LeftBracket_LeftBrace      );
KEYS__SHIFTED(    braceR,         KEY__RightBracket_RightBrace    );
KEYS__SHIFTED(    lessThan,       KEY__Comma_LessThan             );
KEYS__SHIFTED(    undersc,        KEY__Dash_Underscore            );
KEYS__SHIFTED(    plus,           KEY__Equal_Plus                 );
KEYS__SHIFTED(    tilde,          KEY__GraveAccent_Tilde          );
KEYS__SHIFTED(    grtrThan,       KEY__Period_GreaterThan         );
KEYS__SHIFTED(    dblQuote,       KEY__SingleQuote_DoubleQuote    );
KEYS__SHIFTED(    colon,          KEY__Semicolon_Colon            );
KEYS__SHIFTED(    question,       KEY__Slash_Question             );
// --- (keypad) ---
KEYS__DEFAULT(    kpEnter,        KEYPAD__Enter                   );
// ---
KEYS__DEFAULT(    kpDec,          KEYPAD__Period_Delete           );
// ---
KEYS__DEFAULT(    kpAdd,          KEYPAD__Plus                    );
KEYS__DEFAULT(    kpSub,          KEYPAD__Minus                   );
KEYS__DEFAULT(    kpMul,          KEYPAD__Asterisk                );
KEYS__DEFAULT(    kpDiv,          KEYPAD__Slash                   );

// text control
KEYS__DEFAULT(    arrowU,         KEY__UpArrow                    );
KEYS__DEFAULT(    arrowD,         KEY__DownArrow                  );
KEYS__DEFAULT(    arrowL,         KEY__LeftArrow                  );
KEYS__DEFAULT(    arrowR,         KEY__RightArrow                 );
KEYS__DEFAULT(    bs,             KEY__DeleteBackspace            );
KEYS__DEFAULT(    del,            KEY__DeleteForward              );
KEYS__DEFAULT(    end,            KEY__End                        );
KEYS__DEFAULT(    esc,            KEY__Escape                     );
KEYS__DEFAULT(    home,           KEY__Home                       );
KEYS__DEFAULT(    ins,            KEY__Insert                     );
KEYS__DEFAULT(    pageU,          KEY__PageUp                     );
KEYS__DEFAULT(    pageD,          KEY__PageDown                   );

// modifier
KEYS__DEFAULT(    altR,           KEY__RightAlt                   );
KEYS__DEFAULT(    altL,           KEY__LeftAlt                    );
KEYS__DEFAULT(    ctrlL,          KEY__LeftControl                );
KEYS__DEFAULT(    ctrlR,          KEY__RightControl               );
KEYS__DEFAULT(    guiL,           KEY__LeftGUI                    );
KEYS__DEFAULT(    guiR,           KEY__RightGUI                   );
KEYS__DEFAULT(    shiftL,         KEY__LeftShift                  );
KEYS__DEFAULT(    shiftR,         KEY__RightShift                 );

// lock
KEYS__DEFAULT(    caps,           KEY__CapsLock                   );
KEYS__DEFAULT(    scrl,           KEY__ScrollLock                 );
// --- (keypad) ---
KEYS__DEFAULT(    num,            KEYPAD__NumLock_Clear           );

// special function
KEYS__DEFAULT(    app,            KEY__Application                );
KEYS__DEFAULT(    pause,          KEY__Pause                      );
KEYS__DEFAULT(    prScr,          KEY__PrintScreen                );

// international and language
KEYS__DEFAULT(    nonUSBkslash,   KEY__NonUS_Backslash_Pipe       );
KEYS__DEFAULT(    nonUSPound,     KEY__NonUS_Pound_Tilde          );


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__FIRMWARE__LIB__LAYOUT__KEYS__H

