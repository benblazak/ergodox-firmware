/* ----------------------------------------------------------------------------
 * linked list : exports
 *
 * Includes aliases to treat the list as a queue or stack.
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef LINKED_LIST_h
	#define LINKED_LIST_h

	#include "lib/data-types.h"


	// default list data type
	#ifndef LINKED_LIST_DATA_TYPE
		#define LINKED_LIST_DATA_TYPE uint8_t
	#endif


	// structs
	struct linked_list_node {
		LINKED_LIST_DATA_TYPE data;
		struct linked_list_node * next;
	};

	struct linked_list{
		uint8_t number_of_elements;
		struct linked_list_node * head;
		struct linked_list_node * tail;
	};

	// functions
	struct linked_list * linked_list_new(void);
	struct linked_list * linked_list_add_head(
			struct linked_list * list,
			LINKED_LIST_DATA_TYPE data );
	struct linked_list * linked_list_add_tail(
			struct linked_list * list,
			LINKED_LIST_DATA_TYPE data );
	LINKED_LIST_DATA_TYPE linked_list_pop_head(struct linked_list * list);
	LINKED_LIST_DATA_TYPE linked_list_pop_tail(struct linked_list * list);
	LINKED_LIST_DATA_TYPE linked_list_read(
			struct linked_list * list,
			uint8_t position );
	struct linked_list * linked_list_copy(struct linked_list * list);
	void linked_list_free(struct linked_list * list);


	// typedefs, for user code
	typedef struct linked_list * linked_list_t;
	typedef struct linked_list_node * linked_list_node_t;

	// aliases, for user code
	#define list_t        linked_list_t
	#define list_new      linked_list_new
	#define list_push     linked_list_add_head
	#define list_append   linked_list_add_tail
	#define list_pop      linked_list_pop_head
	#define list_pop_tail linked_list_pop_tail
	#define list_read     linked_list_read
	#define list_copy     linked_list_copy
	#define list_free     linked_list_free

	#define queue_t      list_t
	#define queue_new    list_new
	#define queue_append list_append
	#define queue_pop    list_pop
	#define queue_read   list_read
	#define queue_copy   list_copy
	#define queue_free   list_free

	#define stack_t    list_t
	#define stack_new  list_new
	#define stack_push list_push
	#define stack_pop  list_pop
	#define stack_read list_read
	#define stack_copy list_copy
	#define stack_free list_free


#endif

