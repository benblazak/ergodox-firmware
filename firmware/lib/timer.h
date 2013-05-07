/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Timer interface
 *
 * Prefix: `timer__`
 *
 * `timer__init()` is meant to be called once, on startup, by `main()`
 */


#ifndef ERGODOX_FIRMWARE__LIB__TIMER__H
#define ERGODOX_FIRMWARE__LIB__TIMER__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


void timer__init(void);
/**                                           functions/timer__init/description
 * Initialize the timer
 */

uint32_t timer__get_milliseconds(void);
/**                               functions/timer__get_milliseconds/description
 * Return the number of milliseconds since the timer was initialized (mod 2^32)
 *
 * Usage notes:
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


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__LIB__TIMER__H

