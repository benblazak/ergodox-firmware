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
#include "../../../../firmware/lib/data-types/list.h"
#include "../event-list.h"

// ----------------------------------------------------------------------------

#if F_CPU != 16000000
    #error "Expecting different CPU frequency"
#endif

// ----------------------------------------------------------------------------

static volatile uint16_t _milliseconds__counter;
static list__list_t      _milliseconds__scheduled_events;

// ----------------------------------------------------------------------------

uint8_t timer__init(void) {
    OCR0A  = 250;         // (ticks per millisecond)
    TCCR0A = 0b00000010;  // (configure Timer/Counter 0)
    TCCR0B = 0b00000011;  // (configure Timer/Counter 0)

    TIMSK0 = 0b00000010;  // (enable interrupt vector)

    return 0;  // success
}

uint16_t timer__get_milliseconds(void) {
    return _milliseconds__counter;
}

uint8_t timer__schedule_milliseconds(uint16_t ticks, void(*function)(void)) {
    return event_list__append(
            _milliseconds__scheduled_events, ticks, function );
}

void timer___tick_milliseconds(void) {
    static uint8_t _milliseconds__last_ticked;
    uint8_t elapsed = timer__get_milliseconds() - _milliseconds__last_ticked;

    for (uint8_t i=0; i<elapsed; i++)
        event_list__tick(_milliseconds__scheduled_events);

    _milliseconds__last_ticked += elapsed;
}

ISR(TIMER0_COMPA_vect) {
    _milliseconds__counter++;
}

