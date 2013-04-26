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
 * TODO: make sure this is how we want to do things...
 * TODO: document and write header
 * TODO: notes
 * - it's unnecessary to keep 32 (or even 16) bit resolution if you don't need
 *   it;  functions that don't should cast to uint8_t or uint16_t
 * - use `end-start` for determining time difference.  since the values are
 *   unsigned, this will work across overflows, for up to the maximum amount of
 *   time representable by the type you're using
 * - `timer__init()` should be called once by `main()`
 */


#include <stdint.h>
#include <avr/interrupt.h>

// ----------------------------------------------------------------------------

static volatile uint32_t _milliseconds;

// ----------------------------------------------------------------------------

void timer__init(void) {
    // /TODO

    // references:
    //
    // Newbie's Guide to AVR Timers
    // tutorial by Dean Camera
    // http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&t=50106
    //
    // the atmega32u4 spec sheet
    //
    // the reference somewhere about what happens to unsigned things when
    // negative values are assigned to them

    // --- python3 ---
    // >>> f_cpu = 16000000
    // >>> .001/((1/f_cpu)*64)
    // 250.00000000000003
    // >>> (.001*f_cpu)/(64)
    // 250.0
    // ---------------

    // table
    // ------------------------------------------
    // prescale value       ticks per millisecond
    // --------------       ---------------------
    // 1                    16000
    // 8                     2000
    // 64                     250
    // 256                    62.5
    // 1024                   15.625

    // - we want a period = 1 millisecond = .001 seconds
    // - cpu = 16 MHz; we can prescale at clk_io/64 to get 250 prescaled ticks
    //   per millisecond (which fits into a uint8_t, just barely)
    //
    // so we want to use TCCR0A, on the CTC (clear timer on compare match)
    // mode, with compare interrupt enabled
}

uint32_t timer__get_milliseconds(void) {
    return _milliseconds;
}

// ----------------------------------------------------------------------------

ISR(TIMER0_COMPA_vect) {
    _milliseconds++;
}

