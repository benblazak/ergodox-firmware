/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * `main()`: tying it all together
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

#ifndef OPT__DEBOUNCE_TIME
    #error "OPT__DEBOUNCE_TIME not defined"
#endif
/**                                       macros/OPT__DEBOUNCE_TIME/description
 * The minimum amount of time to wait between two scans of a key, in
 * milliseconds
 *
 * Notes:
 * - Cherry MX bounce time <= 5ms (at 16 in/sec actuation speed) (spec)
 */

// ----------------------------------------------------------------------------

#define  main__is_pressed   is_pressed
#define  main__was_pressed  was_pressed
#define  main__row          row
#define  main__col          col

// ----------------------------------------------------------------------------

// --- for main() loop ---

static bool _pressed_1[OPT__KB__ROWS][OPT__KB__COLUMNS];
static bool _pressed_2[OPT__KB__ROWS][OPT__KB__COLUMNS];

bool (* is_pressed) [OPT__KB__ROWS][OPT__KB__COLUMNS] = &_pressed_1;
bool (* was_pressed) [OPT__KB__ROWS][OPT__KB__COLUMNS] = &_pressed_2;
uint8_t row;
uint8_t col;

// --- for `main__timer__` functions ---

typedef struct {
    list__node_t _private;
    uint16_t cycles;
    void(*function)(void);
} event_t;


static uint16_t       _cycles;
static list__list_t * _scheduled;


// ----------------------------------------------------------------------------
// --- main() loop ------------------------------------------------------------
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
    main__timer__init();

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

        // take care of `main__timer__` stuff
        _cycles++;

        for (event_t * event = _scheduled->head; event;) {
            if (event->cycles == 0) {
                (*event->function)();
                event = list__pop_node_next(_scheduled, event);
            } else {
                event->cycles--;
                event = event->_private.next;
            }
        }
    }

    return 0;
}


// ----------------------------------------------------------------------------
// --- `main__timer__` functions ----------------------------------------------
// ----------------------------------------------------------------------------

uint8_t main__timer__init(void) {
    _scheduled = list__new();
    if (!_scheduled) return 1;  // error

    return 0;  // success
}

uint16_t main__timer__cycles(void) {
    return _cycles;
}

uint8_t  main__timer__schedule(uint16_t cycles, void(*function)(void)) {
    if (!function) return 0;  // success: there is no function to add

    event_t * event = list__insert(_scheduled, -1, malloc(sizeof(event_t)));
    if (!event) return 1;  // error

    event->cycles   = cycles;
    event->function = function;

    return 0;  // success
}

