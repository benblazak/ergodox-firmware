/* ----------------------------------------------------------------------------
 * Copyright (c) 2013, 2014 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * This code fragment implements and extends the definitions in
 * ".../lib/layout/keys.h" and extends the definitions in
 * ".../lib/layout/key-functions.h"
 */


/**                                            macros/KEYS__DEFAULT/description
 * Define the functions for a default key (i.e. a normal key that presses and
 * releases a keycode as you'd expect)
 *
 * Needed by ".../lib/layout/keys.h"
 */
#define  KEYS__DEFAULT(name, value)             \
    void P(name) (void) { KF(press)(value); }   \
    void R(name) (void) { KF(release)(value); }

/**                                            macros/TYPE__DEFAULT/description
 * Define the functions for a default key (i.e. a normal key that presses and
 * releases a keycode as you'd expect). Other than KEYS_DEFAULT, this does send
 * a press and release event on key press and does not wait for the user
 * releasing the key.
 */
#define  TYPE__DEFAULT(name, value)                   \
    void P(name) (void) { KF(press)(value);           \
                          usb__kb__send_report();     \
                          KF(release)(value); }       \
    void R(name) (void) { }

/**                                            macros/KEYS__SHIFTED/description
 * Define the functions for a "shifted" key (i.e. a key that sends a "shift"
 * along with the keycode)
 *
 * Needed by ".../lib/layout/keys.h"
 */
#define  KEYS__SHIFTED(name, value)                             \
    void P(name) (void) { KF(press)(KEYBOARD__LeftShift);       \
                          KF(press)(value); }                   \
    void R(name) (void) { KF(release)(value);                   \
                          KF(release)(KEYBOARD__LeftShift); }

/**                                            macros/TYPE__SHIFTED/description
 * Define the functions for a "shifted" key (i.e. a key that sends a "shift"
 * along with the keycode). Other than KEYS_SHIFTED, this does send
 * a press and release event on key press and does not wait for the user
 * releasing the key.
 */
#define  TYPE__SHIFTED(name, value)                             \
    void P(name) (void) { KF(press)(KEYBOARD__LeftShift);       \
                          usb__kb__send_report();               \
                          KF(press)(value);                     \
                          usb__kb__send_report();               \
                          KF(release)(value);                   \
                          KF(release)(KEYBOARD__LeftShift); }   \
    void R(name) (void) { }

/**                                            macros/KEYS__ALT_GR/description
 * Define the functions for a "AltGr" key (i.e. a key that sends a "AltGr"
 * along with the keycode).
 */
#define  KEYS__ALT_GR(name, value)                             \
    void P(name) (void) { KF(press)(KEYBOARD__RightAlt);       \
                          KF(press)(value); }                  \
    void R(name) (void) { KF(release)(value);                  \
                          KF(release)(KEYBOARD__RightAlt); }

/**                                            macros/TYPE__ALT_GR/description
 * Define the functions for a "AltGr" key (i.e. a key that sends a "AltGr"
 * along with the keycode). Other than KEYS_SHIFTED, this does send
 * a press and release event on key press and does not wait for the user
 * releasing the key.
 */
#define  TYPE__ALT_GR(name, value)                             \
    void P(name) (void) { KF(press)(KEYBOARD__RightAlt);       \
                          usb__kb__send_report();              \
                          KF(press)(value);                    \
                          usb__kb__send_report();              \
                          KF(release)(value);                  \
                          KF(release)(KEYBOARD__RightAlt); }   \
    void R(name) (void) { }

/**                                            macros/TYPE__NON_DEAD/description
 * Define the functions for a normally dead key, to be non-dead.
 */
#define  TYPE__NON_DEAD(name, value)                           \
    void P(name) (void) { KF(press)(value);                    \
                          usb__kb__send_report();              \
                          KF(release)(value);                  \
                          usb__kb__send_report();              \
                          KF(press)(KEYBOARD__Spacebar);       \
                          usb__kb__send_report();              \
                          KF(release)(KEYBOARD__Spacebar); }   \
    void R(name) (void) {}

/**                                            macros/TYPE__NON_DEAD_SHIFTED/description
 * Define the functions for a normally dead key, which needs the "shift"
 * key to be pressed, to be non-dead.
 */
#define  TYPE__NON_DEAD_SHIFTED(name, value)                   \
    void P(name) (void) { KF(press)(KEYBOARD__LeftShift);      \
                          usb__kb__send_report();              \
                          KF(press)(value);                    \
                          usb__kb__send_report();              \
                          KF(release)(value);                  \
                          KF(release)(KEYBOARD__LeftShift);    \
                          usb__kb__send_report();              \
                          KF(press)(KEYBOARD__Spacebar);       \
                          usb__kb__send_report();              \
                          KF(release)(KEYBOARD__Spacebar); }   \
    void R(name) (void) {}

/**                                            macros/TYPE__NON_DEAD_ALT_GR/description
 * Define the functions for a normally dead key, which needs the "AltGr"
 * key, to be non-dead.
 */
#define  TYPE__NON_DEAD_ALT_GR(name, value)                    \
    void P(name) (void) { KF(press)(KEYBOARD__RightAlt);       \
                          usb__kb__send_report();              \
                          KF(press)(value);                    \
                          usb__kb__send_report();              \
                          KF(release)(value);                  \
                          KF(release)(KEYBOARD__RightAlt);     \
                          usb__kb__send_report();              \
                          KF(press)(KEYBOARD__Spacebar);       \
                          usb__kb__send_report();              \
                          KF(release)(KEYBOARD__Spacebar); }   \
    void R(name) (void) {}

/**                                    macros/KEYS__LAYER__PUSH_POP/description
 * Define the functions for a layer push-pop key (i.e. a layer shift key).
 *
 * Naming Convention:
 * - Example: In the name `lpupo1l1`, we have the following:
 *     - `l`  : this is a layer key
 *     - `pu` : it pushes the layer element onto the stack on "press"
 *     - `po` : it pops the layer element out of the stack on "release"
 *     - `1`  : it pushes and pops the layer element with `layer_id` = 1
 *     - `l`  : (separate the `layer_id` from the `layer_number`)
 *     - `1`  : it pushes a layer element with `layer_number` = 1
 *
 * - The first and second number do not have to be the same (that is, the
 *   `layer_id` and `layer_number` can be different; there may be situations
 *   where you want or need this).
 *
 * - Only one of `pu` or `po` is necessary.  A key with only `pu` should *only*
 *   push the layer onto the stack, not pop anything out of it.  A key with
 *   only `po` should *only* pop the layer out of the stack.
 *
 * - If the function *only* pops the layer-element, the `layer_number` is not
 *   important: layers are popped based only on their `layer_id`.
 *
 * Notes:
 * - To save space, if you define a push-pop function, the push (only) and pop
 *   (only) functions may be defined as follows (using the example `lpupo1l1`
 *   from above):
 *
 *       #define  keys__press__lpu1l1    P(lpupo1l1)
 *       #define  keys__release__lpu1l1  KF(nop)
 *       #define  keys__press__lpo1l1    R(lpupo1l1)
 *       #define  keys__release__lpo1l1  KF(nop)
 */
#define  KEYS__LAYER__PUSH_POP(ID, LAYER)                                   \
    void P(lpupo##ID##l##LAYER) (void) { layer_stack__push(0, ID, LAYER); } \
    void R(lpupo##ID##l##LAYER) (void) { layer_stack__pop_id(ID); }

// ----------------------------------------------------------------------------

/**                                   functions/KF(2_keys_capslock)/description
 * Press the given keycode, and also press "capslock" if this is the second
 * consecutive time this function has been called with `pressed == true`.
 *
 * Meant to be used with the left and right "shift" keys.
 */
void KF(2_keys_capslock)(bool pressed, uint8_t keycode) {
    static uint8_t counter = 0;
    if (pressed) {
        counter++;
        KF(press)(keycode);
    }
    if (counter == 2 && pressed) {
        KF(toggle_capslock)();
    }
    if (!pressed) {
        counter--;
        KF(release)(keycode);
    }
}

// ----------------------------------------------------------------------------

// --- default key definitions ------------------------------------------------

#include "../../../../../firmware/lib/layout/keys.h"


// --- special meaning --------------------------------------------------------

/**                                                     keys/transp/description
 * transparent
 *
 * This key signals to the firmware (specifically the
 * `kb__layout__exec_key_location()` function) that it should look for what key
 * to "press" or "release" by going down the layer-stack until it finds a
 * non-transparent key at the same position.
 *
 * Notes:
 * - With this scheme, keys may be half transparent; that is, the "press" part
 *   of a key may be transparent while the "release" part isn't, or vice versa.
 *   I expect this to be fairly uncommon though.
 */
void KF(transp) (void) {}
#define  keys__press__transp    KF(transp)
#define  keys__release__transp  KF(transp)

/**                                                        keys/nop/description
 * no operation
 *
 * This key does nothing (and is not transparent).
 */
void KF(nop) (void) {}
#define  keys__press__nop    KF(nop)
#define  keys__release__nop  KF(nop)


// --- special keycode --------------------------------------------------------

KEYS__DEFAULT( power,   KEYBOARD__Power      );
KEYS__DEFAULT( volumeU, KEYBOARD__VolumeUp   );
KEYS__DEFAULT( volumeD, KEYBOARD__VolumeDown );
KEYS__DEFAULT( mute,    KEYBOARD__Mute       );


// --- special function -------------------------------------------------------

/**                                                   keys/shL2kcap/description
 * left shift + toggle capslock (if both shifts are pressed)
 *
 * This key always generates a left shift.  If the `shR2kcap` is pressed at
 * the same time, "capslock" will be toggled.
 */
void P(shL2kcap) (void) { KF(2_keys_capslock)(true, KEYBOARD__LeftShift); }
void R(shL2kcap) (void) { KF(2_keys_capslock)(false, KEYBOARD__LeftShift); }

/**                                                   keys/shR2kcap/description
 * right shift + toggle capslock (if both shifts are pressed)
 *
 * This key always generates a right shift.  If the `shL2kcaps` is pressed at
 * the same time, "capslock" will be toggled.
 */
void P(shR2kcap) (void) { KF(2_keys_capslock)(true, KEYBOARD__RightShift); }
void R(shR2kcap) (void) { KF(2_keys_capslock)(false, KEYBOARD__RightShift); }

/**                                                      keys/btldr/description
 * jump to the bootloader
 *
 * This prepares the Teensy to load a new firmware.  If you press this without
 * meaning to, you must turn your keyboard off then on again (usually by
 * unplugging it, then plugging it back in).
 */
void P(btldr) (void) { KF(jump_to_bootloader)(); }
void R(btldr) (void) {}

/**                                                   keys/dmp_sram/description
 * type the contents of SRAM, in ihex format
 *
 * This may take a while.  To cancel, you must turn your keyboard off then on
 * again (usually by unplugging it, then plugging it back in).
 */
void P(dmp_sram) (void) { KF(dump_sram_ihex)( (void *)0, (void *)-1 ); }
void R(dmp_sram) (void) {}

/**                                                   keys/dmp_prog/description
 * type the contents of PROGMEM, in ihex format
 *
 * This may take a while.  To cancel, you must turn your keyboard off then on
 * again (usually by unplugging it, then plugging it back in).
 */
void P(dmp_prog) (void) { KF(dump_progmem_ihex)( (void *)0, (void *)-1 ); }
void R(dmp_prog) (void) {}

/**                                                   keys/dmp_eepr/description
 * type the contents of the EEPROM, in ihex format
 *
 * This may take a while.  To cancel, you must turn your keyboard off then on
 * again (usually by unplugging it, then plugging it back in).
 */
void P(dmp_eepr) (void) { KF(dump_eeprom_ihex)( (void *)0, (void *)-1 ); }
void R(dmp_eepr) (void) {}


// ----------------------------------------------------------------------------
// --- layer ------------------------------------------------------------------

// - these are just some default layer key definitions; no need to stick to
//   them if they're inconvenient
// - the functions for layers 1 and 2 are special here in that they turn on and
//   off the corresponding LED (the third LED is reserved for capslock)

KEYS__LAYER__PUSH_POP(0, 0);
#define  keys__press__lpu0l0    P(lpupo0l0)
#define  keys__release__lpu0l0  KF(nop)
#define  keys__press__lpo0l0    R(lpupo0l0)
#define  keys__release__lpo0l0  KF(nop)

KEYS__LAYER__PUSH_POP(1,1);
void P(lpu1l1) (void) { layer_stack__push(0, 1, 1); kb__led__on(1); }
#define  keys__release__lpu1l1  KF(nop)
void P(lpo1l1) (void) { layer_stack__pop_id(1); kb__led__off(1); }
#define  keys__release__lpo1l1  KF(nop)

KEYS__LAYER__PUSH_POP(2,2);
void P(lpu2l2) (void) { layer_stack__push(0, 2, 2); kb__led__on(2); }
#define  keys__release__lpu2l2  KF(nop)
void P(lpo2l2) (void) { layer_stack__pop_id(2); kb__led__off(2); }
#define  keys__release__lpo2l2  KF(nop)

KEYS__LAYER__PUSH_POP(3, 3);
#define  keys__press__lpu3l3    P(lpupo3l3)
#define  keys__release__lpu3l3  KF(nop)
#define  keys__press__lpo3l3    R(lpupo3l3)
#define  keys__release__lpo3l3  KF(nop)

KEYS__LAYER__PUSH_POP(4, 4);
#define  keys__press__lpu4l4    P(lpupo4l4)
#define  keys__release__lpu4l4  KF(nop)
#define  keys__press__lpo4l4    R(lpupo4l4)
#define  keys__release__lpo4l4  KF(nop)

KEYS__LAYER__PUSH_POP(5, 5);
#define  keys__press__lpu5l5    P(lpupo5l5)
#define  keys__release__lpu5l5  KF(nop)
#define  keys__press__lpo5l5    R(lpupo5l5)
#define  keys__release__lpo5l5  KF(nop)

KEYS__LAYER__PUSH_POP(6, 6);
#define  keys__press__lpu6l6    P(lpupo6l6)
#define  keys__release__lpu6l6  KF(nop)
#define  keys__press__lpo6l6    R(lpupo6l6)
#define  keys__release__lpo6l6  KF(nop)

KEYS__LAYER__PUSH_POP(7, 7);
#define  keys__press__lpu7l7    P(lpupo7l7)
#define  keys__release__lpu7l7  KF(nop)
#define  keys__press__lpo7l7    R(lpupo7l7)
#define  keys__release__lpo7l7  KF(nop)

KEYS__LAYER__PUSH_POP(8, 8);
#define  keys__press__lpu8l8    P(lpupo8l8)
#define  keys__release__lpu8l8  KF(nop)
#define  keys__press__lpo8l8    R(lpupo8l8)
#define  keys__release__lpo8l8  KF(nop)

KEYS__LAYER__PUSH_POP(9, 9);
#define  keys__press__lpu9l9    P(lpupo9l9)
#define  keys__release__lpu9l9  KF(nop)
#define  keys__press__lpo9l9    R(lpupo9l9)
#define  keys__release__lpo9l9  KF(nop)

