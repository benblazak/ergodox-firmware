/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Implements the EEPROM interface defined in "../eeprom.h" for the ATMega32U4
 *
 * These functions (and most of the comments) are taken more or less straight
 * from the data sheet, section 5.3
 *
 * Assumptions
 * - Voltage will never fall below the specified minimum for the clock
 *   frequency being used.
 * - The address passed as `address` to any of the functions is valid.
 * - A write to flash memory (PROGMEM) will never be in progress when any of
 *   these functions are called.
 *
 * Warnings:
 * - These functions are *not* reentrant (i.e. they must never be called within
 *   an interrupt unless all calls to these functions are protected by having
 *   interrupts disabled for the duration of the call).
 */


#include <stdint.h>
#include <util/atomic.h>
#include <avr/io.h>
#include "../eeprom.h"

// ----------------------------------------------------------------------------

/**                                          functions/eeprom__read/description
 * Implementation notes:
 *
 * - If a write is in progress when this function is called, this function will
 *   busy wait until the write has been completed.  This may take quite some
 *   time (up to 3.4 ms if a write has just been started), so you should be
 *   careful about when this function is called.
 */
uint8_t eeprom__read(uint8_t * address) {
  while (EECR & (1<<EEPE));   // wait for previous write to complete
  EEAR = (uint16_t) address;  // set up address register
  EECR |= (1<<EERE);          // start EEPROM read (then halt, 4 clock cycles)
  return EEDR;                // return the value in the data register
}

/**                                         functions/eeprom__write/description
 * Implementation notes:
 *
 * - If another write is in progress when this function is called, this
 *   function will busy wait until the first write has been completed.  This
 *   may take quite some time (up to 3.4 ms if a write has just been started),
 *   so you should be careful about when this function is called.
 *
 * - This function starts the write to the EEPROM, but returns long before it
 *   has been completed.
 *
 * TODO: this should *schedule* writes
 */
void eeprom__write(uint8_t * address, uint8_t data) {

    // - if a write is in progress, this will also wait until it's finished
    uint8_t old_data = eeprom__read(address);

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

    EEAR = (uint16_t) address;  // set up address register
    EEDR = data;                // set up data register

    // - interrupts must be disabled between these two operations, or else
    //   "EEPROM Master Programming Enable" may time out (since it's cleared by
    //   hardware 4 clock cycles after being written to `1` by software)
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        EECR |= (1<<EEMPE);  // set "EEPROM Master Programming Enable" to `1`
        EECR |= (1<<EEPE);   // start EEPROM write (then halt, 2 clock cycles)
    }
}

