/* ----------------------------------------------------------------------------
 * Copyright (c) 2013, 2014 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Types used throughout the fragments of layout code in this directory
 */


/**                                                    types/_key_t/description
 * The type we will use for our "key"s
 *
 * Notes:
 * - Keys will be of the form
 *   `_key_t key = { &press_function, &release_function };`
 *
 * - The fact that keys are of this type (composed of two
 *   `void (*function)(void)` pointers) is assumed throughout most of these
 *   layout files
 */
typedef  void (*key_t[2])(void);

/**                                                 types/_layout_t/description
 * The type we will use for our layout matrix
 *
 * Notes:
 * - The first dimension of the matrix (left blank in the typedef since it
 *   varies between layouts) is "layers"
 */
typedef  const key_t layout_t[][OPT__KB__ROWS][OPT__KB__COLUMNS];

