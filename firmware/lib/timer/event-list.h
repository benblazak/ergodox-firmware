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
 * Meant to be used within ".../firmware/lib/timer"
 *
 * Warnings:
 * - These functions are not safe for use within interrupt vectors.  Just in
 *   case you were tempted to try :)
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
 *
 * Implementation notes:
 * - In the case that more than one function is scheduled to run on a given
 *   "tick", the functions should be run in the order in which they were
 *   scheduled.
 */

