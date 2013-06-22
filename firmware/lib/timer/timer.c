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
#include "../../../firmware/lib/data-types/list.h"
#include "./event-list.h"
#include "../timer.h"

// ----------------------------------------------------------------------------

#define  DEFINE_TIMER(name)                                                 \
    static uint16_t     _##name##__counter;                                 \
    static list__list_t _##name##__scheduled_events;                        \
                                                                            \
    uint16_t timer__get_##name(void) {                                      \
        return _##name##__counter;                                          \
    }                                                                       \
    uint8_t timer__schedule_##name(uint16_t ticks, void(*function)(void)) { \
        return event_list__append(                                          \
                &_##name##__scheduled_events, ticks, function );            \
    }                                                                       \
    void timer___tick_##name(void) {                                        \
        _##name##__counter++;                                               \
        event_list__tick(&_##name##__scheduled_events);                     \
    }

// ----------------------------------------------------------------------------

DEFINE_TIMER(cycles);
DEFINE_TIMER(keypresses);

