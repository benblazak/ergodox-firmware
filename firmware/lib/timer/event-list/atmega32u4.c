/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Implements the event-list interface defined in "../event-list.h" for the
 * ATMega32U4 (though, the code should be the same for anything in the AVR
 * family)
 */


#include <stdint.h>
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

    ATOMIC_BLOCK( ATOMIC_RESTORESTATE ) {
        for (event_t * event = list->head; event;) {
            if (event->ticks == 0) {
                NONATOMIC_BLOCK( NONATOMIC_RESTORESTATE ) {
                    (*event->function)();
                }
                event = list__pop_node_next(list, event);
            } else {
                event->ticks--;
                event = event->_private.next;
            }
        }
    }
}

