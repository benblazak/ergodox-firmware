/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Implements the eeprom-macro functionality defined in "../eeprom-macro.h" for
 * the ATMega32U4
 *
 *
 * Implementation notes:
 *
 * - The default state (the "erased" state) of this EEPROM is all `1`s, which
 *   makes setting a byte to `0xFF` easier and faster in hardware than zeroing
 *   it.  This is reflected in some of our choices for default values, and
 *   such.
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
 *   meant to be used for *temporary* macros - so, with the risk of power loss
 *   during a critical time being fairly low, and the consequence of (detected)
 *   data corruption hopefully more of an annoyance than anything else, I
 *   decided the effort (and extra EEMEM usage) wasn't worth it.
 */


#include <stddef.h>
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

#if EEMEM_END - EEMEM_START < 300
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
 *
 * EEMEM sections:
 *
 * - START_ADDRESS:
 *     - byte 0: MSB of `EEMEM_START`
 *     - byte 1: LSB of `EEMEM_START`
 *
 * - END_ADDRESS:
 *     - byte 0: MSB of `EEMEM_END`
 *     - byte 1: LSB of `EEMEM_END`
 *
 * - VERSION:
 *     - byte 0:
 *         - This byte will all be set to `VERSION` as the last step of
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
 *             - `key-action` 0: the key-action which this macro remaps
 *                 - See below for a description of the bytes making up a
 *                   key-action
 *             - `key-action` 1...: (optional) the key-actions to which
 *               `key-action` 0 is remapped
 *         - byte 0: `type == TYPE_END`
 *             - byte 1...: (optional) undefined
 *
 *     - The last key-action in this series will have `type == TYPE_END`.
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
 *           | continued |   n/a   | layer |  row  | column |
 *           '----------------------------------------------'
 *
 *         - `continued`:
 *             - `1`: The next byte is part of this key-action
 *             - `0`: The next byte is not part of this key-action (i.e. this
 *                    is the last byte in this key-action)
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
 *         - Example of an encoded key-action (where `*` means "undefined"):
 *
 *               --- as a key_action_t ---
 *               pressed = true
 *               layer   = 0 b 00 00 01 00
 *               row     = 0 b 00 01 10 01
 *               column  = 0 b 00 10 00 11
 *                             |        '- least significant pair of bits
 *                             '- most significant pair of bits
 *
 *               --- in EEMEM ---
 *               byte 0 = 0 b 1 1 00 01 10
 *               byte 1 = 0 b 1 * 01 10 00
 *               byte 2 = 0 b 0 * 00 01 11
 *                            | | |  |  '- column bit pair
 *                            | | |  '- row bit pair
 *                            | | '- layer bit pair
 *                            | '- pressed / n/a
 *                            '- continued
 *
 *
 * Notes:
 * - `START_ADDRESS` and `END_ADDRESS` are written as part of our effort to
 *   make sure that the assumptions in place when writing the data don't shift
 *   (undetected) by the time it gets read.  Either of these values could
 *   change, legitimately, without `VERSION` being incremented, but it's
 *   important that any two builds of the firmware that deal with this section
 *   of the EEPROM have the same values for each.
 */
#define  EEMEM_START                ((void *)OPT__EEPROM__EEPROM_MACRO__START)
#define  EEMEM_START_ADDRESS_START  EEMEM_START               + 0
#define  EEMEM_START_ADDRESS_END    EEMEM_START_ADDRESS_START + 1
#define  EEMEM_END_ADDRESS_START    EEMEM_START_ADDRESS_END + 1
#define  EEMEM_END_ADDRESS_END      EEMEM_END_ADDRESS_START + 1
#define  EEMEM_VERSION_START        EEMEM_END_ADDRESS_END + 1
#define  EEMEM_VERSION_END          EEMEM_VERSION_START   + 0
#define  EEMEM_MACROS_START         EEMEM_VERSION_END + 1
#define  EEMEM_MACROS_END           EEMEM_END         - 0
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
// local functions ------------------------------------------------------------

/**                                       functions/read_key_action/description
 * Read and return the key-action beginning at `*from` in the EEPROM, and
 * advance `*from` to one byte past the key-action.
 *
 * Arguments:
 * - `from`: A pointer to a pointer to the location in EEPROM from which to
 *   begin reading
 *
 * Returns:
 * - success: The key-action, as a `key_action_t`
 *
 * Notes:
 * - See the documentation for "(group) EEMEM layout" above for a description
 *   of the layout of key-actions in EEMEM.
 */
key_action_t read_key_action(void ** from) {
    uint8_t byte;

    // handle the first byte
    // - since this byte (and no others) stores the value of `k.pressed`
    // - also, this allows us to avoid `|=` in favor of `=` for this byte
    
    byte = eeprom__read((*from)++);

    key_action_t k = {
        .pressed = byte >> 6 & 0b01,
        .layer   = byte >> 4 & 0b11,
        .row     = byte >> 2 & 0b11,
        .column  = byte >> 0 & 0b11,
    };

    // handle all subsequent bytes
    // - we assume the stream is valid.  especially, we do not check to make
    //   sure that the key-action is no more than 4 bytes long.

    while (byte >> 7) {
        byte = eeprom__read((*from)++);

        // shift up (make more significant) the bits we have so far, to make
        // room for the bits we just read
        k.layer  <<= 2;
        k.row    <<= 2;
        k.column <<= 2;

        // logical or the bits we just read into the lowest (least significant)
        // positions
        k.layer  |= byte >> 4 & 0b11;
        k.row    |= byte >> 2 & 0b11;
        k.column |= byte >> 0 & 0b11;
    }

    return k;  // success
}

/**                                      functions/write_key_action/description
 * Write the given information to a key-action beginning at `*to` in the
 * EEPROM, and advance `*to` to one byte past the newly written key-action.
 *
 * Arguments:
 * - `to`: A pointer to a pointer to the location in EEPROM at which to begin
 *   writing
 * - `k`: The key-action to write
 *
 * Returns:
 * - success: `0`
 * - failure: [other]
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
uint8_t write_key_action(void ** to, key_action_t k) {

    // - we need to leave room after this macro (and therefore after this
    //   key-action) for the `TYPE_END` byte
    if ((*to) > EEMEM_END-4)
        return 1;  // error: might not be enough space

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

    for (; i<3 && !((k.layer|k.row|k.column) & 0xC0); i++) {
        k.layer  <<= 2;
        k.row    <<= 2;
        k.column <<= 2;
    }

    // write key-action bytes for all bit pairs that weren't ignored
    // - the first byte contains the value of `k.pressed`
    // - all bytes except the last one written (containing the least
    //   significant bits) have their first bit set to `1`

    uint8_t byte = (k.pressed ? 1 : 0) << 6;

    for (; i<4; i++) {
        byte = byte | ( i<3      ? 1 : 0 ) << 7
                    | ( k.layer  & 0xC0  ) >> 2
                    | ( k.row    & 0xC0  ) >> 4
                    | ( k.column & 0xC0  ) >> 6 ;
        eeprom__write((*to)++, byte);
        byte = 0;

        k.layer  <<= 2;
        k.row    <<= 2;
        k.column <<= 2;
    }

    return 0;  // success
}

// TODO: rewriting (yet again) - stopped here
#if 0

// ----------------------------------------------------------------------------
// variables in EEMEM ---------------------------------------------------------

/**                                                variables/eeprom/description
 * The layout of this library's data in the EEPROM
 *
 * Struct members:
 * - `meta`: For keeping track of layout metadata
 *     - `version`: The version of this layout (`[8]` for fault tolerance and
 *       write balancing)
 * - `table`: To help in quickly returning if the UID we're searching for does
 *   not exist
 *     - `rows`: The number of rows this table has
 *     - `columns`: The number of columns this table has
 *     - `data`:
 *         - For any `eeprom_macro__uid_t uid`
 *             - If `uid.layer > 7`, this table doesn't tell whether a macro
 *               exists for the UID or not
 *             - Otherwise, `! ( (eeprom.table.data[uid.row][uid.column]
 *               >> uid.layer) & 1 )` indicates whether a macro exists with the
 *               given UID (`true`) or not (`false`)
 *             - Note that the expression above will return `true` if
 *               `uid.layer > 7`
 *             - Note that the expression above implies that we are using `1`
 *               bits for `false`
 * - `macros`: To hold a block of memory for storing macros
 *     - `length`: The number of bytes allocated to `macros.data`
 *     - `data`: A (non-padded) list of macros, where a macro (in EEMEM) is
 *         - 1 byte: `type`
 *             - as defined in `enum type`
 *         - 1 byte: `length`
 *             - the number of bytes in the entire macro (i.e.  the number of
 *               bytes to skip over, if one had a pointer to the `type` byte of
 *               this macro, in order to reach the `type` byte of the next
 *               macro)
 *         - (variable length): `key_action`
 *             - as defined in `read_key_action()`
 *             - this is the key action that is being remapped
 *         - (list of 0 or more)
 *             - (variable length): `key_action`
 *                 - as defined in `read_key_action()`
 *                 - these are the key actions to be performed instead of the
 *                   one being remapped
 *
 *
 * Notes:
 *
 * - The struct must be `packed` and `aligned(1)`, or we risk allocating more
 *   than `OPT__EEPROM_MACRO__EEPROM_SIZE` bytes.  This should be the default
 *   when compiling with `avr-gcc`, but it's important to emphasize that we
 *   depend on it.
 *
 * - We keep track of `table.rows`, `table.columns`, and `macros.length`, in
 *   addition to `header.version`, because they all effect the precise layout
 *   of the persistent data; if any of them is different, special handling is
 *   required at the least, and usually the stored data will be unusable.
 */
struct eeprom {
    struct meta {
        uint8_t version[8];
    } meta;

    struct table {
        uint8_t rows;
        uint8_t columns;
        uint8_t data[OPT__KB__ROWS][OPT__KB__COLUMNS];
    } table;

    struct macros {
        uint16_t length;
        uint8_t data[MACROS_LENGTH];
    } macros;

} __attribute__((packed, aligned(1))) eeprom EEMEM;

// ----------------------------------------------------------------------------
// variables in SRAM ----------------------------------------------------------

static void * current_macro;
uint8_t       current_macro_length;

// ----------------------------------------------------------------------------
// TODO:
//
// - the calling function need not ignore layer shift keys, or any other keys.
//
// - use little endian order for the multi-byte encoding. explain why (since
//   utf-8 is big endian)
//
// - 255 bytes (so, on average, about 100 keystrokes = 200 key actions) should
//   be enough for a macro, i think.  `length` can be 1 byte, and count the
//   total number of bytes (including `type` and `length`, and anything else)
//
// - need to write a function to read, and another to write, multi-byte key
//   actions
//
// - so for now, we have
//     - macro = `type` `length` uid key_action*
//     - uid = key_action
//     - key_action =
//         - 1 bit  : are the fields in this byte extended by the next?
//         - 1 bit  : `pressed`
//         - 2 bits : `layer`
//         - 2 bits : `row`
//         - 2 bits : `column`
//
// - need to write `kb__layout__exec_key_layer()` (or something)
//
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// local functions ------------------------------------------------------------

/**                                              functions/find_uid/description
 * Find the macro with the given `uid`
 *
 * Arguments:
 * - `uid`: The UID of the macro we're trying to find
 *
 * Returns:
 * - success: The EEMEM address of the beginning of the macro
 * - failure: `NULL`
 *
 * Notes:
 * - `NULL` is `#define`ed to `((void *)0)`, which for the EEPROM is a valid
 *   memory address; but because `struct eeprom` does not place
 *   `eeprom.macros.data` first in memory, `NULL` is guaranteed to be before
 *   the beginning of that array, and is therefore usable as a signal that the
 *   macro we're looking for does not exist.
 *
 * Implementation notes:
 * - Using `memcmp()` to compare two structs is bad practice in general (what
 *   if there's uninitialized padding in the struct?); but I'm doing it here
 *   because we're already trusting the binary layout of the struct when we
 *   store and retrieve it from EEMEM, and it saves writing another function
 *   just for that.
 * - It should not be strictly necessary for us to check whether we're
 *   iterating over the bounds of `eeprom.macros.data`, since the list of
 *   macros is supposed to be terminated in a well defined way.  But we may as
 *   well, just to be safer :)
 */
static void * find_uid(eeprom_macro__uid_t uid) {
    // if `eeprom.table.data` indicates that the macro does not exist
    if ( (eeprom.table.data[uid.row][uid.column] >> uid.layer) & 1 )
        return NULL;

    // otherwise the macro may exist: we must search for it
    for ( uint8_t * p = &eeprom.macros.data[0];
                    p < &eeprom.macros.data[MACROS_LENGTH-3]; ) {

        header_t header;
        eeprom__block_read(&header, p, sizeof(header));

        switch (header.type) {
            case HEADER_TYPE_VALID:
                if ( ! memcmp(&uid, &header.uid, sizeof(uid)) )
                    return p;

                // (do not break)

            case HEADER_TYPE_DELETED:
                p += sizeof(header_t) + header.length * sizeof(action_t);
                break;

            // `HEADER_TYPE_END` or invalid value
            default:
                // (no more macros to search)
                return NULL;
        }
    }

    // macro does not exist
    return NULL;
}

/**                                     functions/find_next_deleted/description
 * Find the first deleted macro at or after the macro at the given position
 *
 * Arguments:
 * - `start`: The address (in EEMEM) of the first byte of the header of the
 *   macro at which to begin searching
 *
 * Returns:
 * - success: The address (in EEMEM) of the of the beginning of the first
 *   deleted macro found at or after `start`
 * - failure: `NULL` (no deleted macros found)
 */
static void * find_next_deleted(void * start) {
    for ( uint8_t * p = start;
                    p < &eeprom.macros.data[MACROS_LENGTH-3]; ) {

        uint8_t type   = eeprom__read(p);
        uint8_t length = eeprom__read(p+1);

        switch (type) {
            case HEADER_TYPE_VALID:
                p += sizeof(header_t) + length * sizeof(action_t);
                break;

            case HEADER_TYPE_DELETED:
                return p;

            // `HEADER_TYPE_END` or invalid value
            default:
                // (no more macros to search)
                return NULL;
        }
    }

    // no deleted macros found
    return NULL;
}

/**                                              functions/compress/description
 * Compress `macros.data`
 *
 * Shift all macros towards index `0`, overwriting the areas previously
 * occupied by deleted macros.
 */
static void compress(void) { return;
    // TODO: this whole thing... just starting.

    uint8_t * current_deleted = find_next_deleted(&eeprom.macros.data[0]);

    uint8_t * next_deleted = find_next_deleted(current_deleted);
    if (! next_deleted) next_deleted = macros_free_begin;
}

// ----------------------------------------------------------------------------
// public functions -----------------------------------------------------------

#endif  // 0
uint8_t eeprom_macro__init(void) { return 0; }
#if 0

uint8_t eeprom_macro__record_init(void) { return 0;
}

uint8_t eeprom_macro__record_keystroke( bool    pressed,
                                        uint8_t row,
                                        uint8_t column ) { return 0;
}

uint8_t eeprom_macro__record_finalize(eeprom_macro__uid_t index) { return 0;
}

uint8_t eeprom_macro__exists(eeprom_macro__uid_t index) {
    return (bool) find_uid(index);
}

uint8_t eeprom_macro__play(eeprom_macro__uid_t index) { return 0;
}

void eeprom_macro__clear(eeprom_macro__uid_t index) { return;
}

void eeprom_macro__clear_all(void) { return;
}
#endif  // 0

