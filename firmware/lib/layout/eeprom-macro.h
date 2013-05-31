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

// - "block"s are 4 bytes, aligned on the 4 byte boundary
// - all pointers are 1 byte (until converted for use), representing the offset
//   of a block

/*
 *   header                                 block 0x00
 *   .--------+--------+--------+--------.  addresses 0x0000..0x0003
 * 0 |version | free   |     padding     |          = 0x00<<2..(0x00<<2)+3
 *   '--------+--------+--------+--------'
 *
 *   table                                 blocks 0x01..0x03
 *   (example for a [3][3] matrix)         addresses 0x0004..0x000F
 *   .--------.   .--------.   .--------.          = 0x01<<2..(0x03<<2)+3
 * 1 |pointer |   |pointer |   |pointer |
 *   '--------'   '--------'   '--------'
 *   .--------.   .--------.   .--------.
 *   |pointer | 2 |pointer |   |pointer |
 *   '--------'   '--------'   '--------'
 *   .--------.   .--------.   .--------.
 *   |pointer |   |pointer | 3 |pointer |
 *   '--------'   '--------'   '--------'
 *   .--------.   .--------.   .--------.
 *   |padding |   |padding |   |padding |
 *   '--------'   '--------'   '--------'
 *
 *
 *   macros                                        blocks 0x04..0xFF
 *   (example for a [3][3] matrix, above)          addresses 0x0016..0x03FF
 *
 *   .--------+--------.   .--------+--------.
 * 4 |  next  |run_len |   |      index      |
 *   '--------+--------'   '-----------------'
 *   .--------+--------.
 * 5 |      index      |
 *   '--------+--------'
 *   .--------+--------.
 *   |      index      |
 *   '--------+--------'
 *
 * 6 ...
 */

#define  ROWS  OPT__KB__ROWS     // for '.c' file
#define  COLS  OPT__KB__COLUMNS  // for '.c' file

#define  START_HEADER  0x00
#define  START_TABLE   0x01
#define  START_MACROS  (((ROWS * COLS + 0x3) >> 2) + 1)  // > 1
#define  END_EEPROM    0xFF

#define  FLAG_DELETED  0x01

struct header {
    uint8_t  version;     // of this layout; 0x00 or 0xFF => uninitialized
    uint8_t  start_free;  // pointer to the first unallocated block
    uint16_t padding;
};

struct table {
    uint8_t pointers[ ROWS * COLS ];  // to `macro`s
    uint8_t padding[ 3 - ((ROWS * COLS) & 0x3) ];  // may be length = 0
};

struct macro {
    uint8_t next;  // 0x00 => last for this [row][col]
                   // 0x01 => "deleted" macro
    uint8_t run_length;
    eeprom_macro__index_t index;
};

struct action {  // `run_length` of these will follow `macro`
    eeprom_macro__index_t index;  // `layer` will be unset and ignored
};

// ----------------------------------------------------------------------------

typedef struct {
    bool    pressed : 1;
    uint8_t layer   : 5;
    uint8_t row     : 5;
    uint8_t column  : 5;
} eeprom_macro__index_t;
/* - this format artificially limits the number of layers, rows, and columns to
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

uint8_t eeprom_macro__init(void);
/* - check version
 * - "zero" EEPROM if necessary (i.e. if uninitialized for the current version)
 */

uint8_t eeprom_macro__get_size_free(void);
/* - return free space, in blocks
 */

void eeprom_macro__play(eeprom_macro__index_t index);
/* - play back keystrokes (loop: call `kb__layout__exec_key()`)
 */

uint8_t eeprom_macro__record__start(uint8_t skip);
/* - skip `skip` keypresses
 *   - (`...exec_key()` may need these to determine what key to assign the
 *     macro to
 *   - we don't need to worry about them, since the keyboard may want to assign
 *     the macro to a different key; and if the keyboard is using layers we
 *     can't tell what key to assign it to ourselves without a bunch of pain
 *     anyway
 * - start recording
 * - return 0 on success, other on failure
 */
uint8_t eeprom_macro__record__stop(uint8_t skip, eeprom_macro__index_t index);
/* - stop recording
 * - discard `skip` keypresses
 * - update all header and "filesystem" information
 * - return 0 on success, other on failure
 */

void eeprom_macro__compress(void);
/* - remove all "deleted" macros, shifting active ones toward address 0
 */

void eeprom_macro__clear(eeprom_macro__index_t index);
/* - set the `next` pointer for this index to `FLAG_DELETED`
 */

void eeprom_macro__clear_all(void);
/* - put EEPROM into a valid and intialized, but "zeroed" state
 */


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__FIRMWARE__LIB__LAYOUT__EEPROM_MACRO__H

