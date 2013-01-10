/* ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**
 * - description: |
 *     Some generally useful key-functions, and related definitions
 *
 *     Prefix: `kf__`
 */


#ifndef ERGODOX_FIRMWARE__FIRMWARE__LIB__LAYOUT__KEY_FUNCTIONS__H
#define ERGODOX_FIRMWARE__FIRMWARE__LIB__LAYOUT__KEY_FUNCTIONS__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

#include <stdint.h>

// ----------------------------------------------------------------------------

typedef  void (*kf__function_pointer_t)(uint16_t value);

// ----------------------------------------------------------------------------

// basic
void kf__press          (uint16_t keycode);
void kf__release        (uint16_t keycode);
void kf__send           (uint16_t ignore);
void kf__toggle         (uint16_t keycode);
void kf__layer__push    (uint16_t layer_stack_id__layer_number);
void kf__layer__pop     (uint16_t layer_stack_id);
void kf__macro__progmem (uint16_t pointer);
void kf__macro__eeprom  (uint16_t pointer);

// device
void kf__jump_to_bootloader (uint16_t ignore);

// special
void kf__two_keys_capslock (uint16_t pressed);


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__FIRMWARE__LIB__LAYOUT__KEY_FUNCTIONS__H


// TODO:
// - move documentation to the '.c' files
// - rewrite, coz of changes
/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  # documentation ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  # typedefs ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  - typedef
      type: '`void (*kf__function_pointer_t)(void)`'
      name: '`kf__function_pointer_t`'
      description: The pointer type for all key-functions.
      notes:
        - All key-functions must have the same type so that we can easily store
          pointers to them, and call them using the pointers without knowing
          which function specifically is being pointed to.

  # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  # functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  # basic ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  - function:
      name: '`kf__press_release`'
      description: Generate a normal keypress or keyrelease.

  - function:
      name: '`kf__toggle`'
      description: Toggle the key pressed or unpressed.

  - function:
      name: '`kf__transparent`'
      description:
        Execute the key that would have been executed if the current layer was
        not active.


  # layer ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  - .ignore:

    - &kf__layer__push
      description:
        Push a layer element containing the layer value specified in the keymap
        to the top of the stack.

    - &kf__layer__pop
      description:
        Pop the layer element created by the corresponding "layer push"
        function out of the layer stack.
      notes:
        - The layer element is popped out of the stack no matter where it is in
          the stack, without touching any of the other elements.

  # ~~~~~~~

  - function: { name: '`kf__layer__push_0`', << : *kf__layer__push }
  - function: { name: '`kf__layer__push_1`', << : *kf__layer__push }
  - function: { name: '`kf__layer__push_2`', << : *kf__layer__push }
  - function: { name: '`kf__layer__push_3`', << : *kf__layer__push }
  - function: { name: '`kf__layer__push_4`', << : *kf__layer__push }
  - function: { name: '`kf__layer__push_5`', << : *kf__layer__push }
  - function: { name: '`kf__layer__push_6`', << : *kf__layer__push }
  - function: { name: '`kf__layer__push_7`', << : *kf__layer__push }
  - function: { name: '`kf__layer__push_8`', << : *kf__layer__push }
  - function: { name: '`kf__layer__push_9`', << : *kf__layer__push }

  - function: { name: '`kf__layer__pop_0`', << : *kf__layer__pop }
  - function: { name: '`kf__layer__pop_1`', << : *kf__layer__pop }
  - function: { name: '`kf__layer__pop_2`', << : *kf__layer__pop }
  - function: { name: '`kf__layer__pop_3`', << : *kf__layer__pop }
  - function: { name: '`kf__layer__pop_4`', << : *kf__layer__pop }
  - function: { name: '`kf__layer__pop_5`', << : *kf__layer__pop }
  - function: { name: '`kf__layer__pop_6`', << : *kf__layer__pop }
  - function: { name: '`kf__layer__pop_7`', << : *kf__layer__pop }
  - function: { name: '`kf__layer__pop_8`', << : *kf__layer__pop }
  - function: { name: '`kf__layer__pop_9`', << : *kf__layer__pop }

  # device ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  - function:
      name: '`kf__jump_to_bootloader`'
      description: For reflashing the controller

  # special ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  - function:
      name: '`kf__shift_press_release`'
      description:
        Generate a "shift" press or release before the normal keypress or
        keyrelease.

  - function:
      name: '`kf__two_keys_capslock_press_release`'
      description:
        When assigned to two keys (e.g. the physical left and right shift keys)
        (in both the press and release matrices), pressing and holding down on
        of the keys will make the second key toggle capslock.
      notes:
        - If either of the shifts are pressed when the second key is pressed,
          they will be released so that capslock will register properly when
          pressed.  Capslock will then be pressed and released, and the
          original state of the shifts will be restored.

  - function:
      name: '`kf__layer__push_numpad`'
      description:
        Set the numpad to on (put the numpad layer, specified in the keymap, in
        a layer element at the top of the layer stack) and toggle numlock
        (regardless of whether or not numlock is currently on)
      notes:
        - Meant to be assigned (along with "numpad off") *instead* of a normal
          numlock key.

  - function:
      name: '`kf__layer__pop_numpad`'
      description:
        Set the numpad to off (pop the layer element created by "numpad on" out
        of the stack) and toggle numlock (regardless of whether or not numlock
        is currently on).
      notes:
        - Meant to be assigned (along with "numpad on") *instead* of a normal
          numlock key.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ **/

