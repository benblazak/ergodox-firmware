/* ----------------------------------------------------------------------------
 * linked list
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include <stdlib.h>
#include "lib/data-types.h"

#include "linked-list.h"


// convenience macros (undefined later)
#define _NEW_STRUCT_POINTER(type, name)	\
	struct type * name = (struct type *) malloc(sizeof(struct type))


struct linked_list * linked_list_new(void) {
	_NEW_STRUCT_POINTER(linked_list, list);
	if (!list) return NULL;

	list->head = NULL;
	list->tail = NULL;

	list->number_of_elements = 0;
	return list;
}

struct linked_list * linked_list_add_head(
		struct linked_list * list,
		LINKED_LIST_DATA_TYPE data ) {

	_NEW_STRUCT_POINTER(linked_list_node, node);
	if (!node) return NULL;

	node->data = data;
	node->next = list->head;
	list->head = node;
	if (list->number_of_elements == 0)
		list->tail = node;

	list->number_of_elements++;
	return list;
}

struct linked_list * linked_list_add_tail(
		struct linked_list * list,
		LINKED_LIST_DATA_TYPE data ) {

	_NEW_STRUCT_POINTER(linked_list_node, node);
	if (!node) return NULL;

	node->data = data;
	node->next = NULL;
	if (list->number_of_elements == 0)
		list->head = node;
	else
		list->tail->next = node;
	list->tail = node;

	list->number_of_elements++;
	return list;
}

LINKED_LIST_DATA_TYPE linked_list_pop_head(struct linked_list * list) {
	if (list->number_of_elements == 0)
		return 0;

	struct linked_list_node node = {
		.data = list->head->data,
		.next = list->head->next
	};

	free(list->head);

	if (list->number_of_elements == 1) {
		list->head = NULL;
		list->tail = NULL;
	} else {
		list->head = node.next;
	}

	list->number_of_elements--;
	return node.data;
}

// note: this function is inefficient for singly linked lists: it has O(n) time
// instead of O(1) time like most of the other functions.  but it's not needed
// for implementing stacks or queues, so i don't anticipate it being used all
// that much.  it's here for completeness.
LINKED_LIST_DATA_TYPE linked_list_pop_tail(struct linked_list * list) {
	if (list->number_of_elements == 0)
		return 0;

	struct linked_list_node node = {
		.data = list->tail->data,
		.next = list->tail->next
	};

	free(list->tail);

	if (list->number_of_elements == 1) {
		list->head = NULL;
		list->tail = NULL;
	} else {
		list->tail = list->head;
		for (uint8_t i=2; i<(list->number_of_elements); i++)
			list->tail = list->tail->next;
		list->tail->next = NULL;
	}

	list->number_of_elements--;
	return node.data;
}

LINKED_LIST_DATA_TYPE linked_list_read(
			struct linked_list * list,
			uint8_t position ) {

	if (position < 1 || position > (list->number_of_elements))
		return 0;

	struct linked_list_node * node = list->head;
	for (uint8_t i=1; i<position; i++)
		node = node->next;

	return node->data;
}

struct linked_list * linked_list_copy(struct linked_list * list) {
	_NEW_STRUCT_POINTER(linked_list, copy);

	for (uint8_t i=1; i<=(list->number_of_elements); i++)
		linked_list_add_tail(copy, linked_list_read(list, i));

	return copy;
}


// note: this is implemented inefficiently (using ...pop_head(), which does
// extra work).  but that makes things simpler, and i don't anticipate using it
// all that often.
void linked_list_free(struct linked_list * list) {
	while ((list->number_of_elements) > 0)
		linked_list_pop_head(list);

	free(list);
}


// convenience macros (undefined here)
#undef _NEW_STRUCT_POINTER

