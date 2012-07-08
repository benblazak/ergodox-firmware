/* ----------------------------------------------------------------------------
 * linked list
 *
 * Notes:
 * - When 'position' is used, it referes to the position of the node in the
 *   list, not the node's offset.  E.g. the node with position == 1 is the
 *   first node in the list.
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include <stdlib.h>
#include "lib/data-types.h"

#include "linked-list.h"


// local macros (undefined later)
#define  _NEW_POINTER(type, name)  type * name = (type *) malloc(sizeof(type))
#define  _list_t  linked_list_t
#define  _node_t  linked_list_node_t
#define  _data_t  LINKED_LIST_DATA_TYPE


/*
 * new()
 *
 * Returns
 * - success: a pointer to a new linked list
 * - failure: NULL
 */
_list_t * linked_list_new(void) {
	_NEW_POINTER(_list_t, list);
	if (!list) return NULL;

	list->head = NULL;
	list->tail = NULL;

	list->number_of_elements = 0;
	return list;
}

/*
 * add_head()
 *
 * Returns
 * - success: the pointer to the list that was passed
 * - failure: NULL
 */
_list_t * linked_list_add_head(_list_t * list, _data_t data) {
	_NEW_POINTER(_node_t, node);
	if (!node) return NULL;

	node->data = data;
	node->next = list->head;
	list->head = node;
	if (list->number_of_elements == 0)
		list->tail = node;

	list->number_of_elements++;
	return list;
}

/*
 * add_tail()
 *
 * Returns
 * - success: the pointer to the list that was passed
 * - failure: NULL
 */
_list_t * linked_list_add_tail(_list_t * list, _data_t data) {
	_NEW_POINTER(_node_t, node);
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

/*
 * pop_head()
 *
 * Returns
 * - success: the data element of the first node of the list
 * - failure: (_data_t) 0
 */
_data_t linked_list_pop_head(_list_t * list) {
	if (list->number_of_elements == 0)
		return (_data_t) 0;

	_node_t node = {
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

/*
 * pop_tail()
 *
 * Returns
 * - success: the data element of the last node of the list
 * - failure: (_data_t) 0
 *
 * Note
 * - This function is inefficient for singly linked lists: it has O(n) time
 *   instead of O(1) time like most of the other functions.  But it's not
 *   needed for implementing stacks or queues, so i don't anticipate it being
 *   used all that much.  It's here for completeness.
 */
_data_t linked_list_pop_tail(_list_t * list) {
	if (list->number_of_elements == 0)
		return (_data_t) 0;

	_node_t node = {
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

/*
 * read()
 *
 * Returns
 * - success: the data element at the given position
 * - failure: (_data_t) 0
 */
_data_t linked_list_read(_list_t * list, uint8_t position) {
	if (position < 1 || position > (list->number_of_elements))
		return (_data_t) 0;

	_node_t * node = list->head;
	for (uint8_t i=1; i<position; i++)
		node = node->next;

	return node->data;
}

/*
 * insert()
 * - Insert a new node containing the given data such that it occupies the
 *   given position in the list.
 *
 * Returns
 * - success: the pointer to the list that was passed
 * - failure: NULL
 */
_list_t * linked_list_insert(_list_t * list, _data_t data, uint8_t position) {
	if (position < 1 || position > (list->number_of_elements)+1)
		return NULL;

	_NEW_POINTER(_node_t, new);
	if (!new) return NULL;

	_node_t * prev = list->head;
	for (uint8_t i=0; i<position; i++)
		prev = prev->next;

	new->data = data;
	new->next = prev->next;
	prev->next = new;

	list->number_of_elements++;
	return list;
}

/*
 * copy()
 *
 * Returns
 * - success: a new pointer to a copy of the list who's pointer was passed
 * - failure: NULL
 */
_list_t * linked_list_copy(_list_t * list) {
	_NEW_POINTER(_list_t, copy);
	if (!copy) return NULL;

	for (uint8_t i=1; i<=(list->number_of_elements); i++)
		linked_list_add_tail(copy, linked_list_read(list, i));

	return copy;
}

/*
 * free()
 * - Free the memory allocated to all the nodes, then free the memory allocated
 *   to the list.
 *
 * Note
 * - This is implemented inefficiently (using pop_head(), which does extra
 *   work).  But that makes things simpler, and i don't anticipate using it all
 *   that often.
 */
void linked_list_free(_list_t * list) {
	while ((list->number_of_elements) > 0)
		linked_list_pop_head(list);

	free(list);
}

/*
 * slice_copy()
 * - Return the (copied) sublist
 *
 * Arguments
 * - start_position:
 *   - the position of the first element to include in the slice
 *   - or '0' for the beginning of the list
 * - end_position:
 *   - the position of the last element to include in the slice
 *   - or '0' for the end of the list
 *
 * Returns
 * - success: a copy of the portion of the list indicated
 * - failure: NULL
 */
_list_t * linked_list_slice_copy (
		_list_t * list,
		uint8_t start_position,
		uint8_t end_position ) {

	if ( start_position > end_position ||
	     end_position > (list->number_of_elements) )
		return NULL;

	if (start_position == 0)
		start_position = 1;
	if (end_position == 0)
		end_position = list->number_of_elements;

	_NEW_POINTER(_list_t, shallow_slice);
	if (!shallow_slice) return NULL;

	shallow_slice->number_of_elements = end_position - start_position + 1;
	shallow_slice->head = list->head;
	for (uint8_t i=1; i<start_position; i++)
		shallow_slice->head = shallow_slice->head->next;
	shallow_slice->tail = shallow_slice->head;
	for (uint8_t i=1; i<(shallow_slice->number_of_elements); i++)
		shallow_slice->tail = shallow_slice->tail->next;

	return linked_list_copy(shallow_slice);
}

/*
 * slice()
 */
_list_t * linked_list_slice (
		_list_t * list,
		uint8_t start_position,
		uint8_t end_position ) {
	// TODO
}

/*
 * remove()
 */
_list_t * linked_list_remove(_list_t * list, uint8_t position) {
	// TODO
}

/*
 * find_first()
 */
uint8_t linked_list_find_first(_list_t * list, _data_t data) {
	// TODO
}

/*
 * reverse()
 */
_list_t * linked_list_reverse(_list_t * list) {
	// TODO
}


// local macros (undefined here)
#undef _NEW_POINTER
#undef _list_t
#undef _node_t
#undef _data_t

