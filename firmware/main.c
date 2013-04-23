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
#include <util/delay.h>
#include "../firmware/keyboard.h"
#include "../firmware/lib/usb.h"
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

bool _pressed_1[OPT__KB__ROWS][OPT__KB__COLUMNS];
bool _pressed_2[OPT__KB__ROWS][OPT__KB__COLUMNS];

bool (* is_pressed) [OPT__KB__ROWS][OPT__KB__COLUMNS] = &_pressed_1;
bool (* was_pressed) [OPT__KB__ROWS][OPT__KB__COLUMNS] = &_pressed_2;
uint8_t row;
uint8_t col;

// ----------------------------------------------------------------------------

/**                                                  functions/main/description
 * Initialize things, then loop forever
 *
 * Mostly all that happens here after initialization is that current and
 * previous key states are tracked, keys that change state are "executed", the
 * USB report is sent, and the LEDs are updated.  We also have a delay, to make
 * sure we don't detect switch bounce from the keys.  Almost everything
 * interesting happens somewhere else (especially in
 * ".../firmware/keyboard/.../layout"); have a look through the source,
 * especially the documentation, to see how things are defined and what's
 * actually happening.
 */
int main(void) {
    static bool (*temp)[OPT__KB__ROWS][OPT__KB__COLUMNS]; // for swapping below
    static bool key_is_pressed;
    static bool key_was_pressed;

    kb__init();  // initialize hardware (besides USB)

    kb__led__state__power_on();

    usb__init();
    while (!usb__is_configured());
    kb__led__delay__usb_init();  // give the OS time to load drivers, etc.

    kb__led__state__ready();

    for(;;) {
        temp = is_pressed;
        is_pressed = was_pressed;
        was_pressed = temp;

        kb__update_matrix(*is_pressed);

        // "execute" keys that have changed state
        for(row=0; row<OPT__KB__ROWS; row++) {
            for(col=0; col<OPT__KB__COLUMNS; col++) {
                key_is_pressed = (*is_pressed)[row][col];
                key_was_pressed = (*was_pressed)[row][col];

                if (key_is_pressed != key_was_pressed)
                    kb__layout__exec_key(key_is_pressed, row, col);
            }
        }

        usb__kb__send_report();  // (even if nothing's changed)
        _delay_ms(OPT__DEBOUNCE_TIME);

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
    }

    return 0;
}

