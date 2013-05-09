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
 * Usage:
 * - `#define` `KEYS__DEFAULT` and `KEYS__SHIFTED` before `#include`ing.
 *   - These macros should probably do what their names imply (i.e. define a
 *     "default" or "shifted" key, respectively, whatever that means to the
 *     implementing layout), but in a practical sense they can be used however
 *     one wants.  They're simply a really convenient way to generate almost
 *     the same bit of code for a lot of (key_name, key_code) pairs.
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
KEYS__DEFAULT(    a,              KEYBOARD__a_A                        );
KEYS__DEFAULT(    b,              KEYBOARD__b_B                        );
KEYS__DEFAULT(    c,              KEYBOARD__c_C                        );
KEYS__DEFAULT(    d,              KEYBOARD__d_D                        );
KEYS__DEFAULT(    e,              KEYBOARD__e_E                        );
KEYS__DEFAULT(    f,              KEYBOARD__f_F                        );
KEYS__DEFAULT(    g,              KEYBOARD__g_G                        );
KEYS__DEFAULT(    h,              KEYBOARD__h_H                        );
KEYS__DEFAULT(    i,              KEYBOARD__i_I                        );
KEYS__DEFAULT(    j,              KEYBOARD__j_J                        );
KEYS__DEFAULT(    k,              KEYBOARD__k_K                        );
KEYS__DEFAULT(    l,              KEYBOARD__l_L                        );
KEYS__DEFAULT(    m,              KEYBOARD__m_M                        );
KEYS__DEFAULT(    n,              KEYBOARD__n_N                        );
KEYS__DEFAULT(    o,              KEYBOARD__o_O                        );
KEYS__DEFAULT(    p,              KEYBOARD__p_P                        );
KEYS__DEFAULT(    q,              KEYBOARD__q_Q                        );
KEYS__DEFAULT(    r,              KEYBOARD__r_R                        );
KEYS__DEFAULT(    s,              KEYBOARD__s_S                        );
KEYS__DEFAULT(    t,              KEYBOARD__t_T                        );
KEYS__DEFAULT(    u,              KEYBOARD__u_U                        );
KEYS__DEFAULT(    v,              KEYBOARD__v_V                        );
KEYS__DEFAULT(    w,              KEYBOARD__w_W                        );
KEYS__DEFAULT(    x,              KEYBOARD__x_X                        );
KEYS__DEFAULT(    y,              KEYBOARD__y_Y                        );
KEYS__DEFAULT(    z,              KEYBOARD__z_Z                        );
// --- (shifted) ---
KEYS__SHIFTED(    A,              KEYBOARD__a_A                        );
KEYS__SHIFTED(    B,              KEYBOARD__b_B                        );
KEYS__SHIFTED(    C,              KEYBOARD__c_C                        );
KEYS__SHIFTED(    D,              KEYBOARD__d_D                        );
KEYS__SHIFTED(    E,              KEYBOARD__e_E                        );
KEYS__SHIFTED(    F,              KEYBOARD__f_F                        );
KEYS__SHIFTED(    G,              KEYBOARD__g_G                        );
KEYS__SHIFTED(    H,              KEYBOARD__h_H                        );
KEYS__SHIFTED(    I,              KEYBOARD__i_I                        );
KEYS__SHIFTED(    J,              KEYBOARD__j_J                        );
KEYS__SHIFTED(    K,              KEYBOARD__k_K                        );
KEYS__SHIFTED(    L,              KEYBOARD__l_L                        );
KEYS__SHIFTED(    M,              KEYBOARD__m_M                        );
KEYS__SHIFTED(    N,              KEYBOARD__n_N                        );
KEYS__SHIFTED(    O,              KEYBOARD__o_O                        );
KEYS__SHIFTED(    P,              KEYBOARD__p_P                        );
KEYS__SHIFTED(    Q,              KEYBOARD__q_Q                        );
KEYS__SHIFTED(    R,              KEYBOARD__r_R                        );
KEYS__SHIFTED(    S,              KEYBOARD__s_S                        );
KEYS__SHIFTED(    T,              KEYBOARD__t_T                        );
KEYS__SHIFTED(    U,              KEYBOARD__u_U                        );
KEYS__SHIFTED(    V,              KEYBOARD__v_V                        );
KEYS__SHIFTED(    W,              KEYBOARD__w_W                        );
KEYS__SHIFTED(    X,              KEYBOARD__x_X                        );
KEYS__SHIFTED(    Y,              KEYBOARD__y_Y                        );
KEYS__SHIFTED(    Z,              KEYBOARD__z_Z                        );

// numbers
KEYS__DEFAULT(    0,              KEYBOARD__0_RightParenthesis         );
KEYS__DEFAULT(    1,              KEYBOARD__1_Exclamation              );
KEYS__DEFAULT(    2,              KEYBOARD__2_At                       );
KEYS__DEFAULT(    3,              KEYBOARD__3_Pound                    );
KEYS__DEFAULT(    4,              KEYBOARD__4_Dollar                   );
KEYS__DEFAULT(    5,              KEYBOARD__5_Percent                  );
KEYS__DEFAULT(    6,              KEYBOARD__6_Caret                    );
KEYS__DEFAULT(    7,              KEYBOARD__7_Ampersand                );
KEYS__DEFAULT(    8,              KEYBOARD__8_Asterisk                 );
KEYS__DEFAULT(    9,              KEYBOARD__9_LeftParenthesis          );
// --- (shifted) ---
KEYS__SHIFTED(    parenR,         KEYBOARD__0_RightParenthesis         );
KEYS__SHIFTED(    exclam,         KEYBOARD__1_Exclamation              );
KEYS__SHIFTED(    at,             KEYBOARD__2_At                       );
KEYS__SHIFTED(    pound,          KEYBOARD__3_Pound                    );
KEYS__SHIFTED(    dollar,         KEYBOARD__4_Dollar                   );
KEYS__SHIFTED(    percent,        KEYBOARD__5_Percent                  );
KEYS__SHIFTED(    caret,          KEYBOARD__6_Caret                    );
KEYS__SHIFTED(    amp,            KEYBOARD__7_Ampersand                );
KEYS__SHIFTED(    asterisk,       KEYBOARD__8_Asterisk                 );
KEYS__SHIFTED(    parenL,         KEYBOARD__9_LeftParenthesis          );
// --- (keypad) ---
KEYS__DEFAULT(    kp0,            KEYPAD__0_Insert                     );
KEYS__DEFAULT(    kp1,            KEYPAD__1_End                        );
KEYS__DEFAULT(    kp2,            KEYPAD__2_DownArrow                  );
KEYS__DEFAULT(    kp3,            KEYPAD__3_PageDown                   );
KEYS__DEFAULT(    kp4,            KEYPAD__4_LeftArrow                  );
KEYS__DEFAULT(    kp5,            KEYPAD__5                            );
KEYS__DEFAULT(    kp6,            KEYPAD__6_RightArrow                 );
KEYS__DEFAULT(    kp7,            KEYPAD__7_Home                       );
KEYS__DEFAULT(    kp8,            KEYPAD__8_UpArrow                    );
KEYS__DEFAULT(    kp9,            KEYPAD__9_PageUp                     );

// function
KEYS__DEFAULT(    F1,             KEYBOARD__F1                         );
KEYS__DEFAULT(    F2,             KEYBOARD__F2                         );
KEYS__DEFAULT(    F3,             KEYBOARD__F3                         );
KEYS__DEFAULT(    F4,             KEYBOARD__F4                         );
KEYS__DEFAULT(    F5,             KEYBOARD__F5                         );
KEYS__DEFAULT(    F6,             KEYBOARD__F6                         );
KEYS__DEFAULT(    F7,             KEYBOARD__F7                         );
KEYS__DEFAULT(    F8,             KEYBOARD__F8                         );
KEYS__DEFAULT(    F9,             KEYBOARD__F9                         );
KEYS__DEFAULT(    F10,            KEYBOARD__F10                        );
KEYS__DEFAULT(    F11,            KEYBOARD__F11                        );
KEYS__DEFAULT(    F12,            KEYBOARD__F12                        );

// whitespace and symbols
KEYS__DEFAULT(    enter,          KEYBOARD__ReturnEnter                );
KEYS__DEFAULT(    space,          KEYBOARD__Spacebar                   );
KEYS__DEFAULT(    tab,            KEYBOARD__Tab                        );
// ---
KEYS__DEFAULT(    bkslash,        KEYBOARD__Backslash_Pipe             );
KEYS__DEFAULT(    brktL,          KEYBOARD__LeftBracket_LeftBrace      );
KEYS__DEFAULT(    brktR,          KEYBOARD__RightBracket_RightBrace    );
KEYS__DEFAULT(    comma,          KEYBOARD__Comma_LessThan             );
KEYS__DEFAULT(    dash,           KEYBOARD__Dash_Underscore            );
KEYS__DEFAULT(    equal,          KEYBOARD__Equal_Plus                 );
KEYS__DEFAULT(    grave,          KEYBOARD__GraveAccent_Tilde          );
KEYS__DEFAULT(    period,         KEYBOARD__Period_GreaterThan         );
KEYS__DEFAULT(    quote,          KEYBOARD__SingleQuote_DoubleQuote    );
KEYS__DEFAULT(    semicol,        KEYBOARD__Semicolon_Colon            );
KEYS__DEFAULT(    slash,          KEYBOARD__Slash_Question             );
// --- (shifted) ---
KEYS__SHIFTED(    pipe,           KEYBOARD__Backslash_Pipe             );
KEYS__SHIFTED(    braceL,         KEYBOARD__LeftBracket_LeftBrace      );
KEYS__SHIFTED(    braceR,         KEYBOARD__RightBracket_RightBrace    );
KEYS__SHIFTED(    lessThan,       KEYBOARD__Comma_LessThan             );
KEYS__SHIFTED(    undersc,        KEYBOARD__Dash_Underscore            );
KEYS__SHIFTED(    plus,           KEYBOARD__Equal_Plus                 );
KEYS__SHIFTED(    tilde,          KEYBOARD__GraveAccent_Tilde          );
KEYS__SHIFTED(    grtrThan,       KEYBOARD__Period_GreaterThan         );
KEYS__SHIFTED(    dblQuote,       KEYBOARD__SingleQuote_DoubleQuote    );
KEYS__SHIFTED(    colon,          KEYBOARD__Semicolon_Colon            );
KEYS__SHIFTED(    question,       KEYBOARD__Slash_Question             );
// --- (keypad) ---
KEYS__DEFAULT(    kpEnter,        KEYPAD__Enter                        );
// ---
KEYS__DEFAULT(    kpDec,          KEYPAD__Period_Delete                );
// ---
KEYS__DEFAULT(    kpAdd,          KEYPAD__Plus                         );
KEYS__DEFAULT(    kpSub,          KEYPAD__Minus                        );
KEYS__DEFAULT(    kpMul,          KEYPAD__Asterisk                     );
KEYS__DEFAULT(    kpDiv,          KEYPAD__Slash                        );

// text control
KEYS__DEFAULT(    arrowU,         KEYBOARD__UpArrow                    );
KEYS__DEFAULT(    arrowD,         KEYBOARD__DownArrow                  );
KEYS__DEFAULT(    arrowL,         KEYBOARD__LeftArrow                  );
KEYS__DEFAULT(    arrowR,         KEYBOARD__RightArrow                 );
KEYS__DEFAULT(    bs,             KEYBOARD__DeleteBackspace            );
KEYS__DEFAULT(    del,            KEYBOARD__DeleteForward              );
KEYS__DEFAULT(    end,            KEYBOARD__End                        );
KEYS__DEFAULT(    esc,            KEYBOARD__Escape                     );
KEYS__DEFAULT(    home,           KEYBOARD__Home                       );
KEYS__DEFAULT(    ins,            KEYBOARD__Insert                     );
KEYS__DEFAULT(    pageU,          KEYBOARD__PageUp                     );
KEYS__DEFAULT(    pageD,          KEYBOARD__PageDown                   );

// modifier
KEYS__DEFAULT(    altR,           KEYBOARD__RightAlt                   );
KEYS__DEFAULT(    altL,           KEYBOARD__LeftAlt                    );
KEYS__DEFAULT(    ctrlL,          KEYBOARD__LeftControl                );
KEYS__DEFAULT(    ctrlR,          KEYBOARD__RightControl               );
KEYS__DEFAULT(    guiL,           KEYBOARD__LeftGUI                    );
KEYS__DEFAULT(    guiR,           KEYBOARD__RightGUI                   );
KEYS__DEFAULT(    shiftL,         KEYBOARD__LeftShift                  );
KEYS__DEFAULT(    shiftR,         KEYBOARD__RightShift                 );

// lock
KEYS__DEFAULT(    caps,           KEYBOARD__CapsLock                   );
KEYS__DEFAULT(    scrl,           KEYBOARD__ScrollLock                 );
// --- (keypad) ---
KEYS__DEFAULT(    num,            KEYPAD__NumLock_Clear                );

// special function
KEYS__DEFAULT(    app,            KEYBOARD__Application                );
KEYS__DEFAULT(    pause,          KEYBOARD__Pause                      );
KEYS__DEFAULT(    prScr,          KEYBOARD__PrintScreen                );

// international and language
KEYS__DEFAULT(    nonUSBkslash,   KEYBOARD__NonUS_Backslash_Pipe       );
KEYS__DEFAULT(    nonUSPound,     KEYBOARD__NonUS_Pound_Tilde          );


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__FIRMWARE__LIB__LAYOUT__KEYS__H

