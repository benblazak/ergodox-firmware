/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Implements the "LED" section of '.../firmware/keyboard.h'
 *
 * Code is specific to Teensy 2.0
 */


#include <stdint.h>
#include <avr/io.h>

// ----------------------------------------------------------------------------

#ifndef OPT__LED_BRIGHTNESS
    #error "OPT__LED_BRIGHTNESS not defined"
#endif
/**                                      macros/OPT__LED_BRIGHTNESS/description
 * A percentage of maximum brightness, with '1' being greatest and '0' being
 * not quite off
 */

// ----------------------------------------------------------------------------

void kb__led__on(uint8_t led) {
    switch(led) {
        case 1: (DDRB |=  (1<<5)); break;  // topmost
        case 2: (DDRB |=  (1<<6)); break;  // middle
        case 3: (DDRB |=  (1<<7)); break;  // bottommost
        case 4:                    break;
        case 5:                    break;
    };
}

void kb__led__off(uint8_t led) {
    switch(led) {
        case 1: (DDRB &= ~(1<<5)); break;  // topmost
	    case 2: (DDRB &= ~(1<<6)); break;  // middle
	    case 3: (DDRB &= ~(1<<7)); break;  // bottommost
        case 4:                    break;
        case 5:                    break;
    };
}

void kb__led__set(uint8_t led, float n) {
    switch(led) {
        case 1: (OCR1A = (uint8_t)((n) * 0xFF)); break;  // topmost
        case 2: (OCR1B = (uint8_t)((n) * 0xFF)); break;  // middle
        case 3: (OCR1C = (uint8_t)((n) * 0xFF)); break;  // bottommost
        case 4:                                  break;
        case 5:                                  break;
    };
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

void kb__led__all_on(void) {
    for(int8_t i=1; i<=3; i++)
        kb__led__on(i);
}

void kb__led__all_off(void) {
    for(int8_t i=1; i<=3; i++)
        kb__led__off(i);
}

void kb__led__all_set(float n) {
    for(int8_t i=1; i<=3; i++)
        kb__led__set(i, n);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

void kb__led__state__power_on(void) {
    kb__led__all_set( OPT__LED_BRIGHTNESS / 10 );
    kb__led__all_on();
}

void kb__led__state__ready(void) {
    kb__led__all_off();
    kb__led__all_set( OPT__LED_BRIGHTNESS );
}

void kb__led__delay__usb_init(void) {
	// need to delay for a total of ~1 second
    kb__led__set( 1, OPT__LED_BRIGHTNESS );
    _delay_ms(333);
    kb__led__set( 2, OPT__LED_BRIGHTNESS );
    _delay_ms(333);
    kb__led__set( 3, OPT__LED_BRIGHTNESS );
    _delay_ms(333);
}

