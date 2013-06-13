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
#include "../../../firmware/lib/data-types/list.h"
#include "../../../firmware/lib/timer.h"
#include "../eeprom.h"

// ----------------------------------------------------------------------------

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
    list__node_t _super;
    uint8_t  action :  6;
    uint16_t to     : 10;  // since we only have 1024 bytes
    uint8_t  value;
} write_t;

/**                                                    types/copy_t/description
 * To hold the extra values needed for a "copy" to/from the EEPROM
 *
 * Struct members:
 * - `from`: The address in the EEPROM memory space to copy from
 */
typedef struct {
    list__node_t _super;
    uint16_t from;
} copy_t;

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

/**                                              variables/to_write/description
 * A list of writes (and copies) to perform
 */
static list__list_t to_write;

/**                                               variables/to_copy/description
 * A list of extra information for each `action == ACTION_COPY` element in
 * `to_write`
 */
static list__list_t to_copy;

// ----------------------------------------------------------------------------

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
    #define  next_write  ((write_t *) to_write.head)
    #define  next_copy   ((copy_t *) to_copy.head)

    // if there's nothing to write
    // - checking for this here will cause this function to be called an extra
    //   time before it stops rescheduling itself; but it also allows us not to
    //   make assumptions about the state of `to_write` when this function is
    //   called
    if (to_write.length == 0) {
        status.writing = 0;
        return;
    }

    if (next_write->action == ACTION_WRITE) {

        // write 1 byte
        write( next_write->to, next_write->value );
        // prepare for the next
        free( list__pop_index(&to_write, 0) );

    } else if (next_write->action == ACTION_COPY && to_copy.length) {

        // if we're done with the current copy
        // - checking for this here requires an extra iteration between a copy
        //   being finished and the next operation being started; but it also
        //   allows us not to make assumptions about the state of `to_copy`
        //   when this function is called
        if (next_write->value == 0) {
            free( list__pop_index(&to_write, 0) );
            free( list__pop_index(&to_copy, 0) );
        }

        // copy 1 byte
        write( next_write->to, eeprom__read( (uint8_t *) next_copy->from ) );
        // prepare for the next
        ++(next_write->to);
        ++(next_copy->from);
        --(next_write->value);

    } else {
        // if we get here, there was an invalid node: remove it
        free( list__pop_index(&to_write, 0) );
    }

    // - `(3.5/OPT__DEBOUNCE_TIME)+1` gives us the number of cycles we need to
    //   wait until the next write, where `3.5` is the maximum number of
    //   milliseconds an EEPROM write can take, and `OPT__DEBOUNCE_TIME` is the
    //   minimum number of milliseconds a scan can take.  Note that if the
    //   division produces an integer, the `+1` is strictly unnecessary, since
    //   no truncation will be performed; but if we're that close to needing to
    //   wait an extra cycle we may as well wait anyway, just to be safe.
    timer__schedule_cycles( (3.5/OPT__DEBOUNCE_TIME)+1, &write_queued );

    #undef  next_write
    #undef  next_copy
}

// ----------------------------------------------------------------------------

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

uint8_t eeprom__write(uint8_t * address, uint8_t data) {
    write_t * write = malloc(sizeof(write_t));
    if (!write) return 1;  // error

    write->action = ACTION_WRITE;
    write->to     = (uint16_t) address;
    write->value  = data;

    list__insert(&to_write, -1, write);

    if (! status.writing) {
        timer__schedule_cycles( 0, &write_queued );
        status.writing = true;
    }

    return 0;  // success
}

uint8_t eeprom__copy(uint8_t * to, uint8_t * from, uint8_t length) {
    write_t * write = malloc(sizeof(write_t));
    copy_t * copy = malloc(sizeof(copy_t));
    if (!(write && copy)) {
        free(write);
        free(copy);
        return 1;  // error
    }

    write->action = ACTION_COPY;
    write->to     = (uint16_t) to;
    write->value  = length;

    copy->from = (uint16_t) from;

    list__insert(&to_write, -1, write);
    list__insert(&to_copy, -1, copy);

    if (! status.writing) {
        timer__schedule_cycles( 0, &write_queued );
        status.writing = true;
    }

    return 0;  // success
}

