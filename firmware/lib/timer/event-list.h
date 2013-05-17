/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Event-list interface, to handle lists of scheduled events
 *
 * Prefix: `event_list__`
 *
 * Meant to be used only within ".../firmware/lib/timer"
 *
 *
 * Usage notes:
 *
 * - A "tick" is an ill-defined unit of time.  It may represent any occurrence,
 *   even a randomly timed one; but it makes the most sense for it to count
 *   something that occurs predictably, like the passing of a millisecond, or
 *   the completion of a scan cycle.
 *
 * - To "tick" (as a verb) is to denote the passage of a "tick" of time by
 *   performing the actions corresponding thereto (i.e. incrementing the
 *   counter and running any scheduled events).
 *
 * - All functions declared here should be safe for use within interrupt
 *   routines, as long as you pay attention to the warnings below.
 *
 *
 * Warnings:
 *
 * - Any list passed as an argument to one of these functions must not be used
 *   *anywhere* except as an argument to one of these functions.
 */


#ifndef ERGODOX_FIRMWARE__LIB__TIMER__EVENT_LIST__H
#define ERGODOX_FIRMWARE__LIB__TIMER__EVENT_LIST__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


#include <stdint.h>
#include "../../../firmware/lib/data-types/list.h"

// ----------------------------------------------------------------------------

uint8_t event_list__append ( list__list_t * list,
                             uint16_t       ticks,
                             void(*function)(void) );
void    event_list__tick   (list__list_t * list);


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__LIB__TIMER__EVENT_LIST__H



// ============================================================================
// === Documentation ==========================================================
// ============================================================================


// ----------------------------------------------------------------------------
// functions ------------------------------------------------------------------
// ----------------------------------------------------------------------------

// === event_list__append() ===
/**                                    functions/event_list__append/description
 * Append an event with the given attributes to `list`
 *
 * Arguments:
 * - `list`: The list to add the new event to
 * - `ticks`: The number of ticks to assign to the event
 * - `function`: A function pointer to assign to the event
 *
 * Returns:
 * - success: `0`
 * - failure: [other]
 */

// === event_list__tick() ===
/**                                      functions/event_list__tick/description
 * Perform any actions that should occur every "tick", and run functions as
 * scheduled
 *
 * Arguments:
 * - `list`: The list to "tick"
 */

