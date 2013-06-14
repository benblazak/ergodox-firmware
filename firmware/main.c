/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * `main()`: tying it all together
 *
 * If you're just trying to get a feel for the source, I'd glance over this
 * file, then move on to ".../firmware/keyboard.h"
 */


#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "../firmware/keyboard.h"
#include "../firmware/lib/timer.h"
#include "../firmware/lib/usb.h"
#include "../firmware/lib/data-types/list.h"
#include "./main.h"

// ----------------------------------------------------------------------------

/**                                       macros/OPT__DEBOUNCE_TIME/description
 * The minimum amount of time to wait between two scans of a key, in
 * milliseconds
 *
 * Notes:
 * - Cherry MX bounce time <= 5ms (at 16 in/sec actuation speed) (spec)
 */
#ifndef OPT__DEBOUNCE_TIME
    #error "OPT__DEBOUNCE_TIME not defined"
#endif

// ----------------------------------------------------------------------------

#define  main__is_pressed   is_pressed
#define  main__was_pressed  was_pressed
#define  main__row          row
#define  main__col          col
#define  main__flags        flags

// ----------------------------------------------------------------------------

bool (* is_pressed) [OPT__KB__ROWS][OPT__KB__COLUMNS]
          = &( bool [OPT__KB__ROWS][OPT__KB__COLUMNS] ){};
bool (* was_pressed) [OPT__KB__ROWS][OPT__KB__COLUMNS]
           = &( bool [OPT__KB__ROWS][OPT__KB__COLUMNS] ){};

uint8_t row;
uint8_t col;

struct main__flags_t flags = { .update_leds = true };

// ----------------------------------------------------------------------------

/**                                                  functions/main/description
 * Initialize things, then loop forever
 *
 * There are a few interesting things that happen here, but most things happen
 * elsewhere.  Have a look through the source, especially the documentation,
 * and especially in ".../firmware/keyboard/.../layout", to see what's going
 * on.
 */
int main(void) {
    static bool (*temp)[OPT__KB__ROWS][OPT__KB__COLUMNS]; // for swapping below
    static bool key_is_pressed;
    static bool key_was_pressed;

    static uint8_t time_scan_started;

    kb__init();  // initialize hardware (besides USB and timer)

    kb__led__state__power_on();

    usb__init();
    while (!usb__is_configured());
    kb__led__delay__usb_init();  // give the OS time to load drivers, etc.

    timer__init();

    kb__led__state__ready();

    time_scan_started  // on the first iteration, scan immediately
        = timer__get_milliseconds() - OPT__DEBOUNCE_TIME;

    for (;;) {
        temp = is_pressed;
        is_pressed = was_pressed;
        was_pressed = temp;

        // delay if necessary, then rescan
        while( (uint8_t)(timer__get_milliseconds()-time_scan_started)
               < OPT__DEBOUNCE_TIME );
        time_scan_started = timer__get_milliseconds();
        kb__update_matrix(*is_pressed);

        // "execute" keys that have changed state
        for (row=0; row<OPT__KB__ROWS; row++) {
            for (col=0; col<OPT__KB__COLUMNS; col++) {
                key_is_pressed = (*is_pressed)[row][col];
                key_was_pressed = (*was_pressed)[row][col];

                if (key_is_pressed != key_was_pressed)
                    kb__layout__exec_key(key_is_pressed, row, col);
            }
        }

        usb__kb__send_report();  // (even if nothing's changed)

        // note: only use the `kb__led__logical...` functions here, since the
        // meaning of the physical LEDs should be controlled by the layout
        if (flags.update_leds) {
            #define  read  usb__kb__read_led
            #define  on    kb__led__logical_on
            #define  off   kb__led__logical_off
            read('N') ? on('N') : off('N');  // numlock
            read('C') ? on('C') : off('C');  // capslock
            read('S') ? on('S') : off('S');  // scroll lock
            read('O') ? on('O') : off('O');  // compose
            read('K') ? on('K') : off('K');  // kana
            #undef read
            #undef on
            #undef off
        }

        timer___tick_cycles();
    }

    return 0;
}

