/* ----------------------------------------------------------------------------
 * Copyright (c) 2012, 2013, 2014 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Default macro definitions
 */


/**                                                        macros/P/description
 * Expand `name` into the corresponding "press" function name
 */
#define  P(name)  keys__press__##name

/**                                                        macros/R/description
 * Expand `name` into the corresponding "release" function name
 */
#define  R(name)  keys__release__##name

/**                                                        macros/K/description
 * Expand into a "key" suitable for putting into the layout matrix
 */
#define  K(name)  { &keys__press__##name, &keys__release__##name }

/**                                                       macros/KF/description
 * Expand `name` into the corresponding "key_functions" function name
 */
#define  KF(name)  key_functions__##name


/**                                             macros/MATRIX_LAYER/description
 * Mapping from spatial position to matrix position.
 *
 * - Spatial position: Where the key is spatially, relative to other keys, both
 *   on the keyboard and in the layout.
 * - Matrix position: The coordinate in the matrix to which a key is scanned by
 *   the update functions.
 *
 * - Location numbers are in the format `row##column`, where both 'row' and
 *   'column' are single digit hex numbers corresponding to the matrix position
 *   (which also corresponds to the row and column pin labels used in the
 *   Teensy and MCP23018 files).
 *
 * - Coordinates:
 *     - optional keys
 *         - k15, k16 (left hand thumb group)
 *         - k17, k18 (right hand thumb group)
 *     - unused keys
 *         - k36, k00 (left hand)
 *         - k37, k0D (right hand)
 *
 * - Other Info:
 *       ----------------------------------------------------
 *                 rows x columns = positions;  used,  unused
 *       per hand:    6 x  7      = 42;         40,    2
 *          total:    6 x 14      = 84;         80,    4
 *       
 *       left hand  : rows 0..5, cols 0..6
 *       right hand : rows 0..5, cols 7..D
 *       ----------------------------------------------------
 */
#define MATRIX_LAYER(                                                                                           \
            /* the name of a macro to call on all arguments */                                                  \
            M,                                                                                                  \
                                                                                                                \
            /* for unused positions */                                                                          \
            na,                                                                                                 \
                                                                                                                \
            /* left hand, spatial positions */                                                                  \
            k50,k51,k52,k53,k54,k55,k56,                                                                        \
            k40,k41,k42,k43,k44,k45,k46,                                                                        \
            k30,k31,k32,k33,k34,k35,                                                                            \
            k20,k21,k22,k23,k24,k25,k26,                                                                        \
            k10,k11,k12,k13,k14,                                                                                \
                                    k05,k06,                                                                    \
                                k15,k16,k04,                                                                    \
                                k03,k02,k01,                                                                    \
                                                                                                                \
            /* right hand, spatial positions */                                                                 \
                k57,k58,k59,k5A,k5B,k5C,k5D,                                                                    \
                k47,k48,k49,k4A,k4B,k4C,k4D,                                                                    \
                    k38,k39,k3A,k3B,k3C,k3D,                                                                    \
                k27,k28,k29,k2A,k2B,k2C,k2D,                                                                    \
                        k19,k1A,k1B,k1C,k1D,                                                                    \
            k07,k08,                                                                                            \
            k09,k17,k18,                                                                                        \
            k0C,k0B,k0A )                                                                                       \
                                                                                                                \
    /* matrix positions */                                                                                      \
    {{ M( na),M(k01),M(k02),M(k03),M(k04),M(k05),M(k06), M(k07),M(k08),M(k09),M(k0A),M(k0B),M(k0C),M( na) },    \
     { M(k10),M(k11),M(k12),M(k13),M(k14),M(k15),M(k16), M(k17),M(k18),M(k19),M(k1A),M(k1B),M(k1C),M(k1D) },    \
     { M(k20),M(k21),M(k22),M(k23),M(k24),M(k25),M(k26), M(k27),M(k28),M(k29),M(k2A),M(k2B),M(k2C),M(k2D) },    \
     { M(k30),M(k31),M(k32),M(k33),M(k34),M(k35),M( na), M( na),M(k38),M(k39),M(k3A),M(k3B),M(k3C),M(k3D) },    \
     { M(k40),M(k41),M(k42),M(k43),M(k44),M(k45),M(k46), M(k47),M(k48),M(k49),M(k4A),M(k4B),M(k4C),M(k4D) },    \
     { M(k50),M(k51),M(k52),M(k53),M(k54),M(k55),M(k56), M(k57),M(k58),M(k59),M(k5A),M(k5B),M(k5C),M(k5D) }}

