/* ----------------------------------------------------------------------------
 * Copyright (c) 2012, 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Implements the "keyboard" section of '.../firmware/lib/usb.h'
 */

#include <stdbool.h>
#include <stdint.h>
#include "../usage-page/keyboard.h"
#include "./keyboard/from-pjrc/usb.h"
#include "../../usb.h"

// ----------------------------------------------------------------------------

uint8_t usb__kb__set_key(bool pressed, uint8_t keycode) {
    // no-op
    if (keycode == 0)
        return 1;

    // modifier keys
    switch (keycode) {
        case KEYBOARD__LeftControl:  (pressed)
                                     ? (keyboard_modifier_keys |=  (1<<0))
                                     : (keyboard_modifier_keys &= ~(1<<0));
                                     return 0;
        case KEYBOARD__LeftShift:    (pressed)
                                     ? (keyboard_modifier_keys |=  (1<<1))
                                     : (keyboard_modifier_keys &= ~(1<<1));
                                     return 0;
        case KEYBOARD__LeftAlt:      (pressed)
                                     ? (keyboard_modifier_keys |=  (1<<2))
                                     : (keyboard_modifier_keys &= ~(1<<2));
                                     return 0;
        case KEYBOARD__LeftGUI:      (pressed)
                                     ? (keyboard_modifier_keys |=  (1<<3))
                                     : (keyboard_modifier_keys &= ~(1<<3));
                                     return 0;
        case KEYBOARD__RightControl: (pressed)
                                     ? (keyboard_modifier_keys |=  (1<<4))
                                     : (keyboard_modifier_keys &= ~(1<<4));
                                     return 0;
        case KEYBOARD__RightShift:   (pressed)
                                     ? (keyboard_modifier_keys |=  (1<<5))
                                     : (keyboard_modifier_keys &= ~(1<<5));
                                     return 0;
        case KEYBOARD__RightAlt:     (pressed)
                                     ? (keyboard_modifier_keys |=  (1<<6))
                                     : (keyboard_modifier_keys &= ~(1<<6));
                                     return 0;
        case KEYBOARD__RightGUI:     (pressed)
                                     ? (keyboard_modifier_keys |=  (1<<7))
                                     : (keyboard_modifier_keys &= ~(1<<7));
                                     return 0;
    }

    // all others
    for (uint8_t i=0; i<6; i++) {
        if (pressed) {
            if (keyboard_keys[i] == 0) {
                keyboard_keys[i] = keycode;
                return 0;
            }
        } else {
            if (keyboard_keys[i] == keycode) {
                keyboard_keys[i] = 0;
                return 0;
            }
        }
    }

    return 1;
}

bool usb__kb__read_key(uint8_t keycode) {
    // no-op
    if (keycode == 0)
        return false;

    // modifier keys
    switch (keycode) {
        case KEYBOARD__LeftControl:  return (keyboard_modifier_keys & (1<<0));
        case KEYBOARD__LeftShift:    return (keyboard_modifier_keys & (1<<1));
        case KEYBOARD__LeftAlt:      return (keyboard_modifier_keys & (1<<2));
        case KEYBOARD__LeftGUI:      return (keyboard_modifier_keys & (1<<3));
        case KEYBOARD__RightControl: return (keyboard_modifier_keys & (1<<4));
        case KEYBOARD__RightShift:   return (keyboard_modifier_keys & (1<<5));
        case KEYBOARD__RightAlt:     return (keyboard_modifier_keys & (1<<6));
        case KEYBOARD__RightGUI:     return (keyboard_modifier_keys & (1<<7));
    }

    // all others
    for (uint8_t i=0; i<6; i++)
        if (keyboard_keys[i] == keycode)
            return true;

    return false;
}

bool usb__kb__read_led(char led) {
    switch(led) {
        case 'N': return keyboard_leds & (1<<0);  // numlock
        case 'C': return keyboard_leds & (1<<1);  // capslock
        case 'S': return keyboard_leds & (1<<2);  // scroll lock
        case 'O': return keyboard_leds & (1<<3);  // compose
        case 'K': return keyboard_leds & (1<<4);  // kana
    };
    return false;
}

uint8_t usb__kb__send_report(void) {
    return usb_keyboard_send();
}

