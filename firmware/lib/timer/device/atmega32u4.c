/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Implements the device specific functionality of ".../firmware/lib/timer" for
 * the ATMega32U4
 *
 * See the accompanying '.md' file for further documentation.
 */


#include <avr/interrupt.h>
#include <avr/io.h>
#include "../common.h"

// ----------------------------------------------------------------------------

#if F_CPU != 16000000
    #error "Expecting different CPU frequency"
#endif

// ----------------------------------------------------------------------------

uint8_t _device__init(void) {
    OCR0A  = 250;         // (ticks per millisecond)
    TCCR0A = 0b00000010;  // (configure Timer/Counter 0)
    TCCR0B = 0b00000011;  // (configure Timer/Counter 0)

    TIMSK0 = 0b00000010;  // (enable interrupt vector)

    return 0;  // success
}

// ----------------------------------------------------------------------------

ISR(TIMER0_COMPA_vect) {
    _milliseconds++;

    // if possible, move all events from `...to_schedule` into `...scheduled`
    // - interrupts are disabled here, so it's safe to operate on the list
    //   without locking it, as long as it's not already locked
    if (!_milliseconds_to_schedule_lock)
        _event_list__move(_milliseconds_scheduled, _milliseconds_to_schedule);

    _event_list__update(_milliseconds_scheduled);
}

