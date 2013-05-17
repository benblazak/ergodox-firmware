/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Implements the timer interface defined in ".../firmware/lib/timer.h" for the
 * ATMega32U4
 *
 * See the accompanying '.md' file for further documentation.
 *
 * Notes:
 * - Not all of this code is device-specific, but the parts that aren't are
 *   trivial enough that it's not worth separating them.
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

/**                                               variables/_cycles/description
 * The number of scan cycles since the timer was initialized (mod 2^16)
 */
static uint16_t _cycles;

/**                                    variables/_cycles__scheduled/description
 * A list of scheduled events, to be run in a given number of cycles
 *
 * After initialization, this should *only* be used as an argument to an
 * `event_list__...()` function.
 */
static list__list_t * _cycles__scheduled;

/**                                         variables/_milliseconds/description
 * The number of milliseconds since the timer was initialized (mod 2^16)
 */
static volatile uint16_t _milliseconds;

/**                              variables/_milliseconds__scheduled/description
 * A list of scheduled events, to be run in a given number of milliseconds
 *
 * After initialization, this should *only* be used as an argument to an
 * `event_list__...()` function.
 */
static list__list_t * _milliseconds__scheduled;

// ----------------------------------------------------------------------------

uint8_t timer__init(void) {
    _cycles__scheduled       = list__new();
    _milliseconds__scheduled = list__new();

    if (!_cycles__scheduled || !_milliseconds__scheduled) {
        list__free(_cycles__scheduled);
        list__free(_milliseconds__scheduled);
        return 1;  // error
    }

    OCR0A  = 250;         // (ticks per millisecond)
    TCCR0A = 0b00000010;  // (configure Timer/Counter 0)
    TCCR0B = 0b00000011;  // (configure Timer/Counter 0)

    TIMSK0 = 0b00000010;  // (enable interrupt vector)

    return 0;  // success
}

uint16_t timer__get_cycles(void) {
    return _cycles;
}

uint16_t timer__get_milliseconds(void) {
    return _milliseconds;
}

uint8_t timer__schedule_cycles(uint16_t cycles, void(*function)(void)) {
    return event_list__append(_cycles__scheduled, cycles, function);
}

uint8_t timer__schedule_milliseconds( uint16_t milliseconds,
                                      void(*function)(void) ) {
    return event_list__append( _milliseconds__scheduled,
                                milliseconds,
                                function );
}

// ----------------------------------------------------------------------------

void timer___tick_cycles (void) {
        _cycles++;
        event_list__tick(_cycles__scheduled);
}

// ----------------------------------------------------------------------------

ISR(TIMER0_COMPA_vect) {
    _milliseconds++;
    event_list__tick(_milliseconds__scheduled);
}

