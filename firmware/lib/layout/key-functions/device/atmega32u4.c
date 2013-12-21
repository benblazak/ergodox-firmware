/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Implements the "device" section of "../../key-functions.h" for the
 * ATMega23U4
 */


#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "../../../../../firmware/lib/eeprom.h"
#include "../../key-functions.h"

// ----------------------------------------------------------------------------

/**                                             functions/sram_read/description
 * A tiny little helper function to let `key_functions__dump_sram_ihex()` work
 * the same way as the other `...dump...ihex()` functions.
 *
 * Arguments:
 * - `from`: The address of (i.e. a pointer to) the location from which to read
 *
 * Returns:
 * - success: The data stored at `pointer` in the SRAM memory space
 */
static uint8_t sram_read(void * from) {
    return *(uint8_t *)from;
}

/**                                          functions/progmem_read/description
 * A tiny little helper function to let `key_functions__dump_progmem_ihex()`
 * work the same way as the other `...dump...ihex()` functions.
 *
 * Arguments:
 * - `from`: The address of (i.e. a pointer to) the location from which to read
 *
 * Returns:
 * - success: The data stored at `pointer` in the PROGMEM memory space
 */
static uint8_t progmem_read(void * from) {
    return pgm_read_byte(from);
}

/**                                             functions/dump_ihex/description
 * Type, in ihex format, all data between `from` and `last`, inclusive.
 *
 * Arguments:
 * - `read`: A pointer to a function that takes a memory address and returns 1
 *   byte of data (presumably from that memory address, in whatever address
 *   space we're dealing with)
 * - `from`: A pointer to the location from which to start reading
 * - `last`: A pointer to the last location from which to read
 *
 * Notes:
 * - See [the Wikipedia article] (http://en.wikipedia.org/wiki/Intel_HEX) on
 *   the Intel HEX (ihex) format.
 *
 * Implementation notes:
 * - When the loop starts, `from` might be `0`, and `last` might be
 *   `UINT16_MAX`, in which case `from == last+1`.  We need to ignore this on
 *   the first iteration, hence the do-while loop and the `from != last+1` part
 *   of the first conditional.  When this condition occurs after the first
 *   iteration, it will be because `from` was incremented one past `last`, and
 *   the loop should be terminated.
 * - Pointer comparisons in C are interesting...  Specifically, `last-from+1 <
 *   line_width` seems to cast `last-from+1` to the same type as `line_width`
 *   (`uint8_t`) which causes problems since pointers on this platform are 16
 *   bits.  Casting either side of the expression to `uint16_t` seems to solve
 *   the problem.  It feels cleaner to me to cast the pointer side, because
 *   comparison between pointers and integers is only implementation defined,
 *   whereas comparison between two integers ought to be defined by the
 *   standard.
 */
static void dump_ihex( uint8_t (*read)(void *),
                       void * from,
                       void * last ) {

    if (from > last)
        return;  // error

    const uint8_t record_type = 0x00;  // ihex record type = data
          uint8_t line_width  = 0x10;  // 16 bytes of data per line, by default

    do {
        // - As long as `from != last+1`, `last-from+1` is the number of bytes
        //   left to print
        if (from != last+1 && (uint16_t)(last-from+1) < line_width)
            line_width = last-from+1;

        uint8_t checksum = line_width + record_type
                         + ((uint16_t)(from) >> 8)
                         + ((uint16_t)(from) & 0xFF);

        key_functions__type_string( PSTR(":") );
        key_functions__type_byte_hex( line_width );
        key_functions__type_byte_hex( (uint16_t)(from) >> 8 );
        key_functions__type_byte_hex( (uint16_t)(from) & 0xFF );
        key_functions__type_byte_hex( record_type );

        for (uint8_t l=0; l<line_width; l++) {
            uint8_t byte = (*read)(from++);
            checksum += byte;
            key_functions__type_byte_hex(byte);
        }

        key_functions__type_byte_hex( 0x100 - checksum );  // 2's compliment
        key_functions__type_string( PSTR("\n") );

    } while (from != last+1);

    key_functions__type_string( PSTR(":00000001FF\n") );  // ihex EOF record
}

// ----------------------------------------------------------------------------

/**                     functions/key_functions__jump_to_bootloader/description
 * Implementation notes:
 * - This code is from PJRC (slightly modified):
 *   <http://www.pjrc.com/teensy/jump_to_bootloader.html>.
 *
 */
void key_functions__jump_to_bootloader(void) {
    // --- for all Teensy boards ---

    cli();

    // disable watchdog, if enabled
    // disable all peripherals
    UDCON = 1;
    USBCON = (1<<FRZCLK);  // disable USB
    UCSR1B = 0;
    _delay_ms(5);

    // --- Teensy 2.0 specific ---

    EIMSK = 0; PCICR = 0; SPCR = 0; ACSR = 0; EECR = 0; ADCSRA = 0;
    TIMSK0 = 0; TIMSK1 = 0; TIMSK3 = 0; TIMSK4 = 0; UCSR1B = 0; TWCR = 0;
    DDRB = 0; DDRC = 0; DDRD = 0; DDRE = 0; DDRF = 0; TWCR = 0;
    PORTB = 0; PORTC = 0; PORTD = 0; PORTE = 0; PORTF = 0;
    asm volatile("jmp 0x7E00");
}

void key_functions__dump_sram_ihex(void * from, void * last) {
    if (last > (void *)RAMEND)
        last = (void *)RAMEND;
    dump_ihex(&sram_read, from, last);
}

void key_functions__dump_progmem_ihex(void * from, void * last) {
    if (last > (void *)FLASHEND)
        last = (void *)FLASHEND;
    dump_ihex(&progmem_read, from, last);
}

void key_functions__dump_eeprom_ihex(void * from, void * last) {
    if (last > (void *)E2END)
        last = (void *)E2END;
    dump_ihex(&eeprom__read, from, last);
}

