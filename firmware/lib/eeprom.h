/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * EEPROM interface
 *
 * Prefix: `eeprom__`
 *
 * Notes:
 * - This is meant to be a replacement for the read, write, and update
 *   functions provided by `<avr/eeprom.h>`, and should be preferred for those
 *   operations.  There are other things provided by that header that may be
 *   useful however, and it's likely that both will be needed.
 */


#ifndef ERGODOX_FIRMWARE__LIB__EEPROM__H
#define ERGODOX_FIRMWARE__LIB__EEPROM__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


#include <stdint.h>

// ----------------------------------------------------------------------------

uint8_t eeprom__read  (uint8_t * address);
void    eeprom__write (uint8_t * address, uint8_t data);


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__LIB__EEPROM__H



// ============================================================================
// === documentation ==========================================================
// ============================================================================


// === eeprom__read() ===
/**                                          functions/eeprom__read/description
 * Read and return the data at `address` in the EEPROM memory space
 *
 * Arguments:
 * - `address: The address of (i.e. a pointer to) the location to operate on
 */

// === eeprom__write() ===
/**                                         functions/eeprom__write/description
 * Schedule a write to `address` in the EEPROM memory space
 *
 * Arguments:
 * - `address: The address of (i.e. a pointer to) the location to operate on
 * - `data`: The data to write
 *
 *
 * Notes:
 *
 * - Due to the technology used, EEPROM bytes, when cleared, have a logical
 *   value of `1`.  Interesting stuff, but I didn't read about it thoroughly
 *   enough to give my own explanation here.
 *
 *
 * Implementation notes:
 *
 * - If possible, this function should only modify when necessary; that is,
 *   when the data to be written is different than the data that's already
 *   there.  This requires more processor time (to read the current value and
 *   compare), but it's better for the EEPROM (which has a limited write life),
 *   and will allow the operation to complete *much* more quickly in the event
 *   that the data has not changed.
 *
 * - If possible, writing `0xFF` should clear the memory (without writing
 *   anything), and writing to a location currently set to `0xFF` should write
 *   without clearing first.
 *
 * - If possible, this function should "schedule" writes to the EEPROM; that
 *   is, it should keep track of what needs to be written and write it more or
 *   less as soon as possible, but return quickly after it's called without
 *   waiting for the write (or even previous writes) to finish.
 */

