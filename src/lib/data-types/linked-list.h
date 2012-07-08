/* ----------------------------------------------------------------------------
 * linked list : exports
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef LINKED_LIST_h
	#define LINKED_LIST_h

	#include "lib/data-types.h"


	// default data type for the list
	#ifndef LINKED_LIST_DATA_TYPE
		#define LINKED_LIST_DATA_TYPE uint8_t
	#endif


	// structs
	struct linked_list_node {
		LINKED_LIST_DATA_TYPE data;
		struct linked_list_node * next;
	};

	struct linked_list {
		uint8_t number_of_elements;
		struct linked_list_node * head;
		struct linked_list_node * tail;
	};

	// typedefs
	typedef  struct linked_list       linked_list_t;
	typedef  struct linked_list_node  linked_list_node_t;

	// functions
	#define  _list_t  linked_list_t
	#define  _data_t  LINKED_LIST_DATA_TYPE
	_list_t * linked_list_new        (void);
	_list_t * linked_list_add_head   (_list_t * list, _data_t data);
	_list_t * linked_list_add_tail   (_list_t * list, _data_t data);
	_data_t   linked_list_pop_head   (_list_t * list);
	_data_t   linked_list_pop_tail   (_list_t * list);
	_data_t   linked_list_read       (_list_t * list, uint8_t position);
	_list_t * linked_list_insert     ( _list_t * list,
	                                   uint8_t position,
	                                   _data_t data );
	_list_t * linked_list_copy       (_list_t * list);
	void      linked_list_free       (_list_t * list);

	_list_t * linked_list_slice_copy ( _list_t * list,
	                                   uint8_t start_position,
	                                   uint8_t end_position );
	_list_t * linked_list_slice      ( _list_t * list,
	                                   uint8_t start_position,
	                                   uint8_t end_position );
	_list_t * linked_list_remove     (_list_t * list, uint8_t position);
	uint8_t   linked_list_find_first (_list_t * list, _data_t data);
	_list_t * linked_list_reverse    (_list_t * list);
	#undef _list_t
	#undef _data_t

#endif

