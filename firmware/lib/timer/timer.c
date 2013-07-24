/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Implements the device agnostic portion of the timer interface defined in
 * ".../firmware/lib/timer.h"
 */


#include <stdint.h>
#include <stdlib.h>
#include "../timer.h"

// ----------------------------------------------------------------------------
// macros ---------------------------------------------------------------------

/**                                               macros/MIN_UNUSED/description
 * The minimum number of elements to have unused after a resize
 */
#define  MIN_UNUSED  0

/**                                               macros/MAX_UNUSED/description
 * The maximum number of elements to have unused after a resize
 */
#define  MAX_UNUSED  4

// ----------------------------------------------------------------------------
// types ----------------------------------------------------------------------

/**                                                   types/event_t/description
 * To hold an event that should be run at some point in the future
 *
 * Struct members:
 * - `ticks`: The number of units of time to wait until running this event
 * - `function`: The event (the function to run)
 */
typedef struct {
    uint16_t ticks;
    void (*function)(void);
} event_t;

/**                                                    types/list_t/description
 * To hold a list of events, with corresponding metadata
 *
 * Struct members:
 * - `allocated`: The number of positions allocated
 * - `filled`: The number of positions filled
 * - `data`: A list of events to run at some point in the future
 */
typedef struct {
    uint8_t   allocated;
    uint8_t   filled;
    event_t * data;
} list_t;

/**                                                   types/timer_t/description
 * To hold all the variables needed by a timer
 *
 * Struct members:
 * - `counter`: How many "ticks" of this timer have occurred since it was
 *   initialized (mod 2^16)
 * - `scheduled`: The list of events to be eventually run by this timer, with
 *   corresponding metadata
 *
 */
typedef struct {
    uint16_t counter;
    list_t   scheduled;
} timer_t;

// ----------------------------------------------------------------------------
// variable manipulator functions ---------------------------------------------

/**                                                functions/resize/description
 * Resize `list->data`, so that the number of unused elements is between
 * `MIN_UNUSED` and `MAX_UNUSED`, inclusive
 *
 * Arguments:
 * - `list`: A pointer to the list to operate on
 *
 * Returns:
 * - success: `0`
 * - failure: [other]
 *
 * Implementation notes:
 * - We use a signed type for `unused` in case `filled` is greater than
 *   `allocated`, as may happen when appending a new event.  This number should
 *   normally be much smaller than either `filled` or `allocated`, so there is
 *   no need to worry about using a signed type (with a smaller maximum value)
 *   rather than an unsigned one.
 * - The only time `realloc()` should fail is if we are trying to grow the
 *   stack.  See [the documentation]
 *   (http://www.nongnu.org/avr-libc/user-manual/malloc.html)
 *   for `malloc()` in avr-libc.
 */
static uint8_t resize(list_t * list) {
    int8_t unused = list->allocated - list->filled;

    if (MIN_UNUSED <= unused && unused <= MAX_UNUSED)
        return 0;  // nothing to do

    uint8_t new_allocated;
    if (UINT8_MAX >= list->filled + (MIN_UNUSED+MAX_UNUSED)/2)
        new_allocated = list->filled + (MIN_UNUSED+MAX_UNUSED)/2;
    else if (UINT8_MAX >= list->filled + MIN_UNUSED)
        new_allocated = UINT8_MAX;
    else
        return 1;  // unable to count the required number of elements

    void * new_data = realloc( list->data, sizeof(event_t) * new_allocated );
    if (!new_data)
        return 1;  // error: `realloc()` failed (unable to grow list)

    list->allocated = new_allocated;
    list->data = new_data;

    return 0;  // success
}

/**                                                functions/append/description
 * Append a new event containing the passed information to `list->data`
 *
 * Arguments:
 * - `list`: A pointer to the list to operate on
 * - `ticks`: The value to put into the event's corresponding field
 * - `function`: The value to put into the event's corresponding field
 *
 * Returns:
 * - success: `0`
 * - failure: [other]
 */
static uint8_t append(list_t * list, uint16_t ticks, void(*function)(void)) {
    if (!function)
        return 0;  // nothing to do

    if (list->filled == UINT8_MAX)
        return 1;  // error: list already full
    list->filled++;
    if(resize(list)) {
        list->filled--;
        return 1;  // resize failed
    }

    list->data[list->filled - 1].ticks    = ticks;
    list->data[list->filled - 1].function = function;

    return 0;  // success
}

/**                                                    function/pop/description
 * Remove the event at `index` from `list->data`
 *
 * Arguments:
 * - `list`: A pointer to the list to operate on
 * - `index`: The index of the event to pop
 */
static void pop(list_t * list, uint8_t index) {
    // shift down
    // - start with the element at `index`, and copy the element above it down
    // - continue until we copy the top element (which will then be duplicated
    //   at indices `list->filled - 2` and `list->filled - 1`)
    // - if the top element is at `index` (or `index` is out of bounds), this
    //   will do nothing
    for (uint8_t i = index; i < list->filled - 1; i++)
        list->data[i] = list->data[i+1];

    // remove an element
    list->filled--;
    resize(list);  // we're shrinking the list, so this should never fail
}

// ----------------------------------------------------------------------------
// variables ------------------------------------------------------------------

static timer_t cycles;
static timer_t keypresses;

// ----------------------------------------------------------------------------
// front end functions --------------------------------------------------------

uint16_t timer__get_cycles(void) {
    return cycles.counter;
}

uint16_t timer__get_keypresses(void) {
    return keypresses.counter;
}

uint8_t timer__schedule_cycles(uint16_t ticks, void(*function)(void)) {
    return append(&cycles.scheduled, ticks, function);
}

uint8_t timer__schedule_keypresses(uint16_t ticks, void(*function)(void)) {
    return append(&keypresses.scheduled, ticks, function);
}

void timer___tick_cycles(void) {
    cycles.counter++;
    for (uint8_t i = 0; i < cycles.scheduled.filled; i++) {
        if (cycles.scheduled.data[i].ticks == 0) {
            (*cycles.scheduled.data[i].function)();
            pop(&cycles.scheduled, i);
        } else {
            cycles.scheduled.data[i].ticks--;
        }
    }
}

void timer___tick_keypresses(void) {
    keypresses.counter++;
    for (uint8_t i = 0; i < keypresses.scheduled.filled; i++) {
        if (keypresses.scheduled.data[i].ticks == 0) {
            (*keypresses.scheduled.data[i].function)();
            pop(&keypresses.scheduled, i);
        } else {
            keypresses.scheduled.data[i].ticks--;
        }
    }
}

