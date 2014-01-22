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
 * Struct members:
 * - `tick_keypresses`: A predicate indicating whether or not to "tick"
 *   keypresses on this run of the function (see the documentation in
 *   ".../firmware/lib/timer.h" for more precisely what this means)
 *     - This is useful for defining things like sticky keys, if, e.g., you
 *       want to make it so that you can press more than one and have none of
 *       them release until the press of the next normal key.
 */
static struct {
    bool tick_keypresses : 1;
} flags = {
    .tick_keypresses = true,
};

