/* ----------------------------------------------------------------------------
 * stack : exports
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef DATA_TYPES_STACK_h
	#define DATA_TYPES_STACK_h

	// for "linked-list.h"
	#ifdef STACK_DATA_TYPE
		#define LINKED_LIST_DATA_TYPE STACK_DATA_TYPE
	#endif

	#include "./linked-list.h"

	// --------------------------------------------------------------------

	#define stack_new              linked_list_new
	#define stack_push(list, data) linked_list_insert(list, 0, data)
	#define stack_peek             linked_list_peek
	#define stack_pop(list)        linked_list_pop(list, 0)
	#define stack_copy             linked_list_copy
	#define stack_free             linked_list_free

	// --------------------------------------------------------------------

	typedef  linked_list_t *       stack_t;
	typedef  linked_list_node_t *  stack_node_t;

#endif

