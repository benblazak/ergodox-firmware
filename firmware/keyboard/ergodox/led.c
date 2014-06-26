/* ----------------------------------------------------------------------------
 * Copyright (c) 2013, 2014 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Implements the "LED" section of '.../firmware/keyboard.h'
 *
 * Code is specific to Teensy 2.0
 */

#include <stdbool.h>
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "../../../firmware/keyboard.h"

// ----------------------------------------------------------------------------

/**                                      macros/OPT__LED_BRIGHTNESS/description
 * A percentage of maximum brightness, with '1' being greatest and '0' being
 * not quite off
 */
#ifndef OPT__LED_BRIGHTNESS
    #error "OPT__LED_BRIGHTNESS not defined"
#endif

// ----------------------------------------------------------------------------

/**                                          types/struct led_state/description
 * For holding the state of the LEDs (if we ever need to save/restore them)
 */
struct led_state {
    bool led_1 : 1;
    bool led_2 : 1;
    bool led_3 : 1;
};

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

bool kb__led__read(uint8_t led) {
    switch(led) {
        case 1: return (PINB & (1<<5));  // topmost
	    case 2: return (PINB & (1<<6));  // middle
	    case 3: return (PINB & (1<<7));  // bottommost
        case 4: ;
        case 5: ;
    };
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

void kb__led__all_on(void) {
    for (uint8_t i=1; i<=3; i++)
        kb__led__on(i);
}

void kb__led__all_off(void) {
    for (uint8_t i=1; i<=3; i++)
        kb__led__off(i);
}

void kb__led__all_set(float n) {
    for (uint8_t i=1; i<=3; i++)
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

void kb__led__delay__error(void) {
    // make sure LED states have stabilized
    // - i'm not quite sure how long this takes; i would think it'd be nearly
    //   instant, but a bit of testing seemed to show that even 5ms isn't quite
    //   long enough; 10ms seems to work; at least we can afford the time here
    _delay_ms(10);

    struct led_state state = {
        .led_1 = kb__led__read(1),
        .led_2 = kb__led__read(2),
        .led_3 = kb__led__read(3),
    };

    kb__led__all_off();
    _delay_ms(167);
    kb__led__all_on();
    _delay_ms(167);
    kb__led__all_off();
    _delay_ms(167);
    kb__led__all_on();
    _delay_ms(167);
    kb__led__all_off();
    _delay_ms(167);
    kb__led__all_on();
    _delay_ms(167);
    kb__led__all_off();
    _delay_ms(167);

    if (state.led_1) kb__led__on(1);
    if (state.led_2) kb__led__on(2);
    if (state.led_3) kb__led__on(3);
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

