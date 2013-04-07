/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * The `main()` interface for the rest of the program
 *
 * Prefix: `main__`
 *
 * Certain variables are declared here so that other functions can see (and
 * perhaps modify) them, to accomplish things that may be difficult otherwise.
 * If, for instance, a key-function needed to be called on every scan while
 * they key was pressed instead of just on state-change: it could set its entry
 * in `main__was_pressed` to `false` on every run.
 */


#ifndef ERGODOX_FIRMWARE__FIRMWARE__MAIN__H
#define ERGODOX_FIRMWARE__FIRMWARE__MAIN__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


#include <stdbool.h>
#include <stdint.h>

// ----------------------------------------------------------------------------

/**                                      variables/main__is_pressed/description
 * A matrix of `bool`s indicating whether the key at a given position is
 * currently pressed
 */
extern bool (* main__is_pressed) [OPT__KB__ROWS][OPT__KB__COLUMNS];

/**                                     variables/main__was_pressed/description
 * A matrix of `bool`s indicating whether the key at a given position was
 * pressed on the previous scan
 */
extern bool (* main__was_pressed) [OPT__KB__ROWS][OPT__KB__COLUMNS];

/**                                             variables/main__row/description
 * Indicates which row is currently being tested for changes of key state
 */
extern uint8_t main__row;

/**                                             variables/main__col/description
 * Indicates which column is currently being tested for changes of key state
 */
extern uint8_t main__col;


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__FIRMWARE__MAIN__H

