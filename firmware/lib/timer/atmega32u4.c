/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Implements the timer functions defined in "../timer.h" for the ATMega32U4
 *
 * Prefix: `timer__`
 *
 * See the accompanying '.md' file for documentation.
 */


#include <stdint.h>
#include <avr/interrupt.h>

// ----------------------------------------------------------------------------

static volatile uint32_t _milliseconds;

// ----------------------------------------------------------------------------

uint8_t timer__init(void) {
    TCCR0A = 0b10000010;
    TCCR0B = 0b00000011;
    TIMSK0 = 0b00000010;
    OCR0A  = 250;

    return 0;  // success
}

uint32_t timer__get_milliseconds(void) {
    return _milliseconds;
}

// ----------------------------------------------------------------------------

ISR(TIMER0_COMPA_vect) {
    _milliseconds++;
}

