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

list__list_t * list__new(void) {
    list__list_t * list = malloc( sizeof(list__list_t) );
    if (!list) return NULL;

    list->head = NULL;
    list->tail = NULL;
    list->length = 0;

    return list;
}

void * list__insert(list__list_t * list, int8_t index, uint8_t size) {
    list__node_t * node = malloc(size);
    if (!node) return NULL;

    list->length++;

    if (list->length == 1) {
        // insert as only node (no others exist yet)
        list->head = node;
        list->tail = node;
        node->next = NULL;

    } else {
        index %= list->length;

        if (index == 0) {
            // insert as first node
            node->next = list->head;
            list->head = node;

        } else if (index == list->length-1) {
            // insert as last node
            list->tail->next = node;
            list->tail = node;
            node->next = NULL;

        } else {
            // insert as other node
            list__node_t * previous = list->head;
            for (uint8_t i=1; i<index; i++)
                previous = previous->next;
            node->next = previous->next;
            previous->next = node;
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
    list__node_t * node = list->head;
    for (uint8_t i=0; i<index; i++)
        node = node->next;
    return node;
}

void * list__pop__no_free(list__list_t * list, int8_t index) {
    // if no nodes exist
    if (list->length == 0)
        return NULL;

    index %= list->length;

    list__node_t * node;

    if (index == 0) {
        // pop first node
        node = list->head;
        list->head = node->next;

    } else {
        // find the `index-1`th node
        list__node_t * previous = list->head;
        for (uint8_t i=1; i<index; i++)
            previous = previous->next;

        // if last node
        if (index == list->length-1)
            list->tail = previous;

        // pop the node at `index`
        node = previous->next;
        previous->next = node->next;
    }

    list->length--;

    return node;
}

void list__free(list__list_t * list) {
    list__node_t * node;
    while (list->head) {
        node = list->head;
        list->head = list->head->next;
        free(node);
    }
    free(list);
}

