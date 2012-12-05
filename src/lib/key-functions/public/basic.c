/* ----------------------------------------------------------------------------
 * key functions : basic : code
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include "../../../main.h"
#include "../../../keyboard/layout.h"
#include "../public.h"
#include "../private.h"

// ----------------------------------------------------------------------------

#define  MAX_LAYER_PUSH_POP_FUNCTIONS  10

// ----------------------------------------------------------------------------

// convenience macros
#define  LAYER         main_arg_layer
#define  LAYER_OFFSET  main_arg_layer_offset
#define  ROW           main_arg_row
#define  COL           main_arg_col
#define  IS_PRESSED    main_arg_is_pressed
#define  WAS_PRESSED   main_arg_was_pressed

// ----------------------------------------------------------------------------

/*
 * [name]
 *   Press|Release
 *
 * [description]
 *   Generate a normal keypress or keyrelease
 */
void kbfun_press_release(void) {
	uint8_t keycode = kb_layout_get(LAYER, ROW, COL);
	_kbfun_press_release(IS_PRESSED, keycode);
}

/*
 * [name]
 *   Toggle
 *
 * [description]
 *   Toggle the key pressed or unpressed
 */
void kbfun_toggle(void) {
	uint8_t keycode = kb_layout_get(LAYER, ROW, COL);

	if (_kbfun_is_pressed(keycode))
		_kbfun_press_release(false, keycode);
	else
		_kbfun_press_release(true, keycode);
}

/*
 * [name]
 *   Transparent
 *
 * [description]
 *   Execute the key that would have been executed if the current layer was not
 *   active
 */
void kbfun_transparent(void) {
	LAYER_OFFSET++;
	LAYER = main_layers_peek(LAYER_OFFSET);
	main_layers_pressed[ROW][COL] = LAYER;
	main_exec_key();
}


/* ----------------------------------------------------------------------------
 * layer push/pop functions
 * ------------------------------------------------------------------------- */

static layer_ids[MAX_LAYER_PUSH_POP_FUNCTIONS];

static void layer_push(uint8_t local_id) {
	uint8_t keycode = kb_layout_get(LAYER, ROW, COL);
	main_layers_pop_id(layer_ids[local_id]);
	layer_ids[local_id] = main_layers_push(keycode);
}

static void layer_pop(uint8_t local_id) {
	main_layers_pop_id(layer_ids[local_id]);
	layer_ids[local_id] = 0;
}

/*
 * [name]
 *   Layer push #1
 *
 * [description]
 *   Push a layer element containing the layer value specified in the keymap to
 *   the top of the stack, and record the id of that layer element
 */
void kbfun_layer_push_1(void) {
	layer_push(1);
}

/*
 * [name]
 *   Layer pop #1
 *
 * [description]
 *   Pop the layer element created by the corresponding "layer push" function
 *   out of the layer stack (no matter where it is in the stack, without
 *   touching any other elements)
 */
void kbfun_layer_pop_1(void) {
	layer_pop(1);
}

/*
 * [name]
 *   Layer push #2
 *
 * [description]
 *   Push a layer element containing the layer value specified in the keymap to
 *   the top of the stack, and record the id of that layer element
 */
void kbfun_layer_push_2(void) {
	layer_push(2);
}

/*
 * [name]
 *   Layer pop #2
 *
 * [description]
 *   Pop the layer element created by the corresponding "layer push" function
 *   out of the layer stack (no matter where it is in the stack, without
 *   touching any other elements)
 */
void kbfun_layer_pop_2(void) {
	layer_pop(2);
}

/*
 * [name]
 *   Layer push #3
 *
 * [description]
 *   Push a layer element containing the layer value specified in the keymap to
 *   the top of the stack, and record the id of that layer element
 */
void kbfun_layer_push_3(void) {
	layer_push(3);
}

/*
 * [name]
 *   Layer pop #3
 *
 * [description]
 *   Pop the layer element created by the corresponding "layer push" function
 *   out of the layer stack (no matter where it is in the stack, without
 *   touching any other elements)
 */
void kbfun_layer_pop_3(void) {
	layer_pop(3);
}

/*
 * [name]
 *   Layer push #4
 *
 * [description]
 *   Push a layer element containing the layer value specified in the keymap to
 *   the top of the stack, and record the id of that layer element
 */
void kbfun_layer_push_4(void) {
	layer_push(4);
}

/*
 * [name]
 *   Layer pop #4
 *
 * [description]
 *   Pop the layer element created by the corresponding "layer push" function
 *   out of the layer stack (no matter where it is in the stack, without
 *   touching any other elements)
 */
void kbfun_layer_pop_4(void) {
	layer_pop(4);
}

/*
 * [name]
 *   Layer push #5
 *
 * [description]
 *   Push a layer element containing the layer value specified in the keymap to
 *   the top of the stack, and record the id of that layer element
 */
void kbfun_layer_push_5(void) {
	layer_push(5);
}

/*
 * [name]
 *   Layer pop #5
 *
 * [description]
 *   Pop the layer element created by the corresponding "layer push" function
 *   out of the layer stack (no matter where it is in the stack, without
 *   touching any other elements)
 */
void kbfun_layer_pop_5(void) {
	layer_pop(5);
}

/*
 * [name]
 *   Layer push #6
 *
 * [description]
 *   Push a layer element containing the layer value specified in the keymap to
 *   the top of the stack, and record the id of that layer element
 */
void kbfun_layer_push_6(void) {
	layer_push(6);
}

/*
 * [name]
 *   Layer pop #6
 *
 * [description]
 *   Pop the layer element created by the corresponding "layer push" function
 *   out of the layer stack (no matter where it is in the stack, without
 *   touching any other elements)
 */
void kbfun_layer_pop_6(void) {
	layer_pop(6);
}

/*
 * [name]
 *   Layer push #7
 *
 * [description]
 *   Push a layer element containing the layer value specified in the keymap to
 *   the top of the stack, and record the id of that layer element
 */
void kbfun_layer_push_7(void) {
	layer_push(7);
}

/*
 * [name]
 *   Layer pop #7
 *
 * [description]
 *   Pop the layer element created by the corresponding "layer push" function
 *   out of the layer stack (no matter where it is in the stack, without
 *   touching any other elements)
 */
void kbfun_layer_pop_7(void) {
	layer_pop(7);
}

/*
 * [name]
 *   Layer push #8
 *
 * [description]
 *   Push a layer element containing the layer value specified in the keymap to
 *   the top of the stack, and record the id of that layer element
 */
void kbfun_layer_push_8(void) {
	layer_push(8);
}

/*
 * [name]
 *   Layer pop #8
 *
 * [description]
 *   Pop the layer element created by the corresponding "layer push" function
 *   out of the layer stack (no matter where it is in the stack, without
 *   touching any other elements)
 */
void kbfun_layer_pop_8(void) {
	layer_pop(8);
}

/*
 * [name]
 *   Layer push #9
 *
 * [description]
 *   Push a layer element containing the layer value specified in the keymap to
 *   the top of the stack, and record the id of that layer element
 */
void kbfun_layer_push_9(void) {
	layer_push(9);
}

/*
 * [name]
 *   Layer pop #9
 *
 * [description]
 *   Pop the layer element created by the corresponding "layer push" function
 *   out of the layer stack (no matter where it is in the stack, without
 *   touching any other elements)
 */
void kbfun_layer_pop_9(void) {
	layer_pop(9);
}

/*
 * [name]
 *   Layer push #10
 *
 * [description]
 *   Push a layer element containing the layer value specified in the keymap to
 *   the top of the stack, and record the id of that layer element
 */
void kbfun_layer_push_10(void) {
	layer_push(10);
}

/*
 * [name]
 *   Layer pop #10
 *
 * [description]
 *   Pop the layer element created by the corresponding "layer push" function
 *   out of the layer stack (no matter where it is in the stack, without
 *   touching any other elements)
 */
void kbfun_layer_pop_10(void) {
	layer_pop(10);
}

/* ----------------------------------------------------------------------------
 * ------------------------------------------------------------------------- */

