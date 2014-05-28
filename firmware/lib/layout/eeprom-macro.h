/* ----------------------------------------------------------------------------
 * Copyright (c) 2013, 2014 Ben Blazak <benblazak.dev@gmail.com>
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
 * Warnings:
 * - This library is meant to be used for recording and playing back
 *   *temporary* macros.  Permanent macros should be assigned to a key in the
 *   source of the layout directly.  Macros created using this library may be
 *   very difficult to retrieve and back up.  They may also be erased without
 *   warning in the event that they become corrupted by power loss or
 *   invalidated by future changes in the format of the persistent data used to
 *   store them.
 *
 * Terms:
 * - A "key" is a pair of actions, one for when the key is pressed and another
 *   for when it is released.  We specify keys by their `layer`, `row`, and
 *   `column`.
 * - A "key-action" is a single action.  We specify key-actions by their
 *   `pressed` value (whether the action corresponds to a press (`true`) or
 *   release (`false`)) and the key they belong to.
 * - A "macro" is a collection of data that lives in persistent memory, and
 *   specifies possibly many actions to perform in the place of a single,
 *   usually different, action.  For the purposes of this library, macros live
 *   in the EEPROM, and contain a key-action who's original behavior we wish
 *   to mask, and a list of key-actions that should be sequentially performed
 *   instead.
 * - A "keystroke" is a full press then release of a key.  Keystrokes may
 *   overlap each other.
 * - To "remap" a key-action is to assign a macro to it (masking, not
 *   replacing, what the key-action originally did).
 * - The "EEPROM" is an "Electronically Erasable Programmable Read Only
 *   Memory".  It is where this library stores persistent data.
 * - "EEMEM" is "EEprom MEMory" (i.e. another way of referring to the memory of
 *   the EEPROM, instead of the EEPROM itself) following the convention of
 *   avr-gcc.
 *
 * Usage notes:
 * - When macros are recorded, the key they are assigned to does not loose its
 *   functionality, but rather has that functionality masked by this new
 *   definition.
 * - Timing information may not be recorded, due to the space restrictions of
 *   the EEPROM.  If it is not, keys which change meaning depending on the
 *   timing with which they are pressed (and not just the sequence in which
 *   they are pressed) may not be played back as expected.
 *
 * Implementation notes:
 * - When macros are being recorded or played back, keys should operate with
 *   their original meanings (i.e. macro lookup should be disabled).  This may
 *   be inconvenient at times, e.g. if the user wishes to have a single macro
 *   execute several others which are already recorded, or if they wish to have
 *   an especially long macro which cannot (because of implementation
 *   limitations) be recorded in one piece.  It has many benefits, however.  It
 *   makes it impossible to define recursive macros (which would never
 *   terminate).  It makes it impossible for new macros to accidentally
 *   redefine old ones.  Perhaps most importantly, it makes it possible to
 *   create macros with actions that may have been masked by another macro, as
 *   one might wish to do when, for example, quickly swapping the positions of
 *   two letter keys.
 * - With sufficient trickiness, we could probably do away with having `layer`
 *   in the key-actions that make up the body of macros (most of this
 *   trickiness being in the logic for how users record macros and assign them
 *   to key-actions).  I could imagine there being situations where this turned
 *   out to be useful... but I feel like much more often it would just be a bit
 *   confusing.  It would also be inconsistent a little, having two different
 *   representations of a key-action.  And it wouldn't actually save us that
 *   much EEPROM.
 */


#ifndef ERGODOX_FIRMWARE__FIRMWARE__LIB__LAYOUT__EEPROM_MACRO__H
#define ERGODOX_FIRMWARE__FIRMWARE__LIB__LAYOUT__EEPROM_MACRO__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


#include <stdbool.h>
#include <stdint.h>

// ----------------------------------------------------------------------------

#if OPT__EEPROM__EEPROM_MACRO__START > OPT__EEPROM__EEPROM_MACRO__END
    #error "OPT__EEPROM__EEPROM_MACRO__START must be smaller than ...END"
#endif

// ----------------------------------------------------------------------------

#define  ARGS  bool pressed, uint8_t layer, uint8_t row, uint8_t column
uint8_t eeprom_macro__init            (void);
uint8_t eeprom_macro__record_init     ( ARGS );
uint8_t eeprom_macro__record_action   ( ARGS );
uint8_t eeprom_macro__record_finalize (void);
uint8_t eeprom_macro__record_cancel   (void);
uint8_t eeprom_macro__play            ( ARGS );
bool    eeprom_macro__exists          ( ARGS );
uint8_t eeprom_macro__clear           ( ARGS );
uint8_t eeprom_macro__clear_all       (void);
#undef  ARGS


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__FIRMWARE__LIB__LAYOUT__EEPROM_MACRO__H



// ============================================================================
// === documentation ==========================================================
// ============================================================================


// ----------------------------------------------------------------------------
// macros ---------------------------------------------------------------------
// ----------------------------------------------------------------------------

// === OPT__EEPROM__EEPROM_MACRO__START ===
/**                         macros/OPT__EEPROM__EEPROM_MACRO__START/description
 * The first EEMEM address in the block assigned to this section of the code 
 */

// === OPT__EEPROM__EEPROM_MACRO__END ===
/**                           macros/OPT__EEPROM__EEPROM_MACRO__END/description
 * The last EEMEM address in the block assigned to this section of the code 
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
 * - This function should initialize our portion of the EEPROM to the current
 *   format if we don't know how to read it; i.e. if the version of the data
 *   stored is different than what we expect, or if the data has been
 *   corrupted.
 */

// === eeprom_macro__record_init() ===
/**                             functions/eeprom_macro__record_init/description
 * Prepare to record a new macro
 *
 * Arguments:
 * - (group) The key-action to remap
 *     - `pressed`: Whether the key-action is a press (`true`) or a release
 *       (`false`)
 *     - `layer`: The layer of the key-action
 *     - `row`: The row of the key-action
 *     - `column`: The column of the key-action
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
 * - If a macro remapping the given key-action already exists, it should be
 *   deleted.
 */

// === eeprom_macro__record_action() ===
/**                           functions/eeprom_macro__record_action/description
 * Record the next key-action of the current macro
 *
 * Arguments:
 * - (group) The key-action to record
 *     - `pressed`: Whether the key-action is a press (`true`) or a release
 *     (`false`)
 *     - `layer`: The layer of the key-action
 *     - `row`: The row of the key-action
 *     - `column`: The column of the key-action
 *
 * Returns:
 * - success: `0`
 * - failure: [other]
 *
 * Notes:
 * - If this function fails, the macro currently being written may be canceled
 *   (thrown away).
 */

// === eeprom_macro__record_finalize() ===
/**                         functions/eeprom_macro__record_finalize/description
 * Finalize the recording of the current macro
 *
 * Returns:
 * - success: `0`
 * - failure: [other]
 *
 * Notes:
 * - Before this function is called, the macro (even though parts of it may be
 *   written) should not be readable, or referenced anywhere in the EEPROM.
 *
 * Notes:
 * - If this function fails, the macro currently being written may be canceled
 *   (thrown away).
 */

// === eeprom_macro__record_cancel() ===
/**                           functions/eeprom_macro__record_cancel/description
 * Cancel the recording of the current macro
 *
 * Returns:
 * - success: `0`
 * - failure: [other]
 *
 * Notes:
 * - Depending on the implementation, this function may not be necessary due to
 *   the behavior of `eeprom_macro__record_init()` and
 *   `eeprom_macro__record_finalize()`.  In that case this function should
 *   simply do nothing.
 */

// === eeprom_macro__play() ===
/**                                    functions/eeprom_macro__play/description
 * Play back recorded key-actions for the macro assigned to the specified key
 * action
 *
 * Arguments:
 * - (group) The key-action to search for
 *     - `pressed`: Whether the key-action is a press (`true`) or a release
 *     (`false`)
 *     - `layer`: The layer of the key-action
 *     - `row`: The row of the key-action
 *     - `column`: The column of the key-action
 *
 * Returns:
 * - success: `0` (macro successfully played)
 * - failure: [other] (macro does not exist)
 */

// === eeprom_macro__exists() ===
/**                                  functions/eeprom_macro__exists/description
 * Predicate indicating whether the specified key-action has been remapped
 *
 * Arguments:
 * - (group) The key-action to search for
 *     - `pressed`: Whether the key-action is a press (`true`) or a release
 *     (`false`)
 *     - `layer`: The layer of the key-action
 *     - `row`: The row of the key-action
 *     - `column`: The column of the key-action
 *
 * Returns:
 * - `true`: if a macro remapping the given key-action exists
 * - `false`: if a macro remapping the given key-action does not exist
 */

// === eeprom_macro__clear() ===
/**                                   functions/eeprom_macro__clear/description
 * Clear (delete) the macro assigned to the given key-action
 *
 * Arguments:
 * - (group) The key-action to un-remap
 *     - `pressed`: Whether the key-action is a press (`true`) or a release
 *     (`false`)
 *     - `layer`: The layer of the key-action
 *     - `row`: The row of the key-action
 *     - `column`: The column of the key-action
 *
 * Returns:
 * - success: `0`
 * - failure: [other]
 */

// === eeprom_macro__clear_all() ===
/**                               functions/eeprom_macro__clear_all/description
 * Clear (delete) all macros in the EEPROM
 *
 * Notes:
 * - For the purposes of this function, "clearing" the EEPROM means to put it
 *   in such a state that none of the functions declared here will be able to
 *   find a macro for any key-action.  This does not necessarily imply that the
 *   EEPROM is in a fully known state.
 *
 * Returns:
 * - success: `0`
 * - failure: [other]
 */

