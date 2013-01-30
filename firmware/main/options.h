/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * `main()` options
 *
 * Prefix: `OPT__`
 *
 * This file is meant to be included by the using '.../options.h'
 */


#ifndef ERGODOX_FIRMWARE__FIRMWARE__MAIN__OPTIONS__H
#define ERGODOX_FIRMWARE__FIRMWARE__MAIN__OPTIONS__H
// ----------------------------------------------------------------------------
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
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__FIRMWARE__MAIN__OPTIONS__H

