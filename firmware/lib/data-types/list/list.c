/* ----------------------------------------------------------------------------
 * Copyright (c) 2012, 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Implements the list type in "../list.h"
 */


#include <stddef.h>
#include <stdlib.h>
#include "../list.h"

// ----------------------------------------------------------------------------

#define  list_t  list__list_t
#define  node_t  list__node_t

// since we'll be casting to `node_t *` a lot
#define  N(name)  ((node_t *) name)

// ----------------------------------------------------------------------------

void * list__insert(list_t * list, int8_t index, void * node) {
    // if `node` does not exist
    if (!node)
        return NULL;

    list->length++;

    if (list->length == 1) {
        // insert as only node (no others exist yet)
        list->head = node;
        list->tail = node;
        N(node)->next = NULL;

    } else {
        index %= list->length;

        if (index == 0) {
            // insert as first node
            N(node)->next = list->head;
            list->head = node;

        } else if (index == list->length-1) {
            // insert as last node
            N(list->tail)->next = node;
            list->tail = node;
            N(node)->next = NULL;

        } else {
            // insert as other node
            node_t * previous = list->head;
            for (uint8_t i=1; i<index; i++)
                previous = previous->next;
            N(node)->next = previous->next;
            previous->next = node;
        }
    }

    return node;
}

void * list__peek(list_t * list, int8_t index) {
    // if no nodes exist
    if (list->length == 0)
        return NULL;

    index %= list->length;

    // if last node
    if (index == list->length-1)
        return list->tail;

    // else
    node_t * node = list->head;
    for (uint8_t i=0; i<index; i++)
        node = N(node)->next;
    return node;
}

void * list__pop_index(list_t * list, int8_t index) {
    // if no nodes exist
    if (list->length == 0)
        return NULL;

    index %= list->length;

    node_t * node;

    if (index == 0) {
        // pop first node
        node = list->head;
        list->head = N(node)->next;

    } else {
        // find the `index-1`th node
        node_t * previous = list->head;
        for (uint8_t i=1; i<index; i++)
            previous = previous->next;

        // if last node
        if (index == list->length-1)
            list->tail = previous;

        // pop the node at `index`
        node = previous->next;
        previous->next = N(node)->next;
    }

    list->length--;

    return node;
}

void * list__pop_node(list_t * list, void * node) {
    // if `node` does not exist, or no nodes exist
    if (!node || list->length == 0)
        return NULL;

    node_t * previous = list->head;

    if (node == list->head) {
        // pop first node
        list->head = N(node)->next;

    } else {
        // find the previous node (if `node` is in `list`)
        while (previous->next != node) {
            previous = previous->next;
            if (!previous)
                return NULL;  // `node` not found
        }

        // if last node
        if (node == list->tail)
            list->tail = previous;

        // pop the node
        previous->next = N(node)->next;
    }

    list->length--;

    return node;
}

void * list__pop_node_next(list_t * list, void * node ) {
    if (!list__pop_node(list, node))
        return NULL;  // `node` was not in `list`

    node_t * next = N(node)->next;
    free(node);

    return next;
}

void list__free_all(list_t * list) {
    node_t * node;
    while (list->head) {
        node = list->head;
        list->head = node->next;
        free(node);
    }
}

