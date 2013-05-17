/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Timer interface
 *
 * Prefixes: `timer__`, `timer___`
 */


#ifndef ERGODOX_FIRMWARE__LIB__TIMER__H
#define ERGODOX_FIRMWARE__LIB__TIMER__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


uint8_t  timer__init             (void);

uint16_t timer__get_cycles       (void);
uint16_t timer__get_milliseconds (void);

uint8_t  timer__schedule__cycles       ( uint16_t cycles,
                                         void(*function)(void) );
uint8_t  timer__schedule__milliseconds ( uint16_t milliseconds,
                                         void(*function)(void) );

// ----------------------------------------------------------------------------
// private

void timer___increment_cycles (void);


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

// === timer__get_cycles() ===
/**                                     functions/timer__get_cycles/description
 * Return the number of cycles since the timer was initialized (mod 2^16)
 *
 * Returns:
 * - success: The number of cycles since the timer was initialized (mod 2^16)
 *
 * Usage notes:
 * - See the documentation for `timer__get_milliseconds()`
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
 *     note: 32-bit values given for reference only
 *
 *
 * Returns:
 * - success: The number of milliseconds since the timer was initialized (mod
 *   2^16)
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

// === timer__schedule__cycles() ===
/**                               functions/timer__schedule__cycles/description
 * Schedule `function` to run in the given number of cycles
 *
 * Arguments:
 * - `cycles`: The number of cycles to wait
 * - `function`: A pointer to the function to run
 *
 * Returns:
 * - success: `0`
 * - failure: [other]
 *
 * Usage notes:
 * - If possible, prefer scheduling using this function over scheduling using
 *   `timer__schedule__milliseconds()`.  Functions run by this scheduler don't
 *   have to be quite as careful about finishing quickly, repeating too soon,
 *   or modifying shared variables, since they will not be executing inside an
 *   interrupt vector.
 */

// === timer__schedule__milliseconds() ===
/**                         functions/timer__schedule__milliseconds/description
 * Schedule `function` to run in the given number of milliseconds
 *
 * Arguments:
 * - `milliseconds`: The number of milliseconds to wait
 * - `function`: A pointer to the function to run
 *
 * Returns:
 * - success: `0`
 * - failure: [other]
 *
 * Warnings:
 * - Be careful when scheduling using this function.  Keep in mind that the
 *   function that is scheduled will be run within an interrupt vector.
 *
 * Usage notes:
 * - If a function needs a longer wait time than is possible with a 16-bit
 *   millisecond resolution counter, it can repeatedly schedule itself to run
 *   in, say, 1 minute (= 1000*60 milliseconds), increment a counter each time,
 *   and then only execute its body code after, say, 5 calls (for a 5 minute
 *   delay).
 */

// ----------------------------------------------------------------------------
// private

// === timer___increment_cycles() ===
/**                              functions/timer___increment_cycles/description
 * Increment the counter for the number of cycles, and perform scheduled tasks
 *
 * Meant to be used only by `main()`
 *
 * Notes:
 * - The corresponding real-time function (dealing with milliseconds instead of
 *   cycles) will be in an interrupt vector, and not explicitly called anywhere
 *   in the code.
 */

