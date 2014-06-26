/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Timer interface
 *
 * Prefixes: `timer__`, `timer___`
 *
 *
 * Usage notes:
 * - A "tick" is an ill-defined unit of time.  It may represent any occurrence,
 *   even a randomly timed one; but it makes the most sense for it to count
 *   something that occurs predictably, like the passing of a millisecond, or
 *   the completion of a scan cycle.
 *
 * - To "tick" (as a verb) is to denote the passage of a "tick" of time by
 *   performing the actions corresponding thereto (i.e. incrementing the
 *   counter and running any scheduled events).
 *
 * - A "timer" is a collection of related `...get...()`, `...schedule...()`,
 *   and `...tick...()` functions, all dealing with the same (private)
 *   variables.
 *
 * - Table, for milliseconds
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
 */


#ifndef ERGODOX_FIRMWARE__LIB__TIMER__H
#define ERGODOX_FIRMWARE__LIB__TIMER__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


uint8_t  timer__init             (void);

uint16_t timer__get_cycles       (void);
uint16_t timer__get_keypresses   (void);
uint16_t timer__get_milliseconds (void);

uint8_t  timer__schedule_cycles       (uint16_t ticks, void(*function)(void));
uint8_t  timer__schedule_keypresses   (uint16_t ticks, void(*function)(void));

// ----------------------------------------------------------------------------
// private

void timer___tick_cycles       (void);
void timer___tick_keypresses   (void);


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

// === (group) get...() ===
/**                                        functions/(group) get.../description
 * Return the number of "ticks" since the given timer was initialized
 * (mod 2^16)
 *
 * Members:
 * - `timer__get_cycles`: Counts the number of scan cycles
 * - `timer__get_keypresses`: Counts the number of applicable key presses
 * - `timer__get_milliseconds`: Counts real time milliseconds
 *
 * Returns:
 * - success: The number of "ticks" since the timer was initialized (mod 2^16)
 *
 *
 * Usage notes:
 *
 * - It's unnecessary to keep 16-bit resolution when storing the value returned
 *   by a get function if you don't need it.  Use variables of the smallest
 *   type that can (*always*) hold the amount of time you'll be dealing with.
 *
 * - Use `end_time - start_time` for determining time difference.  Since the
 *   returned values are unsigned (and you should be storing them in unsigned
 *   variables as well) this will work across overflows, for up to the maximum
 *   amount of ticks representable by the type you're using.  (See [this
 *   answer] (http://stackoverflow.com/a/50632) on <http://stackoverflow.com/>
 *   if you're curious as to why this works across overflows.)
 *
 *
 * Warnings:
 *
 * - Do not cast the return value of a get function directly.  Instead, store
 *   the return value in a smaller variable
 *
 *       uint8_t start_time = timer__get_cycles()
 *
 *   or cast the expression as a whole
 *
 *       (uint8_t)( timer__get_cycles() - start_time )
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
 *   except within the first 2^8 milliseconds of the timer being initialized.
 */

// === (group) schedule ===
/**                                      functions/(group) schedule/description
 * Schedule `function` to run in the given number of "ticks"
 *
 * Members:
 * - `timer__schedule_cycles`
 * - `timer__schedule_keypresses`
 *
 * Arguments:
 * - `ticks`: The number of ticks to wait
 * - `function`: A pointer to the function to run
 *
 * Returns:
 * - success: `0`
 * - failure: [other]
 *
 *
 * Usage notes:
 *
 * - If a function needs a longer wait time than is possible with a 16-bit
 *   resolution counter, it can repeatedly schedule itself to run in, say, 1
 *   minute (= 1000*60/5 cycles, assuming cycles take on average 5
 *   milliseconds) (using the cycles timer), increment a counter each time, and
 *   then only execute its body code after, say, 5 calls (for a 5 minute
 *   delay).
 */

// ----------------------------------------------------------------------------
// private

// === timer___tick_cycles() ===
/**                                   functions/timer___tick_cycles/description
 * Increment the counter for the number of cycles, and perform scheduled tasks
 *
 * Meant to be used only by `main()`
 */

// === timer___tick_keypresses() ===
/**                               functions/timer___tick_keypresses/description
 * Increment the counter for the number of key-presses, and perform scheduled
 * tasks
 *
 * Meant to be used only by `kb__layout__exec_key()`
 */

