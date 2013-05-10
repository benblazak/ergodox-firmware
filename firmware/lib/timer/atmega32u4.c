/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Implements the timer functions defined in "../timer.h" for the ATMega32U4
 *
 * See the accompanying '.md' file for further documentation.
 */


#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "../../../firmware/lib/data-types/list.h"

// ----------------------------------------------------------------------------

#if F_CPU != 16000000
    #error "Expecting different CPU frequency"
#endif

// ----------------------------------------------------------------------------

typedef struct {
    list__node_t _private;
    uint16_t milliseconds;
    void(*function)(void);
} event_t;

// ----------------------------------------------------------------------------

static volatile uint16_t _milliseconds;

// use `_to_schedule__lock` to make sure that only one function at a time is
// accessing `_to_schedule`, even if that function is preempted in the middle
// of its execution by an interrupt
static list__list_t *    _to_schedule;
static bool              _to_schedule__lock;

// for use *only* in `ISR(TIMER0_COMPA_vect)` (after initialization)
static list__list_t * _scheduled;

// ----------------------------------------------------------------------------

uint8_t timer__init(void) {
    _scheduled   = list__new();
    _to_schedule = list__new();

    if (!_scheduled || !_to_schedule)
        return 1;  // error

    OCR0A  = 250;         // (ticks per millisecond)
    TCCR0A = 0b00000010;  // (configure Timer/Counter 0)
    TCCR0B = 0b00000011;  // (configure Timer/Counter 0)

    TIMSK0 = 0b00000010;  // (enable interrupt vector)

    return 0;  // success
}

uint16_t timer__get_milliseconds(void) {
    return _milliseconds;
}

uint8_t timer__schedule(uint16_t milliseconds, void(*function)(void)) {
    if (!function) return 0;  // success: there is no function to add
    if (_to_schedule__lock) return 1;  // error

    _to_schedule__lock = true;

    event_t * event = list__insert(_to_schedule, -1, malloc(sizeof(event_t)));
    if (!event) {
        _to_schedule__lock = false;
        return 2;  // error
    }

    event->milliseconds = milliseconds;
    event->function     = function;

    _to_schedule__lock = false;
    return 0;  // success
}

// ----------------------------------------------------------------------------

ISR(TIMER0_COMPA_vect) {
    _milliseconds++;

    if (!_to_schedule__lock) {
        _to_schedule__lock = true;

        // pop events from `_to_schedule` and insert them into `_scheduled`
        // until there are no more events in `_to_schedule`
        while ( list__insert( _scheduled, -1,
                              list__pop_index(_to_schedule, 0) ) );

        _to_schedule__lock = false;
    }

    for (event_t * event = _scheduled->head; event;) {
        if (event->milliseconds == 0) {
            (*event->function)();
            event = list__pop_node_next(_scheduled, event);
        } else {
            event->milliseconds--;
            event = event->_private.next;
        }
    }
}

