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

// since we'll be casting to type `list__node_t *` a lot
#define  N(name)  ((list__node_t *)name)

// ----------------------------------------------------------------------------

list__list_t * list__new(void) {
    list__list_t * list = malloc( sizeof(list__list_t) );
    if (!list) return NULL;

    list->head = NULL;
    list->tail = NULL;
    list->length = 0;

    return list;
}

void * list__insert(list__list_t * list, int8_t index, void * node) {
    if (!node) return NULL;

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
            void * previous = list->head;
            for (uint8_t i=1; i<index; i++)
                previous = N(previous)->next;
            N(node)->next = N(previous)->next;
            N(previous)->next = node;
        }
    }

    return node;
}

void * list__peek(list__list_t * list, int8_t index) {
    // if no nodes exist
    if (list->length == 0)
        return NULL;

    index %= list->length;

    // if last node
    if (index == list->length-1)
        return list->tail;

    // else
    void * node = list->head;
    for (uint8_t i=0; i<index; i++)
        node = N(node)->next;
    return node;
}

void * list__pop_index(list__list_t * list, int8_t index) {
    // if no nodes exist
    if (list->length == 0)
        return NULL;

    index %= list->length;

    void * node;

    if (index == 0) {
        // pop first node
        node = list->head;
        list->head = N(node)->next;

    } else {
        // find the `index-1`th node
        void * previous = list->head;
        for (uint8_t i=1; i<index; i++)
            previous = N(previous)->next;

        // if last node
        if (index == list->length-1)
            list->tail = previous;

        // pop the node at `index`
        node = N(previous)->next;
        N(previous)->next = N(node)->next;
    }

    list->length--;

    return node;
}

void * list__pop_node(list__list_t * list, void * node) {
    // if `node` is `NULL` or no nodes exist
    if (!node || !list->head)
        return NULL;

    void * previous = list->head;

    if (node == list->head) {
        // pop first node
        list->head = N(node)->next;

    } else {
        // find the previous node (if `node` is in `list`)
        while (N(previous)->next != node) {
            previous = N(previous)->next;
            if (!previous)
                return NULL;  // `node` not found
        }

        // if last node
        if (node == list->tail)
            list->tail = previous;

        // pop the node
        N(previous)->next = N(node)->next;
    }

    list->length--;

    return node;
}

void * list__pop_node_next(list__list_t * list, void * node) {
    if (!list__pop_node(list, node))
        return NULL;

    void * next = N(node)->next;
    free(node);

    return next;
}

void list__free(list__list_t * list) {
    if (list) {
        void * node;
        while (list->head) {
            node = list->head;
            list->head = N(list->head)->next;
            free(node);
        }
        free(list);
    }
}

