/* ----------------------------------------------------------------------------
 * Copyright (c) 2013, 2014 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Default actions for changes in logical (host controlled) LED states
 *
 * Notes:
 * - LEDs 1 and 2 are controlled by the corresponding layer keys.
 */


void kb__led__logical_on(char led) {
    switch(led) {
        case 'N':                 break;  // numlock
        case 'C': kb__led__on(3); break;  // capslock
        case 'S':                 break;  // scroll lock
        case 'O':                 break;  // compose
        case 'K':                 break;  // kana
    };
}

void kb__led__logical_off(char led) {
    switch(led) {
        case 'N':                  break;  // numlock
        case 'C': kb__led__off(3); break;  // capslock
        case 'S':                  break;  // scroll lock
        case 'O':                  break;  // compose
        case 'K':                  break;  // kana
    };
}

