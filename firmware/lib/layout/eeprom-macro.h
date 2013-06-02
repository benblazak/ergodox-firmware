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
 * TODO: might need a "get_size_total()" and "get_size_free()" later, for
 * information display purposes
 *
 *
 * TODO: rewrite the following
 * notes:
 *
 * - these functions will play back keystrokes, not functions or (layer, row,
 *   column) tuples, or anything like that.  this means that if you press a key
 *   that has a macro assigned to it while defining a new macro, the former
 *   macro will be activated each time the new macro is run (unless it is
 *   deleted).  this means that if you intend to use these functions to move
 *   letter keys around, you should probably have a layer somewhere with all
 *   the letters on it, and define the macros on your home layer to press keys
 *   on that other layer.  otherwise, assigning a macro to a letter key will
 *   make that letter unreachable until the macro is removed.
 *
 * - or (instead of the above) `...exec_key()` could handle macro assignment
 *   differently, and trigger macro replay based on something besides what i'm
 *   currently thinking of for the ergodox.  that is, "layers" here need not
 *   correspond to "layers" elsewhere in the firmware, except for the purposes
 *   of convenience, and possibly sanity (both of which are typically overruled
 *   by memory constraints...).
 */


#ifndef ERGODOX_FIRMWARE__FIRMWARE__LIB__LAYOUT__EEPROM_MACRO__H
#define ERGODOX_FIRMWARE__FIRMWARE__LIB__LAYOUT__EEPROM_MACRO__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


typedef struct {
    bool    pressed : 1;
    uint8_t layer   : 5;
    uint8_t row     : 5;
    uint8_t column  : 5;
} eeprom_macro__index_t;

// ----------------------------------------------------------------------------

uint8_t eeprom_macro__init          (void);
uint8_t eeprom_macro__record__start (uint8_t skip);
uint8_t eeprom_macro__record__stop  (uint8_t skip, eeprom_macro__index_t index);
uint8_t eeprom_macro__play          (eeprom_macro__index_t index);
void    eeprom_macro__clear         (eeprom_macro__index_t index);
void    eeprom_macro__clear_all     (void);


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__FIRMWARE__LIB__LAYOUT__EEPROM_MACRO__H



// ============================================================================
// === documentation ==========================================================
// ============================================================================


// ----------------------------------------------------------------------------
// types ----------------------------------------------------------------------

// === eeprom_macro__index_t ===
/**                                     types/eeprom_macro__index_t/description
 * A convenient way to specify a position in the layer matrix
 *
 * Used here to uniquely identify macros, and to group them for optimizations.
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

// === eeprom_macro__init ===
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

// === eeprom_macro__record__start ===
/**                           functions/eeprom_macro__record__start/description
 * Start recording keystrokes to the EEPROM, for the creation of a macro
 *
 * Arguments:
 * - `skip`: The number of keystrokes to skip before beginning to record
 *
 * Returns:
 * - success: `0`
 * - failure: [other] (not enough memory left to record)
 *
 * Notes:
 * - Skipping keystrokes may be useful, for example, if the using function
 *   wants to define the first key pressed after this function is called as the
 *   key to assign the macro to, rather than as part of the macro.
 */

// === eeprom_macro__record__stop ===
/**                            functions/eeprom_macro__record__stop/description
 * Stop recording keystrokes, and finalize the macro
 *
 * Arguments:
 * - `skip`: The number of keystrokes at the end of our recording to ignore
 * - `index`: The unique ID of this macro
 *
 * Returns:
 * - success: `0`
 * - failure: [other] (macro was too long to fit in EEPROM)
 *
 * Notes:
 * - Before this function is called, the macro should not be referenced
 *   anywhere in the EEPROM.
 */

// === eeprom_macro__play ===
/**                                    functions/eeprom_macro__play/description
 * Play back recorded keystrokes for the macro with unique ID `index`
 *
 * Arguments:
 * - `index`: The unique ID of the macro to play
 *
 * Returns:
 * - `0`: Macro successfully played
 * - [other]: Error (macro does not exist)
 *
 * Notes:
 * - Keystrokes will be played back as if the same sequence of keys were being
 *   pressed by the user (regardless of whether the current state of the
 *   keyboard is the same), except as fast as possible (since timing is not
 *   recorded).
 */

// === eeprom_macro__clear ===
/**                                   functions/eeprom_macro__clear/description
 * Clear the macro with unique ID `index`
 *
 * Arguments:
 * - `index`: The unique ID of the macro to clear
 */

// === eeprom_macro__clear_all ===
/**                               functions/eeprom_macro__clear_all/description
 * Clear all macros in the EEPROM
 *
 * Notes:
 * - For the purposes of this function, "clearing" the EEPROM means to put it
 *   in such a state that none of the functions declared here will be able to
 *   find a macro for any `index`.  This does not necessarily imply that the
 *   EEPROM is in a fully known state.
 */


