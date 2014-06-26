/* ----------------------------------------------------------------------------
 * Copyright (c) 2013, 2014 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Implements the eeprom-macro functionality defined in "../eeprom-macro.h" for
 * the ATMega32U4
 *
 *
 * Warnings:
 *
 * - A worst case `compress()` operation might take too much memory.  Not sure
 *   what (if anything) to do about this right now.
 *     - Max EEPROM space for macros: 1024-5 = 1019 bytes
 *     - Min space for a macro: 5 bytes
 *     - Approximate space for a copy object in ".../lib/eeprom": 5 bytes
 *     - Worst case would be EEMEM filled with the smallest possible macros,
 *       alternating between valid and deleted.  This would give us 1019/5/2 ~=
 *       100 noncontiguous deleted macros, which would be about as many copy
 *       objects (plus a few write objects) in ".../lib/eeprom", so about 500
 *       bytes.  SRAM is 2560 bytes (per the PJRC website).  Because of the way
 *       ".../lib/eeprom" is written, much of this data would have to be
 *       contiguous.
 *     - At some point, I should probably consider changing how
 *       ".../lib/eeprom" (and the layer-stack code, and everything else that
 *       needs a variable amount of memory) manages its memory.  Again, not
 *       quite sure how, at the moment.  For common cases, the current solution
 *       might be sufficient.
 *     - If this turns out to be a problem, the easiest solution (at the
 *       expense of extra EEPROM wear in lower memory locations) would probably
 *       be to simply call `compress()` more often.
 *
 *
 * Implementation notes:
 *
 * - The default state (the "erased" state) of this EEPROM is all `1`s, which
 *   makes setting a byte to `0xFF` easier and faster in hardware than zeroing
 *   it (and also causes less wear on the memory over time, I think).  This is
 *   reflected in some of the choices for default values, and such.
 *
 * - GCC and AVR processors (and Intel processors, for that matter) are
 *   primarily little endian: in avr-gcc, multi-byte data types are allocated
 *   with the least significant byte occupying the lowest address.  Protocols,
 *   data formats (including UTF-8), and such are primarily big endian.  I like
 *   little endianness better -- it just feels nicer to me -- but after writing
 *   a bit of code, it seems that big endian serializations are easier to work
 *   with, at least in C.  For that reason, this code organizes bytes in a big
 *   endian manner whenever it has a choice between the two.
 *
 * - For a long time, I was going to try to make this library robust in the
 *   event of power loss, but in the end I decided not to.  This feature is
 *   meant to be used for *temporary* macros -- so, with the risk of power loss
 *   during a critical time being fairly low, and the consequence of (detected)
 *   data corruption hopefully more of an annoyance than anything else, I
 *   decided the effort (and extra EEMEM usage) wasn't worth it.
 */


#include <stdint.h>
#include "../../../../firmware/keyboard.h"
#include "../../../../firmware/lib/eeprom.h"
#include "../eeprom-macro.h"

// ----------------------------------------------------------------------------
// checks ---------------------------------------------------------------------

/**                           macros/OPT__EEPROM__EEPROM_MACRO__END/description
 * Implementation notes:
 * - The ATMega32U4 only has 1024 bytes of EEPROM (beginning with byte 0)
 */
#if OPT__EEPROM__EEPROM_MACRO__END > 1023
    #error "OPT__EEPROM__EEPROM_MACRO__END must not be greater than 1023"
#endif

#if OPT__EEPROM__EEPROM_MACRO__END - OPT__EEPROM__EEPROM_MACRO__START < 300
    #warn "Only a small space has been allocated for macros"
#endif

// ----------------------------------------------------------------------------
// macros ---------------------------------------------------------------------

/**                                                  macros/VERSION/description
 * The version number of the EEMEM layout
 *
 * Assignments:
 * - 0x00: Reserved: EEPROM not yet initialized, or in inconsistent state
 * - 0x01: First version
 * - ... : (not yet assigned)
 * - 0xFF: Reserved: EEPROM not yet initialized, or in inconsistent state
 */
#define  VERSION  0x01

/**                                     macros/(group) EEMEM layout/description
 * To define the layout of our section of the EEPROM
 *
 * Members:
 * - `EEMEM_START`: The address of the first byte of our block of EEMEM
 * - `EEMEM_START_ADDRESS_START`
 * - `EEMEM_START_ADDRESS_END`
 * - `EEMEM_END_ADDRESS_START`
 * - `EEMEM_END_ADDRESS_END`
 * - `EEMEM_VERSION_START`
 * - `EEMEM_VERSION_END`
 * - `EEMEM_MACROS_START`
 * - `EEMEM_MACROS_END`
 * - `EEMEM_END`: The address of the last byte of our block of EEMEM
 *
 * Terms:
 * - The "address" of a macro is the EEMEM address of the first byte of that
 *   macro.
 * - The "header" of a macro is the part of the macro containing the macro's
 *   type and length.
 * - The "data" of a macro is everything following the macro's header.
 *
 * Notes:
 * - `START_ADDRESS` and `END_ADDRESS` are written as part of our effort to
 *   make sure that the assumptions in place when writing the data don't shift
 *   (undetected) by the time it gets read.  Either of these values could
 *   change, legitimately, without `VERSION` being incremented, but it's
 *   important that any two builds of the firmware that deal with this section
 *   of the EEPROM have the same values for each.
 *
 *
 * EEMEM sections:
 *
 * - START_ADDRESS:
 *     - byte 0: MSB of `EEMEM_START`
 *     - byte 1: LSB of `EEMEM_START`
 *
 *     - Upon initialization, if this block does not have the expected value,
 *       our portion of the EEPROM should be reinitialized.
 *
 * - END_ADDRESS:
 *     - byte 0: MSB of `EEMEM_END`
 *     - byte 1: LSB of `EEMEM_END`
 *
 *     - Upon initialization, if this block does not have the expected value,
 *       our portion of the EEPROM should be reinitialized.
 *
 * - VERSION:
 *     - byte 0:
 *         - This byte will be set to `VERSION` as the last step of
 *           initializing our portion of the EEPROM.
 *         - Upon initialization, if this value is not equal to the current
 *           `VERSION`, our portion of the EEPROM should be reinitialized.
 *
 * - MACROS: byte 0..`(EEMEM_END - EEMEM_VERSION_END - 1)`:
 *     - This section will contain a series of zero or more macros, each with
 *       the following format:
 *         - byte 0: `type == TYPE_DELETED`
 *             - byte 1: `length`: the total number of bytes used by this
 *               macro, including the bytes for `type` and `length`
 *             - byte 2...: (optional) undefined
 *         - byte 0: `type == TYPE_VALID_MACRO`
 *             - byte 1: `length`: the total number of bytes used by this
 *               macro, including the bytes for `type` and `length`
 *             - byte 2...: (variable length, as described below)
 *                 - `key-action` 0: the key-action which this macro remaps
 *             - byte ...: (optional) (variable length, as described below)
 *                 - `key-action` 1...: the key-actions to which `key-action` 0
 *                   is remapped
 *         - byte 0: `type == TYPE_END`
 *             - byte 1...: (optional) undefined
 *
 *     - The last macro in this series will have `type == TYPE_END`.
 *
 *     - A key-action is a variable length encoding of the information in a
 *       `key_action_t`, with the following format:
 *
 *           byte 0
 *           .----------------------------------------------.
 *           |     7     |    6    | 5 | 4 | 3 | 2 | 1 | 0  |
 *           |----------------------------------------------|
 *           | continued | pressed | layer |  row  | column |
 *           '----------------------------------------------'
 *
 *           byte 1..3 (optional)
 *           .----------------------------------------------.
 *           |     7     |    6    | 5 | 4 | 3 | 2 | 1 | 0  |
 *           |----------------------------------------------|
 *           | continued |    1    | layer |  row  | column |
 *           '----------------------------------------------'
 *
 *         - `continued`:
 *             - `1`: The next byte is part of this key-action
 *             - `0`: The next byte is not part of this key-action (i.e. this
 *                    is the last byte in this key-action)
 *
 *         - `pressed`:
 *             - This value is stored *only* in the first byte.  In all
 *               subsequent bytes the bit should be set to `1`.
 *
 *         - `layer`, `row`, `column`:
 *             - In the first byte of this key-action, these fields contain the
 *               two most significant bits of their respective values such that
 *               these bits are nonzero in *any* of `layer`, `row`, or
 *               `column`.  In subsequent bytes of this key-action, these
 *               fields contain the pair of bits to the right of the pair of
 *               bits in the previous key-action byte (the next less
 *               significant pair of bits).  If `layer`, `row`, and `column`
 *               all equal `0`, then these three fields will all equal `0`, and
 *               there will only be 1 byte written for this key-action.
 *
 *         - Example of an encoded key-action:
 *
 *               --- as a key_action_t ---
 *               pressed = false
 *               layer   = 0 b 00 00 01 00
 *               row     = 0 b 00 01 10 01
 *               column  = 0 b 00 10 00 11
 *                             |        '- least significant pair of bits
 *                             '- most significant pair of bits
 *
 *               --- in EEMEM ---
 *               byte 0 = 0 b 1 0 00 01 10
 *               byte 1 = 0 b 1 1 01 10 00
 *               byte 2 = 0 b 0 1 00 01 11
 *                            | | |  |  '- column bit pair
 *                            | | |  '- row bit pair
 *                            | | '- layer bit pair
 *                            | '- pressed / 1
 *                            '- continued
 */
#define  EEMEM_START                ((void *)OPT__EEPROM__EEPROM_MACRO__START)
#define  EEMEM_START_ADDRESS_START  (EEMEM_START               + 0)
#define  EEMEM_START_ADDRESS_END    (EEMEM_START_ADDRESS_START + 1)
#define  EEMEM_END_ADDRESS_START    (EEMEM_START_ADDRESS_END + 1)
#define  EEMEM_END_ADDRESS_END      (EEMEM_END_ADDRESS_START + 1)
#define  EEMEM_VERSION_START        (EEMEM_END_ADDRESS_END + 1)
#define  EEMEM_VERSION_END          (EEMEM_VERSION_START   + 0)
#define  EEMEM_MACROS_START         (EEMEM_VERSION_END + 1)
#define  EEMEM_MACROS_END           (EEMEM_END         - 0)
#define  EEMEM_END                  ((void *)OPT__EEPROM__EEPROM_MACRO__END)

/**                                             macros/(group) type/description
 * Aliases for valid values of the "type" field in `MACROS`
 *
 * Members:
 * - `TYPE_DELETED`
 * - `TYPE_VALID_MACRO`
 * - `TYPE_END`
 */
#define  TYPE_DELETED      0x00
#define  TYPE_VALID_MACRO  0x01
#define  TYPE_END          0xFF

// ----------------------------------------------------------------------------
// types ----------------------------------------------------------------------

/**                                              types/key_action_t/description
 * To hold everything needed to represent a single key-action (the press or
 * release of a specific key on a specific layer of the layout matrix).
 *
 * Struct members:
 * - `pressed`: Whether the key is pressed (`true`) or not (`false`)
 * - `layer`: The layer of the key, in the layout matrix
 * - `row`: The row of the key, in the layout matrix
 * - `column`: The column of the key, in the layout matrix
 *
 * Notes:
 * - Since these fields together can reference any key (on any layer)
 *   unambiguously, a `key_action_t` may also serve as a UID for a key.
 */
typedef struct {
    bool    pressed;
    uint8_t layer;
    uint8_t row;
    uint8_t column;
} key_action_t;

// ----------------------------------------------------------------------------
// variables ------------------------------------------------------------------

/**                                             variables/end_macro/description
 * The EEMEM address of the macro with `type == TYPE_END`
 */
void * end_macro;

/**                                         variables/new_end_macro/description
 * The EEMEM address of where to write the next byte of a macro in progress (or
 * `0` if no macro is in progress)
 *
 * Mnemonic:
 * - This macro will become the new `end_macro` when the macro currently being
 *   written is finalized.
 *
 * Note:
 * - This variable should be the primary indicator of whether a macro is in
 *   progress or not.
 */
void * new_end_macro;

// ----------------------------------------------------------------------------
// local functions ------------------------------------------------------------

/**                                       functions/read_key_action/description
 * Read the key-action beginning at `from` in the EEPROM
 *
 * Arguments:
 * - `from`: A pointer to the location in EEPROM from which to begin reading
 * - `k`: A pointer to the variable in which to store the key-action
 *
 * Returns:
 * - success: The number of bytes read
 *
 * Notes:
 * - See the documentation for "(group) EEMEM layout" above for a description
 *   of the layout of key-actions in EEMEM.
 */
static uint8_t read_key_action(void * from, key_action_t * k) {
    uint8_t byte;

    // handle the first byte
    // - since this byte (and no others) stores the value of `k->pressed`
    // - also, this allows us to avoid `|=` in favor of `=` for this byte
    
    byte = eeprom__read(from++);
    uint8_t read = 1;

    k->pressed = byte >> 6 & 0b01;
    k->layer   = byte >> 4 & 0b11;
    k->row     = byte >> 2 & 0b11;
    k->column  = byte >> 0 & 0b11;

    // handle all subsequent bytes
    // - we assume the stream is valid.  especially, we do not check to make
    //   sure that the key-action is no more than 4 bytes long.

    while (byte >> 7) {
        byte = eeprom__read(from++);
        read++;

        // shift up (make more significant) the bits we have so far, to make
        // room for the bits we just read
        k->layer  <<= 2;
        k->row    <<= 2;
        k->column <<= 2;

        // logical or the bits we just read into the lowest (least significant)
        // positions
        k->layer  |= byte >> 4 & 0b11;
        k->row    |= byte >> 2 & 0b11;
        k->column |= byte >> 0 & 0b11;
    }

    return read;  // success
}

/**                                      functions/write_key_action/description
 * Write the given information to a key-action beginning at `to` in the
 * EEPROM, and return the number of bytes written.
 *
 * Arguments:
 * - `to`: A pointer to the location in EEPROM at which to begin writing
 * - `k`: A pointer to the key-action to write
 * - `limit`: A pointer to the last address to which we are allowed to write
 *
 * Returns:
 * - success: The number of bytes written
 * - failure: `0`
 *
 * Warnings:
 * - Writes are not atomic: if there are 4 bytes to be written, and the first
 *   three writes succeed, the 4th may still fail.
 *
 * Notes:
 * - See the documentation for "(group) EEMEM layout" above for a description
 *   of the layout of key-actions in EEMEM.
 *
 * Implementation notes:
 * - We handle the `layer`, `row`, and `column` variables (inside `k`) as being
 *   made up of 4 pairs of bits.
 * - We deal with these bits beginning with the high (most significant) pair,
 *   and shifting left (towards the most significant end of the byte) to
 *   discard bit pairs we're done with.
 *     - This method seemed faster (i.e. generated less assembly code) when I
 *       was testing than leaving the `layer`, `row`, and `column` bytes as
 *       they were and using a variable mask (as in `k.layer & 0b11 << i*2`).
 *       It's probably worthwhile to note that I was looking at the assembly
 *       (though not closely) and function size with optimizations turned on.
 */
static uint8_t write_key_action(void * to, key_action_t * k, void * limit) {
    // ignore the bits we don't need to write
    // - if the leading two bits of all three variables are `0b00`, we don't
    //   need to write a key-action byte containing that pair of bits
    // - the maximum number of pairs of bits we can ignore is 3; the last pair
    //   (the least significant) must be written to the EEPROM regardless of
    //   its value
    // - we set `i` here (and make it global to the function) because we need
    //   to make sure to *consider writing* exactly 4 pairs of bits.  some may
    //   be skipped, some or all may be written, but the total of both must be
    //   4.

    uint8_t i = 0;

    for (; i<3 && !((k->layer|k->row|k->column) & 0xC0); i++) {
        k->layer  <<= 2;
        k->row    <<= 2;
        k->column <<= 2;
    }

    uint8_t written = 4-i;

    // write key-action bytes for all bit pairs that weren't ignored
    // - the first byte contains the value of `k->pressed`; the same position
    //   is set to `1` in all subsequent bytes
    // - all bytes except the last one written (containing the least
    //   significant bits) have their first bit set to `1`

    uint8_t byte = k->pressed << 6;

    for (; i<4; i++) {
        byte = byte | ( i<3             ) << 7
                    | ( k->layer  & 0xC0 ) >> 2
                    | ( k->row    & 0xC0 ) >> 4
                    | ( k->column & 0xC0 ) >> 6 ;

        if ( to > limit )                return 0;  // out of bounds
        if ( eeprom__write(to++, byte) ) return 0;  // write failed

        byte = 1 << 6;

        k->layer  <<= 2;
        k->row    <<= 2;
        k->column <<= 2;
    }

    return written;  // success
}

/**                                       functions/find_key_action/description
 * Find the macro remapping the given key-action (if it exists).
 *
 * Arguments:
 * - `k`: A pointer to the key-action to search for
 *
 * Returns:
 * - success: The EEMEM address of the desired macro
 * - failure: `0`
 *
 * Notes:
 * - The address `0` (or really `NULL`, which is `#define`ed to `((void *)0)`)
 *   is a valid address in the EEPROM; but because macros are not placed first
 *   in the EEPROM, we can still use it to signal nonexistence or failure.
 * - See the documentation for "(group) EEMEM layout" above for a description
 *   of the layout of macros in EEMEM.
 *
 * Implementation notes:
 * - It would be more efficient to convert the given key-action into the same
 *   binary representation as used in the EEPROM, once, and then compare that
 *   directly with the encoded key-action bytes read; but I don't think it'll
 *   have enough of an impact on performance to justify rewriting the
 *   ...key_action() functions, and it seems like this solution is a little bit
 *   cleaner (since it results in slightly fewer functions and keeps the
 *   representation of a key-function in SRAM consistent).
 */
static void * find_key_action(key_action_t * k) {
    void * current = EEMEM_MACROS_START;

    for ( uint8_t type = eeprom__read(current);
          type != TYPE_END;
          current += eeprom__read(current+1), type = eeprom__read(current) ) {

        if (type == TYPE_VALID_MACRO) {

            key_action_t k_current;
            read_key_action(current+2, &k_current);

            if (    k->pressed == k_current.pressed
                 && k->layer   == k_current.layer
                 && k->row     == k_current.row
                 && k->column  == k_current.column ) {

                return current;
            }
        }
    }

    return 0;  // key-action not found
}

/**                                     functions/find_next_deleted/description
 * Find the first deleted macro at or after the given macro.
 *
 * Arguments:
 * - `start`: The EEMEM address of the macro at which to begin searching
 *
 * Returns:
 * - success: The EEMEM address of the first deleted macro at or after `start`
 * - failure: `0` (no deleted macros were found at or after `start`)
 */
static void * find_next_deleted(void * start) {
    for ( uint8_t type = eeprom__read(start);
          type != TYPE_END;
          start += eeprom__read(start+1), type = eeprom__read(start) ) {

        if (type == TYPE_DELETED)
            return start;
    }

    return 0;  // no deleted macro found
}

/**                                  functions/find_next_nondeleted/description
 * Find the first macro at or after the given macro that is not marked as
 * deleted.
 *
 * Arguments:
 * - `start`: The EEMEM address of the macro at which to begin searching
 *
 * Returns:
 * - success: The EEMEM address of the first non-deleted macro at or after
 *   `start`
 *
 * Notes:
 * - Since the sequence of macros must end with a `TYPE_END` macro (which is,
 *   of course, not a deleted macro), this function will always find a
 *   non-deleted macro at or after the one passed.
 */
static void * find_next_nondeleted(void * start) {
    for ( uint8_t type = eeprom__read(start);
          type == TYPE_DELETED;
          start += eeprom__read(start+1), type = eeprom__read(start) );

    return start;
}

/**                                              functions/compress/description
 * Remove any gaps in the EEPROM caused by deleted macros
 *
 * Returns:
 * - success: `0`
 * - failure:
 *     - `1`: write failed; data unchanged
 *     - `2`: write failed; data lost; any macro currently being written is
 *       cancelled
 *
 * Notes:
 * - As a rough idea of the time it might take for a compress to be fully
 *   committed to EEMEM: 1024 bytes * 5 ms/byte = 5120 ms ~= 5 seconds.
 * - It's important to keep in mind that nothing will be written to the EEPROM
 *   until after this function returns (since writes are done 1 byte per
 *   keyboard scan cycle, at the end of each scan cycle).  But the code should
 *   not depend on that.
 * - It's also important to remember that this function will not be interrupted
 *   by the recording of any new key-actions for an in-progress macro (though,
 *   key-actions may be queued for writing before all `compress()` writes have
 *   been completed).
 *
 * Implementation notes:
 * - Before performing any copy operation, we invalidate the portion of the
 *   EEPROM we are going to modify by setting the first byte of it (which is,
 *   and will be, the beginning of a macro) to `TYPE_END`.  This way, as long
 *   as writes to the EEPROM are atomic (or, as long as we don't lose power
 *   while writing one of these crucial `type` bytes) the EEPROM will always be
 *   in a consistent state.
 *     - If power is lost before all writes have been committed, the portion of
 *       the EEPROM that has not yet been compressed will remain invalidated
 *       (so data will be lost, but the list of macros will not be corrupted).
 *     - If the user tries to execute a macro before all writes have been
 *       committed, and the macro is in the portion of the EEPROM that has
 *       already been compressed, it will be found as normal.  If the macro is
 *       in the portion of the EEPROM that is still being modified, it will
 *       temporarily appear not to exist.
 *     - In any case, no extra checks need to be performed, the possibility of
 *       data loss is kept very low, and the possibility of data corruption
 *       (which would, in this scheme, be undetected...) is (I think, for our
 *       purposes) vanishingly small.
 */
static uint8_t compress(void) {
    uint8_t ret;  // for function return codes (to test for errors)

    void * to_overwrite;  // the first byte with a value we don't need to keep
    void * to_compress;   // the first byte of the data we do need to keep
    void * next;          // the next macro after the data to keep (usually)

    uint8_t type;           // the type of the first macro in `to_compress`
    void *  type_location;  // the final location of this `type` byte in EEMEM

    to_overwrite = find_next_deleted(EEMEM_MACROS_START);
    if (! to_overwrite) return 0;  // success: nothing to compress

    // - here `next` is the next macro to consider keeping
    // - we could set `next = to_overwrite`, but then this would depend on
    //   writes being delayed
    next = to_overwrite + eeprom__read(to_overwrite+1);

    // invalidate the portion of the EEPROM we'll be working on
    ret = eeprom__write(to_overwrite, TYPE_END);
    if (ret) return 1;  // write failed; data unchanged

    while (next <= end_macro) {
        to_compress = find_next_nondeleted(next);

        // `next` will always be 1 byte beyond the data we wish to copy
        // - since the EEPROM is only 2^10 bytes, and pointers are 16 bits, we
        //   don't have to worry about overflow
        next = find_next_deleted(to_compress);
        if (! next) next = new_end_macro;
        if (! next) next = end_macro+1;

        // save the `type` so we can write it last
        type = eeprom__read(to_compress);
        type_location = to_overwrite;
        to_overwrite++;
        to_compress++;

        // copy the data in at most `UINT8_MAX` size chunks
        // - because the `length` argument of `eeprom__write()` is a `uint8_t`
        // - even though macros (individually) will be at most `UINT8_MAX`
        //   bytes long, the block of macros we need to save may be longer
        for ( uint16_t length = next-to_compress;
              length;
              length = next-to_compress ) {

            if (length > UINT8_MAX)
                length = UINT8_MAX;

            ret = eeprom__copy(to_overwrite, to_compress, length);
            if (ret) goto out;  // write failed; data lost
            to_overwrite += length;
            to_compress += length;
        }

        // invalidate the portion of the EEPROM we'll be working on next
        // - no need to do this if there's nothing more to compress
        if (next <= end_macro) {
            ret = eeprom__write(to_overwrite, TYPE_END);
            if (ret) goto out;  // write failed; data lost
        }

        // lastly, write the `type` we saved earlier
        // (revalidate the portion of the EEPROM we're done with)
        ret = eeprom__write(type_location, type);
        if (ret) goto out;  // write failed; data lost
    }

    // update state variables
    if (new_end_macro) {
        end_macro -= (new_end_macro-to_overwrite);
        new_end_macro = to_overwrite;
    } else {
        end_macro = to_overwrite-1;
    }

    return 0;  // success: compression finished

out:
    end_macro = type_location;
    new_end_macro = 0;
    return 2;  // write failed; data lost
}

// ----------------------------------------------------------------------------
// helper functions -----------------------------------------------------------

/**                        functions/write_key_action_for_new_macro/description
 * Write the given key-action to the next empty space in the macros block of
 * the EEPROM
 *
 * Arguments:
 * - `k`: A pointer to the key-action to write
 *
 * Returns:
 * - success: `0`
 * - failure: [other]
 *
 * Assumptions:
 * - A macro is currently in progress (i.e. `new_end_macro` is not `0`).
 *
 * Notes:
 * - We make sure to leave 1 empty byte for the end macro.
 * - We update the value of `new_end_macro` (either to indicate the bytes that
 *   were written, or to cancel the new macro if writing failed).
 */
static inline uint8_t write_key_action_for_new_macro(key_action_t * k) {
    uint8_t ret;  // for function return values

    ret = write_key_action(new_end_macro, k, EEMEM_MACROS_END-1);
    if (! ret) {
        if ( compress() ) goto out;  // compress failed (macro cancelled)

        ret = write_key_action(new_end_macro, k, EEMEM_MACROS_END-1);
        if (! ret) goto out;  // write failed again, or not enough room
    }

    new_end_macro += ret;
    return 0;

out:
    new_end_macro = 0;
    return 1;
}

/**                                functions/delete_macro_if_exists/description
 * Deletes the macro remapping the given key-action, if it exists
 *
 * Arguments:
 * - `k`: A pointer to the key-action to delete
 *
 * Returns:
 * - success: `0`
 * - failure: [other]
 */
static inline uint8_t delete_macro_if_exists(key_action_t * k) {
    void * k_location = find_key_action(k);

    if (k_location)
        if ( eeprom__write(k_location, TYPE_DELETED) )
            return 1;  // write failed

    return 0;  // success
}

// ----------------------------------------------------------------------------
// public functions -----------------------------------------------------------

/**                                    functions/eeprom_macro__init/description
 * Implementation notes:
 * - The initialization of static EEPROM values that this function is supposed
 *   to do when the EEPROM is not in a valid state (for this build of the
 *   firmware) is done in `eeprom_macro__clear_all()`.
 */
uint8_t eeprom_macro__init(void) {
    #define  TEST(address, offset, expected)                    \
        if ( eeprom__read((address)+(offset)) != (expected) )   \
            return eeprom_macro__clear_all()

    TEST( EEMEM_START_ADDRESS_START, 0, (uint16_t)EEMEM_START >> 8   );
    TEST( EEMEM_START_ADDRESS_START, 1, (uint16_t)EEMEM_START & 0xFF );

    TEST( EEMEM_END_ADDRESS_START,   0, (uint16_t)EEMEM_END >> 8     );
    TEST( EEMEM_END_ADDRESS_START,   1, (uint16_t)EEMEM_END & 0xFF   );

    TEST( EEMEM_VERSION_START,       0, VERSION );

    #undef  TEST

    // find the end macro
    void * current = EEMEM_MACROS_START;
    for ( uint8_t type = eeprom__read(current);
          type != TYPE_END;
          current += eeprom__read(current+1), type = eeprom__read(current) );

    end_macro = current;
    new_end_macro = 0;

    return 0;  // success
}

/**                             functions/eeprom_macro__record_init/description
 * Implementation notes:
 * - At minimum, for a normal macro, we will need a `type` byte, a `length`
 *   byte, and 3 key-actions (the key-action to remap, 1 press, and 1 release).
 *   Key-actions take a minimum of 1 byte, so our minimum macro will be 5
 *   bytes.
 */
uint8_t eeprom_macro__record_init( bool    pressed,
                                   uint8_t layer,
                                   uint8_t row,
                                   uint8_t column ) {

    if (new_end_macro)
        eeprom_macro__record_cancel();

    if ( end_macro + 5 > EEMEM_MACROS_END )
        return 1;  // not enough room

    key_action_t k = {
        .pressed = pressed,
        .layer   = layer,
        .row     = row,
        .column  = column,
    };

    if ( delete_macro_if_exists(&k) ) return 1;  // failure

    new_end_macro = end_macro + 2;

    return write_key_action_for_new_macro(&k);
}

/**                           functions/eeprom_macro__record_action/description
 * Implementation notes:
 * - Macros can only be `UINT8_MAX` bytes long in total.  If we don't have at
 *   least 4 bytes left before exceeding that limit (since 4 bytes is the
 *   maximum length of a key-action), we simply stop recording actions.  This
 *   is certainly not optimal behavior... but I think it'll end up being the
 *   least surprising, where our other options are to either finalize the
 *   macro, or return an error code.
 *     - If longer macros are desired, there are several ways one might modify
 *       the implementation to allow them.  The simplest method would be to
 *       make `length` a 2 byte variable.  That would reduce the number of
 *       small macros one could have, however.  Alternately, one could steal 2
 *       bits from the `type` byte, which would save space, but make things
 *       more difficult to read.  Another method would be to introduce a
 *       `TYPE_CONTINUED`, or something similar, where the data section of a
 *       macro of this type would continue the data section of the previous
 *       macro.  That would make the logic of recording macros (and playing
 *       them back) a little more complicated though.
 */
uint8_t eeprom_macro__record_action( bool    pressed,
                                     uint8_t layer,
                                     uint8_t row,
                                     uint8_t column ) {

    if (! new_end_macro)
        return 1;  // no macro in progress

    if ( new_end_macro - end_macro > UINT8_MAX - 4 )
        return 0;  // macro too long, ignoring further actions

    key_action_t k = {
        .pressed = pressed,
        .layer   = layer,
        .row     = row,
        .column  = column,
    };

    return write_key_action_for_new_macro(&k);
}

uint8_t eeprom_macro__record_finalize(void) {
    if ( eeprom__write( new_end_macro, TYPE_END ) ) goto out;
    if ( eeprom__write( end_macro+1, new_end_macro - end_macro ) ) goto out;
    if ( eeprom__write( end_macro, TYPE_VALID_MACRO ) ) goto out;

    end_macro = new_end_macro;
    new_end_macro = 0;
    return 0;

out:
    new_end_macro = 0;
    return 1;
}

uint8_t eeprom_macro__record_cancel(void) {
    new_end_macro = 0;
    return 0;
}

uint8_t eeprom_macro__play( bool    pressed,
                            uint8_t layer,
                            uint8_t row,
                            uint8_t column ) {

    key_action_t k = {
        .pressed = pressed,
        .layer   = layer,
        .row     = row,
        .column  = column,
    };

    void * k_location = find_key_action(&k);
    if (! k_location) return 1;  // macro does not exist

    uint8_t length = eeprom__read(k_location+1);
    length -= 2;
    k_location += 2;
    while (length) {
        uint8_t read = read_key_action(k_location, &k);
        kb__layout__exec_key_layer( k.pressed, k.layer, k.row, k.column );
        length -= read;
        k_location += read;
    }

    return 0;
}

bool eeprom_macro__exists( bool    pressed,
                           uint8_t layer,
                           uint8_t row,
                           uint8_t column ) {

    key_action_t k = {
        .pressed = pressed,
        .layer   = layer,
        .row     = row,
        .column  = column,
    };

    return find_key_action(&k);
}

uint8_t eeprom_macro__clear( bool    pressed,
                             uint8_t layer,
                             uint8_t row,
                             uint8_t column ) {

    key_action_t k = {
        .pressed = pressed,
        .layer   = layer,
        .row     = row,
        .column  = column,
    };

    return delete_macro_if_exists(&k);
}

/**                               functions/eeprom_macro__clear_all/description
 * Implementation notes:
 * - Since the `eeprom__...` functions only modify data when necessary, we
 *   don't need to worry here about excessive EEPROM wear when writing; so it's
 *   easier to initialize all static EEPROM values every time this function
 *   runs than to do most of these initializations as a special case in
 *   `eeprom_macro__init()`.
 */
uint8_t eeprom_macro__clear_all(void) {
    #define  WRITE(address, offset, value)  \
        if (eeprom__write( (address)+(offset), (value) )) return 1

    WRITE( EEMEM_START_ADDRESS_START, 0, (uint16_t)EEMEM_START >> 8   );
    WRITE( EEMEM_START_ADDRESS_START, 1, (uint16_t)EEMEM_START & 0xFF );

    WRITE( EEMEM_END_ADDRESS_START,   0, (uint16_t)EEMEM_END >> 8     );
    WRITE( EEMEM_END_ADDRESS_START,   1, (uint16_t)EEMEM_END & 0xFF   );

    WRITE( EEMEM_VERSION_START,       0, VERSION  );

    WRITE( EEMEM_MACROS_START,        0, TYPE_END );

    #undef  WRITE

    end_macro = EEMEM_MACROS_START;
    new_end_macro = 0;

    return 0;
}

