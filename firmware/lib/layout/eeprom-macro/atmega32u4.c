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
 * Warnings:
 *
 * - This library's functionality is meant to be used for recording and playing
 *   back *temporary* macros.  Permanent macros should be assigned to a key in
 *   the layout directly.  Macros created using this library may be difficult
 *   (or practically impossible) to retrieve and back up, and may be
 *   invalidated by changes to this library in future versions of the firmware.
 *   They may also become corrupted if the keyboard looses power at an
 *   inopportune time.  If invalidated or corrupted, macros will (probably) be
 *   erased without warning.
 *
 *
 * Implementation warnings:
 *
 * - One cannot trust the binary layout of bit-fields: the order of the fields
 *   (among other things) is implementation defined, and [can change]
 *   (http://avr.2057.n7.nabble.com/Bit-field-packing-order-changed-between-avrgcc-implementations-td19193.html),
 *   even between different versions of the same compiler.  The risk is
 *   probably low when the compiler and architecture are both so specific, so I
 *   depend on their binary layout anyway, but it's definitely something to be
 *   aware of.
 *
 *
 * Implementation notes:
 *
 * - The default state (the "erased" state) of this EEPROM is all `1`s, which
 *   makes setting a byte to `0xFF` easier and faster in hardware than zeroing
 *   it.  This is reflected in some of our choices for default values, and
 *   such.
 *
 * - In avr-gcc, multi-byte data types are allocated with the least significant
 *   bit occupying the lowest address.
 *
 * - For a long time, I was going to try to make this library robust in the
 *   event of power loss, but in the end I decided not to.  This feature is
 *   meant to be used for *temporary* macros - permanent macros really should
 *   be assigned to a key in the layout code directly, instead of using this
 *   library's functionality after the firmware has already been loaded - so,
 *   with the risk of power loss being fairly low, and the consequence of
 *   (detected) eeprom-macro corruption hopefully more of an annoyance than
 *   anything else, I decided the effort (and extra EEMEM usage) wasn't worth
 *   it.
 */


#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <avr/eeprom.h>
#include "../../../../firmware/keyboard.h"
#include "../../../../firmware/lib/eeprom.h"
#include "../eeprom-macro.h"

// ----------------------------------------------------------------------------

/**                           macros/OPT__EEPROM_MACRO__EEPROM_SIZE/description
 * Implementation notes:
 * - The ATMega32U4 has 1024 bytes of internal EEPROM total
 */
#if OPT__EEPROM_MACRO__EEPROM_SIZE > 1024
    #error "OPT__EEPROM_MACRO__EEPROM_SIZE must be <= 1024"
#endif

// ----------------------------------------------------------------------------
// macros ---------------------------------------------------------------------

/**                                                  macros/VERSION/description
 * The version number of `struct eeprom`
 *
 * Assignments:
 * - 0x00: Reserved: EEPROM not yet initialized, or in inconsistent state
 * - 0x01: First version
 * - ... : (not yet assigned)
 * - 0xFF: Reserved: EEPROM not yet initialized, or in inconsistent state
 */
#define  VERSION  0x01

/**                                                        macros/MACROS_LENGTH
 * The number of items in `eeprom.macros.data`, stored persistently in
 * `eeprom.macros.length`
 */
#define  MACROS_LENGTH  ( OPT__EEPROM_MACRO__EEPROM_SIZE            \
                          - sizeof(uint16_t)  /* for `length` */    \
                          - sizeof(struct meta)                     \
                          - sizeof(struct table) )                  \
                        / sizeof(uint8_t) 

/**                                       macros/(enum) header_type/description
 * Valid values for `header_t.type`, describing what kind of data follows
 *
 * Members:
 * - `HEADER_TYPE_DELETED = 0x00`: This macro has been deleted (only `length`
 *   is valid)
 * - `HEADER_TYPE_VALID`: This macro is valid
 * - `HEADER_TYPE_END = 0xFF`: This header marks the end of the list (nothing
 *   follows)
 */
enum header_type {
    HEADER_TYPE_DELETED = 0x00,
    HEADER_TYPE_VALID,
    HEADER_TYPE_END = 0xFF,
};

// ----------------------------------------------------------------------------
// types ----------------------------------------------------------------------

/**                                                  types/header_t/description
 * To describe the data that follows (most likely a sequence of `action_t`s,
 * making this the beginning of a macro)
 *
 * Struct members:
 * - type: (see description for `header_type` enum)
 * - `length`: the number of `action_t`s that follow
 * - `uid`: a Unique IDentifier for the macro
 */
typedef struct {
    uint8_t             type;
    uint8_t             length;
    eeprom_macro__uid_t uid;
} header_t;

/**                                                  types/action_t/description
 * To describe the "press" or "release" of a key when recording or playing back
 * a macro
 *
 * Notes:
 * - We reuse the `...uid_t` type for convenience and consistency.  Only the
 *   `pressed`, `row`, and `column` fields are relevant, since these are what
 *   will be passed to `kb__layout__exec_key()` when playing back the macro.
 *   `layer` will be ignored.
 */
typedef  eeprom_macro__uid_t  action_t;

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
 *     - `data`: A list of "macro"s, where a "macro" is a `header_t`
 *       followed by zero or more `action_t`s.  The list contains no padding.
 *       It is terminated by a macro with `header_t.type == HEADER_TYPE_END`.
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

// TODO: names for the pointers to where to write the next new macro header,
// and next recorded action
// - macros_next_free_header, macros_next_free_action
static void * macros_free_begin;  // TODO: needs a better name?

// ----------------------------------------------------------------------------
// TODO:
//
// - should we define macros as
//     - length
//         - 0x00 => end
//     - uid
//         - 0xFF => deleted
//     - actions(s)
//         - 1 bit : indicate extended action (read next action, and combine,
//           to reach higher layers, rows, and columns)
//         - 1 bit : pressed
//         - 3 bits : row
//         - 3 bits : column
// - maybe we could define UIDs similar to the actions described above?
//   multi-byte encodings ftw! lol.  like utf-8...
//
// ----------------------------------------------------------------------------
//
// - actually, yes, we could store UIDs as
//     - 1 bit : indicate whether the next byte extends this one (i.e. for
//       every field in the next byte, take it, shift it up, and concatenate it
//       with the corresponding field in this byte to obtain the final value.
//       if the next byte has its extended bit set too, then the byte after
//       that extends each field further, etc.)
//     - 1 bit : pressed (this field is ignored in extended bytes)
//     - 2 bits : layer
//     - 2 bits : row
//     - 2 bits : column
//
// - then we could use the same format for actions (and use the same read
//   function for both)
//
// - then we would probably want to make a function
//   `kb__layout__exec_key_layer()` or some such, to execute a key on a
//   specific layer.  `kb__layout__exec_key()` could look up the top layer in
//   the stack, and call the more specific function.
//
// - recording the layer, and specifying it explicitly when playing back macros
//   might eliminate some problems with defining a macro for a key on a
//   different layer than the ones it presses, or on a different layer than the
//   key indicating to start recording.  this way, we could just ignore all
//   layer shift keys when recording (or... the exec_key function could, since
//   i think that's where functions from this library will be called).
//   otherwise, if we just record (pressed, row, column) tuples, the logic will
//   have to be more complicated...
//
// - still need to consider though: do we really want to give up the `type`
//   byte?  it would much more easily allow for extensions in the future if we
//   kept it, and it would eliminate the need to steal values from `length`.
//
// - actually, if we multi-byte encode the uid, we do need to keep `type`,
//   because otherwise, how will we indicate a deleted macro (where the length
//   still needs to be valid)?
//
// - we'll need to write a read and a write function for (pressed, layer, row,
//   column) tuples
//
// - also, under this scheme, `length` will have to be the number of bytes,
//   since there will be no quick way to know how many bytes there are (to skip
//   over to get to the next macro) if we specify the number of actions.
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

uint8_t eeprom_macro__init(void) { return 0;
}

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

