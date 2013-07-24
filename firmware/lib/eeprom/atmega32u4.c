/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Implements the EEPROM interface defined in "../eeprom.h" for the ATMega32U4
 */


#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <util/atomic.h>
#include <avr/io.h>
#include "../../../firmware/lib/timer.h"
#include "../eeprom.h"

// ----------------------------------------------------------------------------
// macros ---------------------------------------------------------------------

/**                                               macros/MIN_UNUSED/description
 * The minimum number of elements to have unused after a resize (in any queue)
 */
#define  MIN_UNUSED  0

/**                                               macros/MAX_UNUSED/description
 * The maximum number of elements to have unused after a resize (in any queue)
 */
#define  MAX_UNUSED  4

/**                                            macros/(enum) action/description
 * Valid values for `write_t.action`, determining the type of action to perform
 * for an entry in `to_write`
 *
 * Members:
 * - `ACTION_WRITE`
 * - `ACTION_COPY`
 */
enum action {
    ACTION_WRITE,
    ACTION_COPY,
};

// ----------------------------------------------------------------------------
// types ----------------------------------------------------------------------

/**                                                   types/write_t/description
 * To hold values for a "write" to the EEPROM
 *
 * Struct members:
 * - `action`: A field indicating what type of action to perform.  Valid values
 *   defined by `enum action`
 * - `to`: The address in EEPROM memory space to write to
 * - `value`:
 *     - `action == ACTION_WRITE`: The data to write
 *     - `action == ACTION_COPY`: The number of bytes left to copy
 *
 * Implementation notes:
 * - Since the ATMega32U4 only has 1024 bytes of EEPROM, it's safe to restrict
 *   `to` to 10 bits.
 */
typedef struct {
    uint8_t  action :  6;
    uint16_t to     : 10;
    uint8_t  value;
} write_t;

/**                                                    types/copy_t/description
 * To hold the extra values needed for a "copy" to/from the EEPROM
 *
 * Struct members:
 * - `from`: The address in the EEPROM memory space to copy from
 */
typedef struct {
    uint16_t from;
} copy_t;

// ----------------------------------------------------------------------------
// variables ------------------------------------------------------------------

/**                                                variables/status/description
 * Flags for keeping track of the status of these functions (since write
 * operations will be buffered)
 *
 * Members:
 * - `writing`: Indicates that writes are queued and/or being performed
 *     - If this is `true`, `write_queued()` is either running or scheduled to
 *       run, and should not be rescheduled by any function other than itself.
 *     - If this is `false`, no writes are queued or being performed, and
 *       `write_queued()` must be scheduled to run externally before writes
 *       will commence.
 */
struct {
    bool writing : 1;
} status;

/**                                        variables/(group) queues/description
 * Members:
 * - `to_write`: To hold the write queue, and related metadata
 * - `to_copy`: To hold the extra data needed for copies, along with related
 *   metadata
 *
 * Struct members:
 * - `allocated`: The number of positions allocated
 * - `unused_front`: The number of unused positions at the beginning of the
 *   queue
 * - `unused_back`: The number of unused positions at the end of the queue
 * - `to_write.data`: A queue of writes (and copies) to perform
 * - `to_copy.data`: A queue of extra information for each `action ==
 *   ACTION_COPY` element in `to_write`
 *
 * Implementation notes:
 * - `unused_front` and `unused_back` each have a range of between -8 and 7,
 *   inclusive.  This means that, with the current scheme, `MAX_UNUSED` must
 *   not be greater than 7.  Note that negative values for either only make
 *   sense temporarily, when adding an element to the queue.
 */
static struct {
    uint8_t   allocated;
    int8_t    unused_front : 4;
    int8_t    unused_back  : 4;
    write_t * data;
} to_write;
static struct {
    uint8_t  allocated;
    int8_t   unused_front : 4;
    int8_t   unused_back  : 4;
    copy_t * data;
} to_copy;

// ----------------------------------------------------------------------------
// variable manipulator functions ---------------------------------------------

/**                                        functions/(group) resize/description
 * Resize the appropriate queue, so that the number of unused elements is
 * between `MIN_UNUSED` and `MAX_UNUSED`, inclusive
 *
 * Returns:
 * - success: `0`
 * - failure: [other]
 *
 * Notes:
 * - These functions are separate (though identical in source, before macro
 *   expansion) partly because this allows us to deal with elements of the
 *   queue as discrete blocks of memory.  It might not be hard to make the
 *   function generic, but then we would loose the ability to depend on type
 *   information, and have to operate on each `queue.data` solely as an array
 *   of bytes.  It's a close call, but I feel like the conceptual clarity we
 *   gain with this method outweighs the clarity we would gain by having only a
 *   single function, with no copy+pasted code.
 *
 * Implementation notes:
 * - We use a signed type for `unused` in case `unused_front + unused_back`
 *   turns out to be negative, as may happen when adding a new element to the
 *   queue.
 * - The only time `realloc()` should fail is if we are trying to grow the
 *   queue.  See [the documentation]
 *   (http://www.nongnu.org/avr-libc/user-manual/malloc.html)
 *   for `malloc()` in avr-libc.
 */
static uint8_t resize_to_write(void) {
    #define  queue            to_write
    #define  queue_type_size  (sizeof(write_t))

    int8_t unused = queue.unused_front + queue.unused_back;

    if (MIN_UNUSED <= queue.unused_back && unused <= MAX_UNUSED)
        return 0;  // no need to grow, shrink, or shift the queue

    // shift down (if necessary), and update metadata
    // - start with the first used element, and copy it down to index 0
    // - copy the second used element down to index 1, and so on until we copy
    //   the last used element
    // - if there are no empty elements at the front of the queue, this will do
    //   nothing
    if (queue.unused_front != 0) {
        for (uint8_t i = queue.unused_front; i < queue.allocated - unused; i++)
            queue.data[i-queue.unused_front] = queue.data[i];

        queue.unused_front = 0;
        queue.unused_back = unused;

        if (MIN_UNUSED <= unused && unused <= MAX_UNUSED)
            return 0;  // no need to grow or shrink the queue
    }

    uint8_t new_allocated;
    if (UINT8_MAX >= queue.allocated - unused + (MIN_UNUSED+MAX_UNUSED)/2)
        new_allocated = queue.allocated - unused + (MIN_UNUSED+MAX_UNUSED)/2;
    else if (UINT8_MAX >= queue.allocated - unused + MIN_UNUSED)
        new_allocated = UINT8_MAX;
    else
        return 1;  // unable to count the required number of elements

    void * new_data = realloc( queue.data, queue_type_size * new_allocated );
    if (!new_data)
        return 1;  // error: `realloc()` failed (unable to grow queue)

    queue.unused_back += new_allocated - queue.allocated;
    queue.allocated = new_allocated;
    queue.data = new_data;

    return 0;  // success: queue reallocated

    #undef  queue
    #undef  queue_type_size
}
static uint8_t resize_to_copy(void) {
    #define  queue            to_copy
    #define  queue_type_size  (sizeof(copy_t))

    int8_t unused = queue.unused_front + queue.unused_back;

    if (MIN_UNUSED <= queue.unused_back && unused <= MAX_UNUSED)
        return 0;  // no need to grow, shrink, or shift the queue

    // shift down (if necessary), and update metadata
    // - start with the first used element, and copy it down to index 0
    // - copy the second used element down to index 1, and so on until we copy
    //   the last used element
    // - if there are no empty elements at the front of the queue, this will do
    //   nothing
    if (queue.unused_front != 0) {
        for (uint8_t i = queue.unused_front; i < queue.allocated - unused; i++)
            queue.data[i-queue.unused_front] = queue.data[i];

        queue.unused_front = 0;
        queue.unused_back = unused;

        if (MIN_UNUSED <= unused && unused <= MAX_UNUSED)
            return 0;  // no need to grow or shrink the queue
    }

    uint8_t new_allocated;
    if (UINT8_MAX >= queue.allocated - unused + (MIN_UNUSED+MAX_UNUSED)/2)
        new_allocated = queue.allocated - unused + (MIN_UNUSED+MAX_UNUSED)/2;
    else if (UINT8_MAX >= queue.allocated - unused + MIN_UNUSED)
        new_allocated = UINT8_MAX;
    else
        return 1;  // unable to count the required number of elements

    void * new_data = realloc( queue.data, queue_type_size * new_allocated );
    if (!new_data)
        return 1;  // error: `realloc()` failed (unable to grow queue)

    queue.unused_back += new_allocated - queue.allocated;
    queue.allocated = new_allocated;
    queue.data = new_data;

    return 0;  // success: queue reallocated

    #undef  queue
    #undef  queue_type_size
}

/**                                           functions/(group) pop/description
 * Remove the first element from the appropriate queue
 *
 * Members:
 * - `pop_to_write`: operates on the `to_write` queue
 * - `pop_to_copy`: operates on the `to_copy` queue
 */
static void pop_to_write(void) {
    to_write.unused_front++;
    resize_to_write();
}
static void pop_to_copy(void) {
    to_copy.unused_front++;
    resize_to_copy();
}

// ----------------------------------------------------------------------------
// back end functions ---------------------------------------------------------

/**                                                 functions/write/description
 * Write `data` to `address` in EEPROM memory space as soon as possible
 *
 * Arguments:
 * - `to: The address of the location to write to
 * - `data`: The data to write
 *
 * Notes:
 * - This function is static (and `eeprom__write()`, the public function, is
 *   written below) because writes are really slow, and we're going to buffer
 *   them.
 *
 * Implementation notes:
 * - This function (and most of the comments) were taken more or less straight
 *   from the data sheet, section 5.3
 * - If another write is in progress when this function is called, this
 *   function will busy wait until the first write has been completed.  This
 *   may take quite some time (up to 3.4 ms if a write has just been started),
 *   so we must be careful about when this function is called.
 * - This function starts the write to the EEPROM, but returns long before it
 *   has been completed.
 *
 * Assumptions:
 * - The address passed as `to` is valid.
 * - Voltage will never fall below the specified minimum for the clock
 *   frequency being used.
 * - A write to flash memory (PROGMEM) will never be in progress when this
 *   function is called.
 */
static void write(uint16_t to, uint8_t data) {

    // - if a write is in progress, this will also wait until it's finished
    uint8_t old_data = eeprom__read( (uint8_t *) to );

    if (data == old_data) {
        // do nothing
        return;
    } else if (data == 0xFF) {
        // erase only (1.8 ms)
        EECR &= ~(1<<EEPM1);  // clear
        EECR |=  (1<<EEPM0);  // set
    } else if (old_data == 0xFF) {
        // write only (1.8 ms)
        EECR |=  (1<<EEPM1);  // set
        EECR &= ~(1<<EEPM0);  // clear
    } else {
        // erase and write in one (atomic) operation (3.4 ms)
        EECR &= ~(1<<EEPM1);  // clear
        EECR &= ~(1<<EEPM0);  // clear
    }

    EEAR = to;    // set up address register
    EEDR = data;  // set up data register

    // - interrupts must be disabled between these two operations, or else
    //   "EEPROM Master Programming Enable" may time out (since it's cleared by
    //   hardware 4 clock cycles after being written to `1` by software)
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        EECR |= (1<<EEMPE);  // set "EEPROM Master Programming Enable" to `1`
        EECR |= (1<<EEPE);   // start EEPROM write (then halt, 2 clock cycles)
    }
}

/**                                          functions/write_queued/description
 * Write (or copy) the next byte of data as dictated by our queue(s), and
 * schedule the write of the next byte if necessary
 */
static void write_queued(void) {
    #define  next_write     ( to_write.data[to_write.unused_front] )
    #define  next_copy      ( to_copy.data[to_copy.unused_front] )
    #define  length(queue)  ( queue.allocated       \
                              - queue.unused_front  \
                              - queue.unused_back )

    // if there's nothing to write
    // - checking for this here (instead of after writing) will cause this
    //   function to be called an extra time before it stops rescheduling
    //   itself; but it also allows us not to make assumptions about the state
    //   of `to_write` when this function is called
    if ( length(to_write) == 0 ) {
        status.writing = 0;
        return;
    }

    if (next_write.action == ACTION_WRITE) {

        // write 1 byte
        write( next_write.to, next_write.value );
        // prepare for the next
        pop_to_write();

    } else if ( next_write.action == ACTION_COPY && length(to_copy) ) {

        // if we're done with the current copy
        // - checking for this here requires an extra iteration between a copy
        //   being finished and the next operation being started; but it also
        //   allows us not to make assumptions about the state of `to_copy`
        //   when this function is called
        if (next_write.value == 0) {
            pop_to_write();
            pop_to_copy();
        }

        // copy 1 byte
        write( next_write.to, eeprom__read( (uint8_t *) next_copy.from ) );
        // prepare for the next
        ++(next_write.to);
        ++(next_copy.from);
        --(next_write.value);

    } else {
        // if we get here, there was an invalid node: remove it
        pop_to_write();
    }

    // - `(3.5/OPT__DEBOUNCE_TIME)+1` gives us the number of cycles we need to
    //   wait until the next write, where `3.5` is the maximum number of
    //   milliseconds an EEPROM write can take, and `OPT__DEBOUNCE_TIME` is the
    //   minimum number of milliseconds a scan can take.  Note that if the
    //   division produces an integer (other than by truncation), the `+1` is
    //   strictly unnecessary, since no truncation will be performed; but if
    //   we're that close to needing to wait an extra cycle we may as well wait
    //   anyway, just to be safe.
    timer__schedule_cycles( (3.5/OPT__DEBOUNCE_TIME)+1, &write_queued );

    #undef  next_write
    #undef  next_copy
    #undef  length
}

// ----------------------------------------------------------------------------
// front end functions --------------------------------------------------------

/**                                          functions/eeprom__read/description
 * Implementation notes:
 * - This function (and most of the comments) were taken more or less straight
 *   from the data sheet, section 5.3
 * - If a write is in progress when this function is called, this function will
 *   busy wait until the write has been completed.  This may take quite some
 *   time (up to 3.4 ms if a write has just been started), so you should be
 *   careful about when this function is called.
 *
 * Assumptions:
 * - The address passed as `address` is valid.
 */
uint8_t eeprom__read(uint8_t * from) {
  while (EECR & (1<<EEPE));  // wait for previous write to complete
  EEAR = (uint16_t) from;    // set up address register
  EECR |= (1<<EERE);         // start EEPROM read (then halt, 4 clock cycles)
  return EEDR;               // return the value in the data register
}

// note: this should be the only function adding elements to `to_write`
uint8_t eeprom__write(uint8_t * address, uint8_t data) {
    to_write.unused_back--;
    if (resize_to_write()) {
        to_write.unused_back++;
        return 1;  // resize failed
    }

    uint8_t index = to_write.allocated - to_write.unused_back - 1;
    to_write.data[index].action = ACTION_WRITE;
    to_write.data[index].to     = (uint16_t) address;
    to_write.data[index].value  = data;

    if (!status.writing) {
        timer__schedule_cycles( 0, &write_queued );
        status.writing = true;
    }

    return 0;  // success
}

// note: this should be the only function adding elements to `to_copy`
uint8_t eeprom__copy(uint8_t * to, uint8_t * from, uint8_t length) {
    to_write.unused_back--;
    to_copy.unused_back--;
    if (resize_to_write() || resize_to_copy()) {
        to_write.unused_back++; resize_to_write();
        to_copy.unused_back++;  resize_to_copy();
        return 1;  // resize failed
    }

    uint8_t index;

    index = to_write.allocated - to_write.unused_back - 1;
    to_write.data[index].action = ACTION_COPY;
    to_write.data[index].to     = (uint16_t) to;
    to_write.data[index].value  = length;

    index = to_copy.allocated - to_copy.unused_back - 1;
    to_copy.data[index].from = (uint16_t) from;

    if (!status.writing) {
        timer__schedule_cycles( 0, &write_queued );
        status.writing = true;
    }

    return 0;  // success
}

