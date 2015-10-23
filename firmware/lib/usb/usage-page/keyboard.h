/* ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * USB Keyboard Key Codes (usage page 0x07)
 *
 * Prefixes: `KEYBOARD__`, `KEYPAD__`
 *
 * Taken from [the HID Usage Tables pdf][1], Section 10, which can be found on
 * [the HID Page][2] at <http://www.usb.org>
 *
 * - `Boot Keyboard Req.` indicates that the usage code is one that should be
 *   supported by the listed types of keyboards (104-key, ...) on boot
 *
 * - `KEY_` indicates a Keyboard key
 * - `KEYPAD_` indicates a Keypad key
 * - Multiple names concatenated in CamelCase indicate a single value
 * - Multiple names separated by `_`s indicate shifted or alternate values
 *
 * [1]: http://www.usb.org/developers/hidpage/Hut1_12v2.pdf
 * [2]: http://www.usb.org/developers/hidpage#HID_Usage
 */


#ifndef ERGODOX_FIRMWARE__FIRMWARE__LIB__USB__USAGE_PAGE__KEYBOARD__H
#define ERGODOX_FIRMWARE__FIRMWARE__LIB__USB__USAGE_PAGE__KEYBOARD__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


//      Name                              ID    // PC Mac Unix  Boot Keyboard Req.
//      ----------------------------      ----     -- --- ----  --------------------

//      (Reserved)                        0x00  // √  √   √     84/101/104

#define KEYBOARD__ErrorRollOver           0x01  // √  √   √     84/101/104
#define KEYBOARD__POSTFail                0x02  // √  √   √     84/101/104
#define KEYBOARD__ErrorUndefined          0x03  // √  √   √     84/101/104
#define KEYBOARD__a_A                     0x04  // √  √   √     84/101/104
#define KEYBOARD__b_B                     0x05  // √  √   √     84/101/104
#define KEYBOARD__c_C                     0x06  // √  √   √     84/101/104
#define KEYBOARD__d_D                     0x07  // √  √   √     84/101/104
#define KEYBOARD__e_E                     0x08  // √  √   √     84/101/104
#define KEYBOARD__f_F                     0x09  // √  √   √     84/101/104
#define KEYBOARD__g_G                     0x0A  // √  √   √     84/101/104
#define KEYBOARD__h_H                     0x0B  // √  √   √     84/101/104
#define KEYBOARD__i_I                     0x0C  // √  √   √     84/101/104
#define KEYBOARD__j_J                     0x0D  // √  √   √     84/101/104
#define KEYBOARD__k_K                     0x0E  // √  √   √     84/101/104
#define KEYBOARD__l_L                     0x0F  // √  √   √     84/101/104
#define KEYBOARD__m_M                     0x10  // √  √   √     84/101/104
#define KEYBOARD__n_N                     0x11  // √  √   √     84/101/104
#define KEYBOARD__o_O                     0x12  // √  √   √     84/101/104
#define KEYBOARD__p_P                     0x13  // √  √   √     84/101/104
#define KEYBOARD__q_Q                     0x14  // √  √   √     84/101/104
#define KEYBOARD__r_R                     0x15  // √  √   √     84/101/104
#define KEYBOARD__s_S                     0x16  // √  √   √     84/101/104
#define KEYBOARD__t_T                     0x17  // √  √   √     84/101/104
#define KEYBOARD__u_U                     0x18  // √  √   √     84/101/104
#define KEYBOARD__v_V                     0x19  // √  √   √     84/101/104
#define KEYBOARD__w_W                     0x1A  // √  √   √     84/101/104
#define KEYBOARD__x_X                     0x1B  // √  √   √     84/101/104
#define KEYBOARD__y_Y                     0x1C  // √  √   √     84/101/104
#define KEYBOARD__z_Z                     0x1D  // √  √   √     84/101/104
#define KEYBOARD__1_Exclamation           0x1E  // √  √   √     84/101/104
#define KEYBOARD__2_At                    0x1F  // √  √   √     84/101/104
#define KEYBOARD__3_Pound                 0x20  // √  √   √     84/101/104
#define KEYBOARD__4_Dollar                0x21  // √  √   √     84/101/104
#define KEYBOARD__5_Percent               0x22  // √  √   √     84/101/104
#define KEYBOARD__6_Caret                 0x23  // √  √   √     84/101/104
#define KEYBOARD__7_Ampersand             0x24  // √  √   √     84/101/104
#define KEYBOARD__8_Asterisk              0x25  // √  √   √     84/101/104
#define KEYBOARD__9_LeftParenthesis       0x26  // √  √   √     84/101/104
#define KEYBOARD__0_RightParenthesis      0x27  // √  √   √     84/101/104
#define KEYBOARD__ReturnEnter             0x28  // √  √   √     84/101/104
#define KEYBOARD__Escape                  0x29  // √  √   √     84/101/104
#define KEYBOARD__DeleteBackspace         0x2A  // √  √   √     84/101/104
#define KEYBOARD__Tab                     0x2B  // √  √   √     84/101/104
#define KEYBOARD__Spacebar                0x2C  // √  √   √     84/101/104
#define KEYBOARD__Dash_Underscore         0x2D  // √  √   √     84/101/104
#define KEYBOARD__Equal_Plus              0x2E  // √  √   √     84/101/104
#define KEYBOARD__LeftBracket_LeftBrace   0x2F  // √  √   √     84/101/104
#define KEYBOARD__RightBracket_RightBrace 0x30  // √  √   √     84/101/104
#define KEYBOARD__Backslash_Pipe          0x31  // √  √   √     84/101/104
#define KEYBOARD__NonUS_Pound_Tilde       0x32  // √  √   √     84/101/104
#define KEYBOARD__Semicolon_Colon         0x33  // √  √   √     84/101/104
#define KEYBOARD__SingleQuote_DoubleQuote 0x34  // √  √   √     84/101/104
#define KEYBOARD__GraveAccent_Tilde       0x35  // √  √   √     84/101/104
#define KEYBOARD__Comma_LessThan          0x36  // √  √   √     84/101/104
#define KEYBOARD__Period_GreaterThan      0x37  // √  √   √     84/101/104
#define KEYBOARD__Slash_Question          0x38  // √  √   √     84/101/104
#define KEYBOARD__CapsLock                0x39  // √  √   √     84/101/104
#define KEYBOARD__F1                      0x3A  // √  √   √     84/101/104
#define KEYBOARD__F2                      0x3B  // √  √   √     84/101/104
#define KEYBOARD__F3                      0x3C  // √  √   √     84/101/104
#define KEYBOARD__F4                      0x3D  // √  √   √     84/101/104
#define KEYBOARD__F5                      0x3E  // √  √   √     84/101/104
#define KEYBOARD__F6                      0x3F  // √  √   √     84/101/104
#define KEYBOARD__F7                      0x40  // √  √   √     84/101/104
#define KEYBOARD__F8                      0x41  // √  √   √     84/101/104
#define KEYBOARD__F9                      0x42  // √  √   √     84/101/104
#define KEYBOARD__F10                     0x43  // √  √   √     84/101/104
#define KEYBOARD__F11                     0x44  // √  √   √        101/104
#define KEYBOARD__F12                     0x45  // √  √   √        101/104
#define KEYBOARD__PrintScreen             0x46  // √  √   √        101/104
#define KEYBOARD__ScrollLock              0x47  // √  √   √     84/101/104
#define KEYBOARD__Pause                   0x48  // √  √   √        101/104
#define KEYBOARD__Insert                  0x49  // √  √   √        101/104
#define KEYBOARD__Home                    0x4A  // √  √   √        101/104
#define KEYBOARD__PageUp                  0x4B  // √  √   √        101/104
#define KEYBOARD__DeleteForward           0x4C  // √  √   √        101/104
#define KEYBOARD__End                     0x4D  // √  √   √        101/104
#define KEYBOARD__PageDown                0x4E  // √  √   √        101/104
#define KEYBOARD__RightArrow              0x4F  // √  √   √        101/104
#define KEYBOARD__LeftArrow               0x50  // √  √   √        101/104
#define KEYBOARD__DownArrow               0x51  // √  √   √        101/104
#define KEYBOARD__UpArrow                 0x52  // √  √   √        101/104

#define KEYPAD__NumLock_Clear             0x53  // √  √   √        101/104
#define KEYPAD__Slash                     0x54  // √  √   √        101/104
#define KEYPAD__Asterisk                  0x55  // √  √   √     84/101/104
#define KEYPAD__Minus                     0x56  // √  √   √     84/101/104
#define KEYPAD__Plus                      0x57  // √  √   √     84/101/104
#define KEYPAD__Enter                     0x58  // √  √   √        101/104
#define KEYPAD__1_End                     0x59  // √  √   √     84/101/104
#define KEYPAD__2_DownArrow               0x5A  // √  √   √     84/101/104
#define KEYPAD__3_PageDown                0x5B  // √  √   √     84/101/104
#define KEYPAD__4_LeftArrow               0x5C  // √  √   √     84/101/104
#define KEYPAD__5                         0x5D  // √  √   √     84/101/104
#define KEYPAD__6_RightArrow              0x5E  // √  √   √     84/101/104
#define KEYPAD__7_Home                    0x5F  // √  √   √     84/101/104
#define KEYPAD__8_UpArrow                 0x60  // √  √   √     84/101/104
#define KEYPAD__9_PageUp                  0x61  // √  √   √     84/101/104
#define KEYPAD__0_Insert                  0x62  // √  √   √     84/101/104
#define KEYPAD__Period_Delete             0x63  // √  √   √     84/101/104

#define KEYBOARD__NonUS_Backslash_Pipe    0x64  // √  √   √     84/101/104
#define KEYBOARD__Application             0x65  // √  -   √            104
#define KEYBOARD__Power                   0x66  // -  √   √     -

#define KEYPAD__Equal                     0x67  // -  √   -     -

#define KEYBOARD__F13                     0x68  // -  √   -     -
#define KEYBOARD__F14                     0x69  // -  √   -     -
#define KEYBOARD__F15                     0x6A  // -  √   -     -
#define KEYBOARD__F16                     0x6B  // -  -   -     -
#define KEYBOARD__F17                     0x6C  // -  -   -     -
#define KEYBOARD__F18                     0x6D  // -  -   -     -
#define KEYBOARD__F19                     0x6E  // -  -   -     -
#define KEYBOARD__F20                     0x6F  // -  -   -     -
#define KEYBOARD__F21                     0x70  // -  -   -     -
#define KEYBOARD__F22                     0x71  // -  -   -     -
#define KEYBOARD__F23                     0x72  // -  -   -     -
#define KEYBOARD__F24                     0x73  // -  -   -     -
#define KEYBOARD__Execute                 0x74  // -  -   √     -
#define KEYBOARD__Help                    0x75  // -  -   √     -
#define KEYBOARD__Menu                    0x76  // -  -   √     -
#define KEYBOARD__Select                  0x77  // -  -   √     -
#define KEYBOARD__Stop                    0x78  // -  -   √     -
#define KEYBOARD__Again                   0x79  // -  -   √     -
#define KEYBOARD__Undo                    0x7A  // -  -   √     -
#define KEYBOARD__Cut                     0x7B  // -  -   √     -
#define KEYBOARD__Copy                    0x7C  // -  -   √     -
#define KEYBOARD__Paste                   0x7D  // -  -   √     -
#define KEYBOARD__Find                    0x7E  // -  -   √     -
#define KEYBOARD__Mute                    0x7F  // -  -   √     -
#define KEYBOARD__VolumeUp                0x80  // -  -   √     -
#define KEYBOARD__VolumeDown              0x81  // -  -   √     -
#define KEYBOARD__LockingCapsLock         0x82  // -  -   √     -
#define KEYBOARD__LockingNumLock          0x83  // -  -   √     -
#define KEYBOARD__LockingScrollLock       0x84  // -  -   √     -

#define KEYPAD__Comma                     0x85  // -  -   -     -
#define KEYPAD__EqualSign                 0x86  // -  -   -     -

#define KEYBOARD__International1          0x87  // -  -   -     -
#define KEYBOARD__International2          0x88  // -  -   -     -
#define KEYBOARD__International3          0x89  // -  -   -     -
#define KEYBOARD__International4          0x8A  // -  -   -     -
#define KEYBOARD__International5          0x8B  // -  -   -     -
#define KEYBOARD__International6          0x8C  // -  -   -     -
#define KEYBOARD__International7          0x8D  // -  -   -     -
#define KEYBOARD__International8          0x8E  // -  -   -     -
#define KEYBOARD__International9          0x8F  // -  -   -     -
#define KEYBOARD__LANG1                   0x90  // -  -   -     -
#define KEYBOARD__LANG2                   0x91  // -  -   -     -
#define KEYBOARD__LANG3                   0x92  // -  -   -     -
#define KEYBOARD__LANG4                   0x93  // -  -   -     -
#define KEYBOARD__LANG5                   0x94  // -  -   -     -
#define KEYBOARD__LANG6                   0x95  // -  -   -     -
#define KEYBOARD__LANG7                   0x96  // -  -   -     -
#define KEYBOARD__LANG8                   0x97  // -  -   -     -
#define KEYBOARD__LANG9                   0x98  // -  -   -     -
#define KEYBOARD__AlternateErase          0x99  // -  -   -     -
#define KEYBOARD__SysReq_Attention        0x9A  // -  -   -     -
#define KEYBOARD__Cancel                  0x9B  // -  -   -     -
#define KEYBOARD__Clear                   0x9C  // -  -   -     -
#define KEYBOARD__Prior                   0x9D  // -  -   -     -
#define KEYBOARD__Return                  0x9E  // -  -   -     -
#define KEYBOARD__Separator               0x9F  // -  -   -     -
#define KEYBOARD__Out                     0xA0  // -  -   -     -
#define KEYBOARD__Oper                    0xA1  // -  -   -     -
#define KEYBOARD__Clear_Again             0xA2  // -  -   -     -
#define KEYBOARD__CrSel_Props             0xA3  // -  -   -     -
#define KEYBOARD__ExSel                   0xA4  // -  -   -     -

//      (Reserved)                  0xA5..0xAF  // -  -   -     -

#define KEYPAD__00                        0xB0  // -  -   -     -
#define KEYPAD__000                       0xB1  // -  -   -     -

#define KEYBOARD__ThousandsSeparator      0xB2  // -  -   -     -
#define KEYBOARD__DecimalSeparator        0xB3  // -  -   -     -
#define KEYBOARD__CurrencyUnit            0xB4  // -  -   -     -
#define KEYBOARD__CurrencySubunit         0xB5  // -  -   -     -

#define KEYPAD__LeftParenthesis           0xB6  // -  -   -     -
#define KEYPAD__RightParenthesis          0xB7  // -  -   -     -
#define KEYPAD__LeftBrace                 0xB8  // -  -   -     -
#define KEYPAD__RightBrace                0xB9  // -  -   -     -

#define KEYPAD__Tab                       0xBA  // -  -   -     -
#define KEYPAD__Backspace                 0xBB  // -  -   -     -
#define KEYPAD__A                         0xBC  // -  -   -     -
#define KEYPAD__B                         0xBD  // -  -   -     -
#define KEYPAD__C                         0xBE  // -  -   -     -
#define KEYPAD__D                         0xBF  // -  -   -     -
#define KEYPAD__E                         0xC0  // -  -   -     -
#define KEYPAD__F                         0xC1  // -  -   -     -
#define KEYPAD__XOR                       0xC2  // -  -   -     -
#define KEYPAD__Caret                     0xC3  // -  -   -     -
#define KEYPAD__Percent                   0xC4  // -  -   -     -
#define KEYPAD__LessThan                  0xC5  // -  -   -     -
#define KEYPAD__GreaterThan               0xC6  // -  -   -     -
#define KEYPAD__Ampersand                 0xC7  // -  -   -     -
#define KEYPAD__AmpersandAmpersand        0xC8  // -  -   -     -
#define KEYPAD__Pipe                      0xC9  // -  -   -     -
#define KEYPAD__PipePipe                  0xCA  // -  -   -     -
#define KEYPAD__Colon                     0xCB  // -  -   -     -
#define KEYPAD__Pound                     0xCC  // -  -   -     -
#define KEYPAD__Space                     0xCD  // -  -   -     -
#define KEYPAD__At                        0xCE  // -  -   -     -
#define KEYPAD__Exclamation               0xCF  // -  -   -     -
#define KEYPAD__MemoryStore               0xD0  // -  -   -     -
#define KEYPAD__MemoryRecall              0xD1  // -  -   -     -
#define KEYPAD__MemoryClear               0xD2  // -  -   -     -
#define KEYPAD__MemoryAdd                 0xD3  // -  -   -     -
#define KEYPAD__MemorySubtract            0xD4  // -  -   -     -
#define KEYPAD__MemoryMultiply            0xD5  // -  -   -     -
#define KEYPAD__MemoryDivide              0xD6  // -  -   -     -
#define KEYPAD__PlusMinus                 0xD7  // -  -   -     -
#define KEYPAD__Clear                     0xD8  // -  -   -     -
#define KEYPAD__ClearEntry                0xD9  // -  -   -     -
#define KEYPAD__Binary                    0xDA  // -  -   -     -
#define KEYPAD__Octal                     0xDB  // -  -   -     -
#define KEYPAD__Decimal                   0xDC  // -  -   -     -
#define KEYPAD__Hexadecimal               0xDD  // -  -   -     -

//      (Reserved)                  0xDE..0xDF  // -  -   -     -

#define KEYBOARD__LeftControl             0xE0  // √  √   √     84/101/104
#define KEYBOARD__LeftShift               0xE1  // √  √   √     84/101/104
#define KEYBOARD__LeftAlt                 0xE2  // √  √   √     84/101/104
#define KEYBOARD__LeftGUI                 0xE3  // √  √   √            104
#define KEYBOARD__RightControl            0xE4  // √  √   √        101/104
#define KEYBOARD__RightShift              0xE5  // √  √   √     84/101/104
#define KEYBOARD__RightAlt                0xE6  // √  √   √        101/104
#define KEYBOARD__RightGUI                0xE7  // √  √   √            104

//      (Reserved)                0xE8..0xFFFF  // -  -   -     -


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__SRC__LIB__USB__USAGE_PAGE__KEYBOARD__H

