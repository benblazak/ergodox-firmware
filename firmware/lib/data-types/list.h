/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * An interface to a simple linked-list that can be used to implement lists,
 * queues, stacks, and things
 *
 * Prefix: `list__`
 *
 *
 * Implementation notes:
 *
 * - All functions that accept an `index` should set `index %= list->length`
 *   before using it.  This will make all passed indices valid.  It will also
 *   provide a convenient way to reference the last element of a list, by
 *   passing `-1` as the index (as in Python).
 */


#ifndef ERGODOX_FIRMWARE__FIRMWARE__LIB__DATA_TYPES__LIST__H
#define ERGODOX_FIRMWARE__FIRMWARE__LIB__DATA_TYPES__LIST__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


#include <stdint.h>

// ----------------------------------------------------------------------------

typedef struct list__node_t {
    struct list__node_t * next;
} list__node_t;

typedef struct list__list_t {
    list__node_t * head;
    list__node_t * tail;
    uint8_t        length;
} list__list_t;

// ----------------------------------------------------------------------------

list__list_t * list__new          (void);
void *         list__insert       ( list__list_t * list,
                                    int8_t         index,
                                    uint8_t        size );
void *         list__peek         (list__list_t * list, int8_t index);
void *         list__pop__no_free (list__list_t * list, int8_t index);
void           list__free         (list__list_t * list);


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__FIRMWARE__LIB__DATA_TYPES__LIST__H



// ============================================================================
// === documentation ==========================================================
// ============================================================================


// ----------------------------------------------------------------------------
// typedefs -------------------------------------------------------------------
// ----------------------------------------------------------------------------

// === list__node_t ===
/**                                           typedefs/list__node_t/description
 * The type of a "node", for the purposes of this library
 *
 * Full node types should be defined in the using '.c' or '.h' file, with
 * something like
 *
 *     typedef struct {
 *         list__node_t _private;
 *         uint8_t      data;
 *     } node_t;
 *
 * The functions that return pointers to nodes will return `void *` pointers,
 * so functions in the using '.c' file also need to cast these return values to
 * the appropriate type before use.
 */

// === list__list_t ===
/**                                           typedefs/list__list_t/description
 * Simple struct to define and keep track of our list
 */


// ----------------------------------------------------------------------------
// functions ------------------------------------------------------------------
// ----------------------------------------------------------------------------

// === list__new() ===
/**                                             functions/list__new/description
 * Allocate a new (empty) list
 *
 * Returns:
 * - success: A pointer to the new list
 * - failure: `NULL`
 */

// === list__insert() ===
/**                                          functions/list__insert/description
 * Insert `node` at position `index % list->length`
 *
 * Arguments:
 * - `list`: A pointer to the list to be operated on
 * - `index`: An `int8_t` indicating the position the new node will occupy
 * - `size`: The size of the full node type (as in `sizeof(node_t)`) defined in
 *   the using '.c' or '.h' file, so we know how much memory to allocate
 *
 * Returns:
 * - success: A `void *` pointer to the new node
 * - failure: `NULL`
 *
 * Warning:
 * - For any given list, the `size` passed to this function should always be
 *   the same.
 *
 * Caution:
 * - Initialization of the data to be stored in the node is the calling
 *   function's responsibility.
 */

// === list__peek() ===
/**                                            functions/list__peek/description
 * Return a pointer to the node at position `index % list->length`
 *
 * Arguments:
 * - `list`: A pointer to the list to be operated on
 * - `index`: An `int8_t` indicating the position of the node to peek at
 *
 * Returns:
 * - success: A `void *` pointer to the node at position `index % list->length`
 * - failure: `NULL`
 */

// === list__pop__no_free() ===
/**                                    functions/list__pop__no_free/description
 * Return a pointer to the node at position `index % list->length`, and remove
 * the node from the list
 *
 * Warning:
 * - Does not free the node's memory - this is the calling function's
 *   responsibility.  If you want to pop the node and free its memory without
 *   looking at it, call `free( list__pop__no_free( node ) )`.
 *
 * Arguments:
 * - `list`: A pointer to the list to be operated on
 * - `index`: An `int8_t` indicating the position of the node to pop
 *
 * Returns:
 * - success: A `void *` pointer to the node at position `index % list->length`
 * - failure: `NULL`
 */

// === list__free() ===
/**                                            functions/list__free/description
 * Free all node pointers in `list`, then free `list`
 *
 * Arguments:
 * - `list`: A pointer to the list to be operated on
 */

