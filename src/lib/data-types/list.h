/* ----------------------------------------------------------------------------
 * list : exports
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef DATA_TYPES_LIST_h
	#define DATA_TYPES_LIST_h

	// for "linked-list.h"
	#ifdef LIST_DATA_TYPE
		#define LINKED_LIST_DATA_TYPE LIST_DATA_TYPE
	#endif

	#include "./linked-list.h"

	// --------------------------------------------------------------------

	#define list_new    linked_list_new
	#define list_insert linked_list_insert
	#define list_peek   linked_list_peek
	#define list_pop    linked_list_pop
	#define list_copy   linked_list_copy
	#define list_free   linked_list_free

	// --------------------------------------------------------------------

	typedef  linked_list_t *       list_t;
	typedef  linked_list_node_t *  list_node_t;

#endif

