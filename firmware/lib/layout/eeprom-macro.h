/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * EEPROM macro interface
 *
 * Prefix: `eeprom_macro__`
 *
 * This file is meant to be included and used by the keyboard layout
 * implementation.
 *
 *
 * Usage notes:
 *
 * - These functions will play back keystrokes, not actions.  This means that
 *   new macro definitions may affect old ones.  It also means that different
 *   keyboard states may lead to different actions being performed for the same
 *   macro (if, say, the layer the macro is on is mostly transparent, and there
 *   is a different layer underneath it on a subsequent press than there was
 *   during definition).
 *
 * - Even though `eeprom_macro__uid_t` has distinct fields, there is nothing
 *   that says the calling function(s) must maintain the semantic meanings of
 *   those fields.  I imagine that under most circumstances one would want to,
 *   but as long as the '.c' file implementing this interface agrees (or at
 *   least works) with whatever the calling functions are doing, things should
 *   be fine.
 *
 *     - For example, if there were a layout implementation that ignored
 *       layers, but wanted to manually map different key combinations to
 *       different macros for a given key, this could be done by repurposing
 *       the `layer` field to mean "key combination id" (or some such thing).
 */


#ifndef ERGODOX_FIRMWARE__FIRMWARE__LIB__LAYOUT__EEPROM_MACRO__H
#define ERGODOX_FIRMWARE__FIRMWARE__LIB__LAYOUT__EEPROM_MACRO__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


#include <stdbool.h>
#include <stdint.h>

// ----------------------------------------------------------------------------

typedef struct {
    bool    pressed : 1;
    uint8_t layer   : 5;
    uint8_t row     : 5;
    uint8_t column  : 5;
} eeprom_macro__uid_t;

// ----------------------------------------------------------------------------

uint8_t eeprom_macro__init             (void);
uint8_t eeprom_macro__record_init      (void);
uint8_t eeprom_macro__record_keystroke ( bool    pressed,
                                         uint8_t row,
                                         uint8_t column );
uint8_t eeprom_macro__record_finalize  (eeprom_macro__uid_t index);
uint8_t eeprom_macro__play             (eeprom_macro__uid_t index);
void    eeprom_macro__clear            (eeprom_macro__uid_t index);
void    eeprom_macro__clear_all        (void);


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__FIRMWARE__LIB__LAYOUT__EEPROM_MACRO__H



// ============================================================================
// === documentation ==========================================================
// ============================================================================


// ----------------------------------------------------------------------------
// types ----------------------------------------------------------------------
// ----------------------------------------------------------------------------

// === eeprom_macro__uid_t ===
/**                                       types/eeprom_macro__uid_t/description
 * A Unique IDentifier for a macro; also a convenient way to specify a position
 * in the layer matrix
 *
 * Notes:
 * - This format artificially limits the number of layers, rows, and columns
 *   that can be specified to 2^5 = 32 each.  This seems like it'd be hard to
 *   reach practically, but it's much less than the limit of 2^8 possible
 *   values each imposed by most of the rest of the firmware, so it's worth
 *   noting.
 *     - An alternate method would be to use all 15 bits (since 1 of the 16
 *       available bits is allocated to `pressed`) to represent a layer matrix
 *       index calculated according to the normal rules of array indexing for
 *       some `[layer][row][column]`.  The current method is preferred because
 *       it makes it much easier to extract the component values (which is
 *       helpful in grouping the macros, which is helpful in macro seek time
 *       optimizations).
 *     - 15 bits in *some* format should always be enough to uniquely identify
 *       every possible macro.  On the ATMega32U4 it would be impossible to
 *       exceed this, since it only has 32256 bytes of PROGMEM to begin with.
 *       Even if there was more, however, it seems unlikely that more than
 *       2^15 = 32768 positions would be specified by any layer matrix.
 */


// ----------------------------------------------------------------------------
// functions ------------------------------------------------------------------
// ----------------------------------------------------------------------------

// === eeprom_macro__init() ===
/**                                    functions/eeprom_macro__init/description
 * Perform any necessary initializations
 *
 * Returns:
 * - success: `0`
 * - failure: [other]
 *
 * Meant to be called exactly once by `kb__init()`
 *
 * Notes:
 * - This function should zero the EEPROM to the current format if the version
 *   of the data stored is different than what we expect.
 */

// === eeprom_macro__record_init() ===
/**                             functions/eeprom_macro__record_init/description
 * Prepare to record a new macro
 *
 * Returns:
 * - success: `0`
 * - failure: [other]
 *
 * Notes:
 * - Only one macro may be recorded at a time.  If another macro is being
 *   recorded when this function is called (i.e.  this function has been called
 *   once already, and `...finalize()` has not been called yet), the old macro
 *   should be thrown away, and this new one prepared for.
 */

// === eeprom_macro__record_keystroke() ===
/**                        functions/eeprom_macro__record_keystroke/description
 * Record the next keystroke of the current macro
 *
 * Arguments:
 * - `pressed`: Whether or not the keystroke being recorded is a "press" or a
 *   "release"
 * - `row`: The row of the keystroke being recorded
 * - `column`: The column of the keystroke being recorded
 *
 * Returns:
 * - success: `0`
 * - failure: [other] (recording not initialized, or not enough memory left to
 *   record)
 */

// === eeprom_macro__record_finalize() ===
/**                         functions/eeprom_macro__record_finalize/description
 * Finalize the recording of the current macro
 *
 * Arguments:
 * - `index`: The UID of this macro
 *
 * Returns
 * - success: `0`
 * - failure: [other] (macro was too long to fit in EEPROM)
 *
 * Notes:
 * - Before this function is called, the macro (even though parts of it may be
 *   written) should not be readable, or referenced anywhere in the EEPROM
 */

// === eeprom_macro__play() ===
/**                                    functions/eeprom_macro__play/description
 * Play back recorded keystrokes for the macro with UID `index`
 *
 * Arguments:
 * - `index`: The UID of the macro to play
 *
 * Returns:
 * - success: `0` (macro successfully played)
 * - failure: [other] (macro does not exist)
 *
 * Notes:
 * - Keystrokes will be played back as if the same sequence of keys were being
 *   pressed by the user (regardless of whether the current state of the
 *   keyboard is the same), except as fast as possible (since timing is not
 *   recorded).
 */

// === eeprom_macro__clear() ===
/**                                   functions/eeprom_macro__clear/description
 * Clear the macro with UID `index`
 *
 * Arguments:
 * - `index`: The UID of the macro to clear
 */

// === eeprom_macro__clear_all() ===
/**                               functions/eeprom_macro__clear_all/description
 * Clear all macros in the EEPROM
 *
 * Notes:
 * - For the purposes of this function, "clearing" the EEPROM means to put it
 *   in such a state that none of the functions declared here will be able to
 *   find a macro for any `index`.  This does not necessarily imply that the
 *   EEPROM is in a fully known state.
 */


