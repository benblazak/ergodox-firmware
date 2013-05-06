/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Implements the time defined in "../timer.h" for the ATMega32U4
 *
 * Prefix: `timer__`
 *
 * `timer__init()` is meant to be called once, on startup, by `main()`
 *
 * See the accompanying '.md' file for more documentation.
 *
 *
 * Usage Notes:
 *
 * - It's unnecessary to keep 32-bit (or even 16-bit) resolution when storing
 *   the value returned by `timer__get_milliseconds()` if you don't need it.
 *   Casting to a smaller unsigned value should be safe (as long as you cast
 *   *all* the values you plan to compare with each other to the same type!).
 *
 * - Use `end_time - start_time` for determining time difference.  Since the
 *   returned values are unsigned (and you should be storing them in unsigned
 *   variables as well) this will work across overflows, for up to the maximum
 *   amount of milliseconds representable by the type you're using.  (See [this
 *   answer] (http://stackoverflow.com/a/50632) on <http://stackoverflow.com/>
 *   if you're curious as to why.)
 */


#include <stdint.h>
#include <avr/interrupt.h>

// ----------------------------------------------------------------------------

static volatile uint32_t _milliseconds;

// ----------------------------------------------------------------------------

void timer__init(void) {
    TCCR0A = 0b10000010;
    TCCR0B = 0b00000011;
    TIMSK0 = 0b00000010;
    OCR0A  = 250;
}

uint32_t timer__get_milliseconds(void) {
    return _milliseconds;
}

// ----------------------------------------------------------------------------

// TODO: document this in the '.md' file too
ISR(TIMER0_COMPA_vect) {
    _milliseconds++;
}

