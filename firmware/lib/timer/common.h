/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * A central place for all `#include`s and common definitions relevant to this
 * timer library
 *
 * Prefix: `_`
 */


#ifndef ERGODOX_FIRMWARE__LIB__TIMER__COMMON__H
#define ERGODOX_FIRMWARE__LIB__TIMER__COMMON__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "../../../firmware/lib/data-types/list.h"

// ----------------------------------------------------------------------------

typedef struct {
    list__node_t _private; // "subclass" `list__node_t`
    uint16_t     ticks;    // cycles or milliseconds
    void(*function)(void);
} _event_t;

// ----------------------------------------------------------------------------

uint16_t       _cycles;
list__list_t * _cycles_scheduled;
list__list_t * _cycles_to_schedule;
list__list_t * _cycles_to_schedule_lock;

volatile uint16_t _milliseconds;
list__list_t *    _milliseconds_scheduled;
list__list_t *    _milliseconds_to_schedule;
bool              _milliseconds_to_schedule_lock;

// ----------------------------------------------------------------------------

uint8_t _device__init (void);

uint8_t _event_list__append ( list__list_t * list,
                              uint16_t       ticks,
                              void(*function)(void) );
void    _event_list__update (list__list_t * list);
void    _event_list__move   (list__list_t * to, list__list_t * from);


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__LIB__TIMER__COMMON__H



// ============================================================================
// === Documentation ==========================================================
// ============================================================================


// ----------------------------------------------------------------------------
// typedefs -------------------------------------------------------------------
// ----------------------------------------------------------------------------

// === _event_t ===
/**                                               typedefs/_event_t/description
 * A struct to represent a scheduled event
 *
 * Members:
 * - `_private`: The C way of "subclassing" another type
 * - `ticks`: The number of cycles or milliseconds in which the given event
 *   should run
 * - `function`: A pointer to the function to run
 */


// ----------------------------------------------------------------------------
// variables ------------------------------------------------------------------
// ----------------------------------------------------------------------------

// === _cycles ===
/**                                               variables/_cycles/description
 * The number of scan cycles since the timer was initialized (mod 2^16)
 */

// === _cycles_scheduled ===
/**                                     variables/_cycles_scheduled/description
 * A list of scheduled events, to be run in a given number of cycles
 *
 * Meant to be used only by `timer___increment_cycles()` (after initialization)
 */

// === _cycles_to_schedule ===
//
/**                                   variables/_cycles_to_schedule/description
 * A list of events to schedule
 *
 * Meant to be used only by `timer__schedule_cycles()` and
 * `timer___increment_cycles()` (after initialization)
 *
 * `timer___increment_cycles()` will move the events in this list to
 * `_cycles_scheduled` the next time it runs and the latter list is not locked.
 *
 * The reason for having both `_cycles_scheduled` and `_cycles_to_schedule` is
 * that this allows us to only reference `_cycles_scheduled` from place, which
 * in turn allows us not to have to worry about whether that function will have
 * access to it when it runs.
 */

// === _cycles_to_schedule_lock ===
//
/**                        variables/_milliseconds_to_schedule_lock/description
 * A lock for `_milliseconds_to_schedule`
 *
 * To make sure that if `timer__schedule_milliseconds()` is interrupted by the
 * interrupt vector that may touch `_milliseconds_to_schedule`, the interrupt
 * leaves the variable alone until the function is done with it.
 */

// === _milliseconds ===
/**                                         variables/_milliseconds/description
 * The number of milliseconds since the timer was initialized (mod 2^16)
 */

// === _milliseconds_scheduled ===
/**                               variables/_milliseconds_scheduled/description
 * A list of scheduled events, to be run in a given number of milliseconds
 *
 * Meant to be used only in the interrupt vector responsible for updating
 * `_milliseconds` (after initialization)
 */

// === _milliseconds_to_schedule ===
/**                             variables/_milliseconds_to_schedule/description
 * A list of events to schedule
 *
 * Meant to be used only by `timer__schedule_milliseconds()` and the interrupt
 * vector that updates `_milliseconds` (after initialization)
 *
 * The responsible interrupt vector will move the events in this list to
 * `_milliseconds_scheduled` the next time it runs and the latter list is not
 * locked.
 *
 * The reason for having both `_milliseconds_scheduled` and
 * `_milliseconds_to_schedule` is that this way only the events that have not
 * yet been scheduled are effected if `timer__schedule_milliseconds()` is
 * interrupted by the interrupt vector.  In this case, time for these
 * unscheduled events will not start being counted until they are scheduled,
 * hopefully on the interrupt vector's next run.  If, on the other hand, there
 * were only one list and the function was interrupted, every event in the list
 * would be inaccessible to the interrupt vector, and we would not be able to
 * count time for *any* of them during that run.
 */

// === _milliseconds_to_schedule_lock ===
/**                        variables/_milliseconds_to_schedule_lock/description
 * A lock for `_milliseconds_to_schedule`
 *
 * To make sure that if `timer__schedule_milliseconds()` is interrupted by the
 * interrupt vector that may touch `_milliseconds_to_schedule`, the interrupt
 * leaves the variable alone until the function is done with it.
 */


// ----------------------------------------------------------------------------
// functions ------------------------------------------------------------------
// ----------------------------------------------------------------------------

// === _device__init() ===
/**                                         functions/_device__init/description
 * Initialize the device specific portions of the timer
 *
 * Meant to be called only by `timer__init()`
 *
 * Returns:
 * - success: `0`
 * - failure: [other]
 */

// === _event_list__append() ===
/**                                   functions/_event_list__append/description
 * Append an event with the given attributes to `list`
 *
 * Arguments:
 * - `list`: The list to add the new event to
 * - `ticks`: The number of ticks to assign to the event
 * - `function`: A pointer to the function to assign to the event
 *
 * Returns:
 * - success: `0`
 * - failure: [other]
 */

// === _event_list__update() ===
/**                                   functions/_event_list__update/description
 * Decrement the `ticks` of every event in `list` by `1`, and run any event
 * with `ticks == 0`
 *
 * Arguments:
 * - `list`: The list to update
 */

// === _event_list__move() ===
/**                                     functions/_event_list__move/description
 * Move all events in `from` to `to`, and clear `to`
 *
 * Arguments:
 * - `to`: The list into which to move all elements
 * - `from`: The list to move all elements from
 */

