/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Implements the device specific portion of the timer interface defined in
 * ".../firmware/lib/timer.h" for the ATMega32U4
 *
 * See the accompanying '.md' file for further documentation.
 */


#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include "../../timer.h"

// ----------------------------------------------------------------------------

#if F_CPU != 16000000
    #error "Expecting different CPU frequency"
#endif

// ----------------------------------------------------------------------------

static struct {
    volatile uint16_t counter;
} milliseconds;

// ----------------------------------------------------------------------------

uint8_t timer__init(void) {
    OCR0A  = 250;         // (ticks (of hardware timer) per millisecond)
    TCCR0A = 0b00000010;  // (configure Timer/Counter 0)
    TCCR0B = 0b00000011;  // (configure Timer/Counter 0)

    TIMSK0 = 0b00000010;  // (enable interrupt vector)

    return 0;  // success
}

uint16_t timer__get_milliseconds(void) {
    return milliseconds.counter;
}

ISR(TIMER0_COMPA_vect) {
    milliseconds.counter++;
}

