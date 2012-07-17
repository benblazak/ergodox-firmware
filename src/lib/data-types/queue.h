/* ----------------------------------------------------------------------------
 * queue : exports
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef DATA_TYPES_QUEUE_h
	#define DATA_TYPES_QUEUE_h

	#ifdef QUEUE_DATA_TYPE
		#define LINKED_LIST_DATA_TYPE QUEUE_DATA_TYPE
	#endif
	#include "linked-list.h"

	typedef  linked_list_t *       queue_t;
	typedef  linked_list_node_t *  queue_node_t;

	#define queue_new                linked_list_new
	#define queue_append(list, data) linked_list_insert(list, -1, data)
	#define queue_peek               linked_list_peek
	#define queue_pop(list)          linked_list_pop(list, 0)
	#define queue_copy               linked_list_copy
	#define queue_free               linked_list_free

#endif

