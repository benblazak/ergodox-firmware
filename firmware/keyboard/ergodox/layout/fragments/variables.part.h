/* ----------------------------------------------------------------------------
 * Copyright (c) 2013, 2014 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Variables global to the fragments of layout code in this directory
 */


/**                                                variables/layout/description
 * The variable containing our layout matrix
 *
 * Included here so that the matrix control code can come before the actual
 * definition of the layout.
 */
static layout_t layout PROGMEM;

/**                                                 variables/flags/description
 * A collection of flags pertaining to the operation of `...exec_key()`
 *
 * Notes:
 * - These should be set within key-functions, but only read inside
 *   `...exec_key()`.  The ability to read them outside that function should
 *   not be counted on.
 *
 * Struct members:
 * - `key_type`: To indicate the type of key most recently pressed
 *     - More than one type flag may be set (e.g. a key may be both a
 *       layer-shift key and a sticky key).
 * - `key_type.sticky`
 * - `key_type.layer_shift`
 * - `key_type.layer_lock`
 *
 * Terms:
 * - A "sticky key" is one which, once pressed, remains pressed in software
 *   (whether or not the user holds it down) ... TODO
 *
 * TODO:
 * - finish terms
 * - change other code (in "./matrix-control.part.h") to actually use the fact
 *   that we have 2 of these now (so that there is an "old" version, and a
 *   version to update)
 */
static struct {
    struct {
        bool sticky      : 1;
        bool layer_shift : 1;
        bool layer_lock  : 1;
    } key_type;
} flags[2];

