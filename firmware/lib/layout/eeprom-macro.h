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
 */

/*
 * TODO: everything: still in the planning stages
 */

/*
 * notes:
 *
 * - these functions will play back keypresses, not functions or (layer, row,
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


/*
 * layout_matrix_index
 *
 * (see struct below)
 *
 * - this format artificially limits the number of layers, rows, and columns to
 *   2^5 = 32 each, which seems like it'd be hard to practically exceed.  this
 *   is done because it's much easier to extract the values we're going to use
 *   if we separate them this way than if we reverse the array offset
 *   calculations for `[layer][row][column]`.
 *
 * - note that 15 bits in *some* format will always be enough to store our
 *   index, since 2^15 = 32768 positions are unlikely to be taken up by any
 *   layout matrix ever; on the ATMega32U4 it would be impossible, since
 *   there's only 32256 bytes of PROGMEM to begin with.
 */

/*
 * EEPROM
 *
 * ls = layers, rs = rows, cs = columns (total)
 * l  = layer,  r  = row,  c  = column  (current)
 *
 * 0<<2 : version number of the layout (0x00 or 0xFF => not initialized)
 * +1   : (address >> 2) of the first unused 4-byte block
 * +2   : padding
 * +3   : padding
 * 1<<2 : (start)
 * ...  : table of 8-bit pointers to 4-byte blocks, beginning after this table,
 *        containing headers for macro sequences
 *        - 1 pointer for each key in the rs*cs matrix
 *        - a "macro sequence" is a `macro_header` followed by a varying number
 *          of `key_actions`
 * ceil([rs*cs]/4)<<2 = ((rs*cs)+0x3)&0xFC : (end)
 * previous + (1<<2) : (start)
 * ...  : macro sequences
 * 255<<2 : (end) (end of EEPROM)
 */

/*
 * TODO: rename everything and reorganize and stuff
 */
struct layout_matrix_index {
    bool    pressed : 1;
    uint8_t layer   : 5;
    uint8_t row     : 5;
    uint8_t column  : 5;
};  // total: 2 bytes
struct macro_header {
    uint8_t next : 8;
    /* (address >> 2) of the next macro sequence assigned to the same (row,
     * column)
     */
    uint8_t run_length : 8;
    /* the number of `key_action`s following this header
     */
    struct layout_matrix_index index : 16;
};  // total: 4 bytes
struct key_action {
    bool    _ignore : 1;  // padding
    bool    pressed : 1;
    uint8_t row     : 7;
    uint8_t column  : 7;
};  // total: 2 bytes


uint8_t eeprom_macro__init(void);
/* - check version
 * - initialize the EEPROM if necessary
 */

void eeprom_macro__play(uint16_t layout_matrix_index);
/* - play back keystrokes (loop: call `kb__layout__exec_key()`)
 */

void eeprom_macro__record__start(uint8_t skip);
/* - skip `skip` keypresses
 *   - (`...exec_key()` may need these to determine what key to assign the
 *     macro to
 *   - we don't need to worry about them, since the keyboard may want to assign
 *     the macro to a different key; and if the keyboard is using layers we
 *     can't tell what key to assign it to ourselves without a bunch of pain
 *     anyway
 * - start recording
 */
void eeprom_macro__record__stop(uint8_t skip, uint16_t layout_matrix_index);
/* - stop recording
 * - discard `skip` keypresses
 * - update all header and "filesystem" information
 */

// TODO: we probably want a delete, and maybe a clear-all function


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__FIRMWARE__LIB__LAYOUT__EEPROM_MACRO__H

