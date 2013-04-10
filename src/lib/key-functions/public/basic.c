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
	if (!main_arg_trans_key_pressed)
		main_arg_any_non_trans_key_pressed = true;
	kbfun_press_release_preserve_sticky();
}

/*
 * [name]
 *   Press|Release and preserve top layer sticky key state
 *
 * [description]
 *   Generate a normal keypress or keyrelease
 *   While basing the sticky key state transition on whether
 *    kbfun_press_release() was called after kbfun_transparent() generally
 *    works in practice, it is not always the desired behavior. One of the
 *    benefits of sticky keys is avoiding key chording, so we want to make sure
 *    that standard modifiers do not interrupt the sticky key cycle. Use
 *    kbfun_press_release_preserve_sticky() if you want to define a standard
 *    modifier key (shift, control, alt, gui) on the sticky layer instead of
 *    defining the key to be transparent for the layer.
 */
void kbfun_press_release_preserve_sticky(void) {
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
	main_arg_trans_key_pressed = true;
	LAYER_OFFSET++;
	LAYER = main_layers_peek(LAYER_OFFSET);
	main_layers_pressed[ROW][COL] = LAYER;
	main_exec_key();
}


/* ----------------------------------------------------------------------------
 * layer push/pop functions
 * ------------------------------------------------------------------------- */

// While there are only MAX_LAYER_PUSH_POP_FUNCTIONS number of layer functions,
//  there are 1 + MAX_LAYER_PUSH_POP_FUNCTIONS layer ids because we still have
//  layer 0 even if we will never have a push or pop function for it
static uint8_t layer_ids[1 + MAX_LAYER_PUSH_POP_FUNCTIONS];

static void layer_push(uint8_t local_id) {
	uint8_t keycode = kb_layout_get(LAYER, ROW, COL);
	main_layers_pop_id(layer_ids[local_id]);
	// Only the topmost layer on the stack should be in sticky once state, pop
	//  the top layer if it is in sticky once state
	uint8_t topSticky = main_layers_peek_sticky(0);
	if (topSticky == eStickyOnceDown || topSticky == eStickyOnceUp) {
		main_layers_pop_id(main_layers_peek(0));
	}
	layer_ids[local_id] = main_layers_push(keycode, eStickyNone);
}

static void layer_sticky(uint8_t local_id) {
	uint8_t keycode = kb_layout_get(LAYER, ROW, COL);
	if (IS_PRESSED) {
		uint8_t topLayer = main_layers_peek(0);
		uint8_t topSticky = main_layers_peek_sticky(0);
		main_layers_pop_id(layer_ids[local_id]);
		if (topLayer == local_id) {
			if (topSticky == eStickyOnceUp)
				layer_ids[local_id] = main_layers_push(keycode, eStickyLock);
		}
		else
		{
			// only the topmost layer on the stack should be in sticky once state
			if (topSticky == eStickyOnceDown || topSticky == eStickyOnceUp) {
				main_layers_pop_id(layer_ids[topLayer]);
			}
			layer_ids[local_id] = main_layers_push(keycode, eStickyOnceDown);
			// this should be the only place we care about this flag being cleared
			main_arg_any_non_trans_key_pressed = false;
		}
	}
	else
	{
		uint8_t topLayer = main_layers_peek(0);
		uint8_t topSticky = main_layers_peek_sticky(0);
		if (topLayer == local_id) {
			if (topSticky == eStickyOnceDown) {
				// When releasing this sticky key, pop the layer always
				main_layers_pop_id(layer_ids[local_id]);
				if (!main_arg_any_non_trans_key_pressed) {
					// If no key defined for this layer (a non-transparent key)
					//  was pressed, push the layer again, but in the
					//  StickyOnceUp state
					layer_ids[local_id] = main_layers_push(keycode, eStickyOnceUp);
				}
			}
		}
	}
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
 *   Layer sticky cycle #1
 *
 * [description]
 *  This function gives similar behavior to sticky keys for modifiers available
 *   on most operating systems. It is considered an accessibility feature
 *   because it alleviates the user from having to hold down modifiers while
 *   pressing a key to produce the modified key function. It is useful for fast
 *   touch typing because you can avoid chording motions which both strain your
 *   hands and take your hands out of home-row position while pressing normal
 *   alpha keys.
 *  This function emulates the 3-state behavior which is default on OS X and
 *   optional in Windows where the modifier cycles between Off->Once->Locked
 *   states. This is particularly handy for symbol layers where you typically
 *   only type one symbol before you want to return to unmodified typing (layer
 *   0), e.g. 'if (condition) { a = "b" + "c"; }'. If you assign a symbol layer
 *   to a thumb key as a layer sticky cycle, you can type the entire line of
 *   code without taking your hands out of home row position and you do not need
 *   to toggle off the layer after each symbol is pressed, only immediately
 *   before keying the symbol.
 *  The exact behavior of the layer sticky cycle function is defined as follows
 *   for each state:
 *  1) One time down (set on key press) - The layer was not active and the key
 *      has been pressed but not yet released. The layer is pushed in the one
 *      time down state. 
 *  2) One time up (set on key release) - The layer was active when the layer
 *      sticky key was released. If a key on this layer (not set to
 *      transparent) was pressed before the key was released, the layer will be
 *      popped. If a non-transparent key was not pressed, the layer is popped
 *      and pushed again in the one time up state.
 *  3) Locked (set on key press) - The layer was active and in the one time up
 *      state when the layer sticky key was pressed again. The layer will be
 *      popped if the function is invoked on a subsequent keypress.
 */
void kbfun_layer_sticky_1  (void) {
	layer_sticky(1);
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
 *   Layer sticky cycle #2
 *
 * [description]
 *   See the description of kbfun_layer_sticky_1()
 */
void kbfun_layer_sticky_2  (void) {
	layer_sticky(2);
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
 *   Layer sticky cycle #3
 *
 * [description]
 *   See the description of kbfun_layer_sticky_1()
 */
void kbfun_layer_sticky_3  (void) {
	layer_sticky(3);
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
 *   Layer sticky cycle #4
 *
 * [description]
 *   See the description of kbfun_layer_sticky_1()
 */
void kbfun_layer_sticky_4  (void) {
	layer_sticky(4);
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
 *   Layer sticky cycle #5
 *
 * [description]
 *   See the description of kbfun_layer_sticky_1()
 */
void kbfun_layer_sticky_5  (void) {
	layer_sticky(5);
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
 *   Layer sticky cycle #6
 *
 * [description]
 *   See the description of kbfun_layer_sticky_1()
 */
void kbfun_layer_sticky_6  (void) {
	layer_sticky(6);
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
 *   Layer sticky cycle #7
 *
 * [description]
 *   See the description of kbfun_layer_sticky_1()
 */
void kbfun_layer_sticky_7  (void) {
	layer_sticky(7);
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
 *   Layer sticky cycle #8
 *
 * [description]
 *   See the description of kbfun_layer_sticky_1()
 */
void kbfun_layer_sticky_8  (void) {
	layer_sticky(8);
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
 *   Layer sticky cycle #9
 *
 * [description]
 *   See the description of kbfun_layer_sticky_1()
 */
void kbfun_layer_sticky_9  (void) {
	layer_sticky(9);
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
 *   Layer sticky cycle #10
 *
 * [description]
 *   See the description of kbfun_layer_sticky_1()
 */
void kbfun_layer_sticky_10  (void) {
	layer_sticky(10);
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


