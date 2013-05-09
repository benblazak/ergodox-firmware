/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Timer interface
 *
 * Prefix: `timer__`
 */


#ifndef ERGODOX_FIRMWARE__LIB__TIMER__H
#define ERGODOX_FIRMWARE__LIB__TIMER__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


uint8_t  timer__init             (void);
uint16_t timer__get_milliseconds (void);

uint8_t  timer__schedule         ( uint16_t      milliseconds,
                                   void(*)(void) function );
// TODO: `timer__schedule()`, to schedule `function` to run in `milliseconds`
// - will need to be careful with this function, as everything called by it
//   will be executing within an interrupt vector.
// TODO: after this, should probably make a `main__schedule()`, to schedule
// `function` to run in `cycles` (or `scans`).  this will have the benefit of
// being lower resolution (while still high enough resolution for a lot of
// things; and perhaps exactly what other things call for).  Also, functions
// scheduled that way will not be executing from within an interrupt vector, so
// they could, within reason, do more or less what they want.


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__LIB__TIMER__H



// ============================================================================
// === documentation ==========================================================
// ============================================================================


// ----------------------------------------------------------------------------
// functions ------------------------------------------------------------------
// ----------------------------------------------------------------------------

// === timer__init() ===
/**                                           functions/timer__init/description
 * Initialize the timer
 *
 * Returns:
 * - success: `0`
 * - failure: [other]
 *
 * Notes:
 * - Should be called exactly once by `main()` before entering the run loop.
 */

// === timer__get_milliseconds() ===
/**                               functions/timer__get_milliseconds/description
 * Return the number of milliseconds since the timer was initialized (mod 2^16)
 *
 *     ---------------------------------------------------------------------
 *      number     highest value        in          in        in        in
 *      of bits    (milliseconds)     seconds     minutes    hours     days
 *     ---------  ----------------  -----------  ---------  --------  ------
 *           8                255          0.3        0.0       0.0     0.0
 *          16              65535         65.5        1.1       0.0     0.0
 *          32         4294967295    4294967.3    71582.8    1193.0    49.7
 *     ---------------------------------------------------------------------
 *
 *
 * Usage notes:
 *
 * - It's unnecessary to keep 16-bit resolution when storing the value returned
 *   by `timer__get_milliseconds()` if you don't need it.  Use variables of the
 *   smallest type that can (*always*) hold the amount of time you'll be
 *   dealing with.
 *
 * - Use `end_time - start_time` for determining time difference.  Since the
 *   returned values are unsigned (and you should be storing them in unsigned
 *   variables as well) this will work across overflows, for up to the maximum
 *   amount of milliseconds representable by the type you're using.  (See [this
 *   answer] (http://stackoverflow.com/a/50632) on <http://stackoverflow.com/>
 *   if you're curious as to why this workes across overflows.)
 *
 *
 * Warnings:
 *
 * - Do not cast the return value of `timer__get_milliseconds()` directly.
 *   Instead, store the return value in a smaller variable
 *
 *       uint8_t start_time = timer__get_milliseconds()
 *
 *   or cast the expression as a whole
 *
 *       (uint8_t)( timer__get_milliseconds() - start_time )
 *
 *   Casting directly within the end condition check of a `while` or `for` loop
 *   does not produce the desired behavior.  I don't know assembly well enough
 *   to figure out what it's *actually* doing, but the code generated is longer
 *   than when casting as shown, and it doesn't appear to be throwing away all
 *   but the least significant 8 bits before calculation, as I'd expect.
 *   Casting directly when assigning to a variable doesn't appear to do
 *   anything, and casting directly outside end condition checks seems to work
 *   at least sometimes, but those casts may as well be avoided for
 *   consistency.
 *
 * - Be careful when subtracting (or doing anything, really, with multiple)
 *   times, to make sure that if the values are not of the same type, the
 *   expression is cast to the smallest type you're using.  If `start_time` is
 *   a `uint8_t` value,
 *
 *       (uint8_t)( timer__get_milliseconds() - start_time )
 *
 *   has a very different meaning than
 *
 *       timer__get_milliseconds() - start_time
 *
 *   except within the first 255 milliseconds of the timer being initialized.
 */

