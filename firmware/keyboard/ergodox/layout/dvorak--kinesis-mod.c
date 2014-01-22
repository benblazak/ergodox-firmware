/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * A Dvorak layout using the "kinesis-mod" template
 *
 * Implements the "layout" section of '.../firmware/keyboard.h'
 */


// left hand letter key block
#define  T_q        quote
#define  T_w        comma
#define  T_e        period
#define  T_r        p
#define  T_t        y
#define  T_a        a
#define  T_s        o
#define  T_d        e
#define  T_f        u
#define  T_g        i
#define  T_z        semicol
#define  T_x        q
#define  T_c        j
#define  T_v        k
#define  T_b        x

// right hand letter key block
#define  T_y        f
#define  T_u        g
#define  T_i        c
#define  T_o        r
#define  T_p        l
#define  T_h        d
#define  T_j        h
#define  T_k        t
#define  T_l        n
#define  T_semicol  s
#define  T_n        b
#define  T_m        m
#define  T_comma    w
#define  T_period   v
#define  T_slash    z

// right hand outer key block
#define  T_bkslash  slash
#define  T_quote    bkslash


#include "./templates/kinesis-mod.c.h"

