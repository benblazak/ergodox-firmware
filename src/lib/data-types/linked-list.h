/* ----------------------------------------------------------------------------
 * linked list : exports
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef DATA_TYPES_LINKED_LIST_h
	#define DATA_TYPES_LINKED_LIST_h

	#include <stdint.h>

	// --------------------------------------------------------------------

	// default data type for the list
	#ifndef LINKED_LIST_DATA_TYPE
		#define LINKED_LIST_DATA_TYPE uint8_t
	#endif

	// --------------------------------------------------------------------

	// structs
	struct linked_list_node {
		LINKED_LIST_DATA_TYPE data;
		struct linked_list_node * next;
	};

	struct linked_list {
		uint8_t length;  // 'uint8_t' to save memory
		struct linked_list_node * head;
		struct linked_list_node * tail;
	};

	// typedefs
	typedef  struct linked_list        linked_list_t;
	typedef  struct linked_list_node   linked_list_node_t;

	// functions
	#define  _list_t  linked_list_t
	#define  _data_t  LINKED_LIST_DATA_TYPE
	_list_t * linked_list_new    (void);
	_list_t * linked_list_insert (_list_t * list, int index, _data_t data);
	_data_t   linked_list_peek   (_list_t * list, int index);
	_data_t   linked_list_pop    (_list_t * list, int index);
	_list_t * linked_list_copy   (_list_t * list);
	void      linked_list_free   (_list_t * list);
	#undef _list_t
	#undef _data_t

#endif

