/* ----------------------------------------------------------------------------
 * linked list : code
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include <stdlib.h>
#include "lib/data-types/common.h"

#include "linked-list.h"


// local macros (undefined later)
#define  _NEW_POINTER(type, name)  type * name = (type *) malloc(sizeof(type))
#define  _list_t                   linked_list_t
#define  _node_t                   linked_list_node_t
#define  _data_t                   LINKED_LIST_DATA_TYPE


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

	list->length = 0;
	return list;
}

/*
 * insert()
 *
 * Arguments
 * - index: the index of the position that the new node will occupy.  if index
 *   is negative, we set index += length (as in Python).  so:
 *     -  0 => the first node in the list
 *     -  1 => the second node in the list
 *     - -1 => the last node in the list
 *     - -2 => the second from the last node in the list
 *   - out of bounds positions wrap around, so:
 *     -  [length]   =>  0 => the first node in the list
 *     - -[length+1] => -1 => the last node in the list
 *
 * Returns
 * - success: the pointer to the list that was passed
 * - failure: NULL
 *
 * Notes
 * - in this function, 'list->length' is incremented before the index is
 *   calculated|used, so that we have a consistent way to think of adding an
 *   element to the end of the list
 */
_list_t * linked_list_insert(_list_t * list, int index, _data_t data) {
	_NEW_POINTER(_node_t, node);
	if (!node) return NULL;

	list->length++;

	node->data = data;

	if (list->length == 1) {
		// insert as only node (no others exist yet)
		list->head = node;
		list->tail = node;
		node->next = NULL;
	} else {
		// find positive, in-bounds index
		index = index % list->length;
		if (index < 0)
			index += list->length;

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
			_node_t * previous = list->head;
			for (int i=1; i<index; i++)
				previous = previous->next;
			node->next = previous->next;
			previous->next = node;
		}
	}

	return list;
}

/*
 * peek()
 *
 * Arguments
 * - index: [see 'insert()']
 *
 * Returns
 * - success: the data field of the node at the given index
 * - failure: (_data_t) 0
 */
_data_t linked_list_peek(_list_t * list, int index) {
	// if: no nodes exist
	if (list->length == 0)
		return (_data_t) 0;

	// find positive, in-bounds index
	index = index % list->length;
	if (index < 0)
		index += list->length;

	// if: last node
	if (index == list->length-1)
		return list->tail->data;

	// else
	_node_t * node = list->head;
	for (int i=0; i<index; i++)
		node = node->next;
	return node->data;
}

/*
 * pop()
 *
 * Arguments
 * - index: [see 'insert()']
 *
 * Returns
 * - success: the data field of the node at the given index
 * - failure: (_data_t) 0
 */
_data_t linked_list_pop(_list_t * list, int index) {
	// if: no nodes exist
	if (list->length == 0)
		return (_data_t) 0;

	// find positive, in-bounds index
	index = index % list->length;
	if (index < 0)
		index += list->length;

	// vars
	_data_t data;
	_node_t * node;

	if (index == 0) {
		// pop first node
		data = list->head->data;
		node = list->head;
		list->head = node->next;
	} else {
		// find the index-1'th node
		_node_t * previous;
		previous = list->head;
		for (int i=1; i<index; i++)
			previous = previous->next;

		// if: last node
		if (index == list->length-1)
			list->tail = previous;

		// pop the node at index
		data = previous->next->data;
		node = previous->next;
		previous->next = node->next;
	}

	free(node);

	list->length--;
	return data;
}

/*
 * copy()
 *
 * Returns
 * - success: a new pointer to a (deep) copy of the list that was passed
 * - failure: NULL
 */
_list_t * linked_list_copy(_list_t * list) {
	_list_t * copy = linked_list_new();
	if (!copy) return NULL;

	bool error;
	_node_t * node = list->head;
	for (int i=0; i<(list->length); i++) {
		error = ! linked_list_insert(copy, -1, node->data);
		if (error) {
			linked_list_free(copy);
			return NULL;
		}
		node = node->next;
	}

	return copy;
}

/*
 * free()
 * - Free the memory allocated to all the nodes, then free the memory allocated
 *   to the list.
 */
void linked_list_free(_list_t * list) {
	_node_t * node;
	for (int i=0; i<(list->length); i++) {
		node = list->head;
		list->head = list->head->next;
		free(node);
	}
	free(list);
}


// local macros (undefined here)
#undef _NEW_POINTER
#undef _list_t
#undef _node_t
#undef _data_t

