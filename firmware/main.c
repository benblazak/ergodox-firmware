/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * `main()`: tying it all together  // TODO
 */


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

void main(void) {
}

