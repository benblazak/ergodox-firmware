/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Implements the non device specific functionality of
 * ".../firmware/lib/timer", and all the functions defined in "./common.h"
 */


#include "./common.h"

// ----------------------------------------------------------------------------

uint8_t timer__init(void) {
    _cycles_scheduled         = list__new();
    _milliseconds_scheduled   = list__new();
    _milliseconds_to_schedule = list__new();

    if ( !_cycles_scheduled ||
         !_milliseconds_scheduled ||
         !_milliseconds_to_schedule ) {

        list__free(_cycles_scheduled);
        list__free(_milliseconds_scheduled);
        list__free(_milliseconds_to_schedule);

        return 1;  // error
    }

    return _device__init();
}

uint16_t timer__get_cycles(void) {
    return _cycles;
}

uint16_t timer__get_milliseconds(void) {
    return _milliseconds;
}

uint8_t timer__schedule_cycles(uint16_t cycles, void(*function)(void)) {
    // - there is the possibility that this function could be called by an
    //   event executing within an interrupt vector.  if that happens, and the
    //   interrupt originally interrupted this same function, it wouldn't be
    //   safe to operate on `_cycles_scheduled`
    if (lock) return 1;  // error
    lock = true;

    uint8_t ret = _event_list__append(_cycles_scheduled, cycles, function);

    lock = false;
    return ret;
}

uint8_t timer__schedule_milliseconds( uint16_t milliseconds,
                                      void(*function)(void) ) {
    // - even though the only other place `...to_schedule` should be referenced
    //   is within an interrupt vector (which this function can't interrupt),
    //   we have to be careful: what if this function is interrupted, and an
    //   event executes that calls this function?  this function would
    //   essentially be interrupting itself.  we must avoid that.
    if (_milliseconds_to_schedule_lock) return 1;  // error
    _milliseconds_to_schedule_lock = true;

    uint8_t ret = _event_list__append( _milliseconds_to_schedule,
                                       milliseconds,
                                       function );

    _milliseconds_to_schedule_lock = false;
    return ret;
}

// ----------------------------------------------------------------------------

void timer___increment_cycles (void) {
        _cycles++;
        _event_list__update(_cycles_scheduled);
}

// ----------------------------------------------------------------------------

uint8_t _event_list__append( list__list_t * list,
                             uint16_t       ticks,
                             void(*function)(void) ) {
    if (!function) return 0;  // success: there is no function to add

    _event_t * event = list__insert(list, -1, malloc(sizeof(_event_t)) );
    if (!event) return 1;  // error

    event->ticks    = ticks;
    event->function = function;

    return 0;  // success
}

void _event_list__update(list__list_t * list) {
    for (_event_t * event = list->head; event;) {
        if (event->ticks == 0) {
            (*event->function)();
            event = list__pop_node_next(list, event);
        } else {
            event->ticks--;
            event = event->_private.next;
        }
    }
}

void _event_list__move(list__list_t * to, list__list_t * from) {
    if (from->length == 0) return;  // nothing to move

    ((_event_t *)to->tail)->_private.next  = from->head;
    to->tail                 = from->tail;
    to->length              += from->length;

    from->head = NULL;
    from->tail = NULL;
    from->length = 0;
}

