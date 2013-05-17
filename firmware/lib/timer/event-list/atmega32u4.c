/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Implements the event-list interface defined in "../event-list.h" for the
 * ATMega32U4
 *
 * Notes:
 * - The code should be the same for anything in the AVR family.  It's the
 *   `<util/atomic>` macros that make this non-universal.
 */


#include <stdint.h>
#include <stdlib.h>
#include <util/atomic.h>
#include "../../../../firmware/lib/data-types/list.h"

// ----------------------------------------------------------------------------

typedef struct {
    list__node_t _private;  // "subclass" `list__node_t`
    uint16_t     ticks;     // our unit of time
    void(*function)(void);
} event_t;

// ----------------------------------------------------------------------------

uint8_t event_list__append( list__list_t * list,
                            uint16_t       ticks,
                            void(*function)(void) ) {
    if (!function || !list) return 0;  // success: nothing to do

    event_t * event = malloc(sizeof(event_t));
    if (!event) return 1;  // error

    event->ticks    = ticks;
    event->function = function;

    ATOMIC_BLOCK( ATOMIC_RESTORESTATE ) {
        list__insert(list, -1, event);
    }

    return 0;  // success
}

void event_list__tick(list__list_t * list) {
    if (!list) return;

    event_t * next;
    event_t * run = NULL;  // for keeping track of events to run

    // go through the list
    // - keep track of the events that need to be run this "tick"
    // - note that every other event is one "tick" closer to being run
    ATOMIC_BLOCK( ATOMIC_RESTORESTATE ) {
        for (event_t * event = list->head; event;) {
            if (event->ticks == 0) {
                next = event->_private.next;
                list__pop_node(list, event);
                event->_private.next = run;
                run = event;
                event = next;
            } else {
                event->ticks--;
                event = event->_private.next;
            }
        }
    }

    // run all the scheduled events, with interrupts enabled
    NONATOMIC_BLOCK( NONATOMIC_RESTORESTATE ) {
        while (run) {
            next = run->_private.next;
            (*run->function)();
            free(run);
            run = next;
        }
    }
}

