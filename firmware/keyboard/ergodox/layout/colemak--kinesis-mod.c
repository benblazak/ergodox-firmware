/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * A Colemak layout using the "kinesis-mod" template
 *
 * Implements the "layout" section of '.../firmware/keyboard.h'
 */


// left hand letter key block
#define  T_q        q
#define  T_w        w
#define  T_e        f
#define  T_r        p
#define  T_t        g
#define  T_a        a
#define  T_s        r
#define  T_d        s
#define  T_f        t
#define  T_g        d
#define  T_z        z
#define  T_x        x
#define  T_c        c
#define  T_v        v
#define  T_b        b

// right hand letter key block
#define  T_y        j
#define  T_u        l
#define  T_i        u
#define  T_o        y
#define  T_p        semicol
#define  T_h        h
#define  T_j        n
#define  T_k        e
#define  T_l        i
#define  T_semicol  o
#define  T_n        k
#define  T_m        m
#define  T_comma    comma
#define  T_period   period
#define  T_slash    slash

// right hand outer key block
#define  T_bkslash  bkslash
#define  T_quote    quote


#include "./templates/kinesis-mod.c.h"

