/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * A QWERTY layout using the "kinesis-mod" template
 *
 * Implements the "layout" section of '.../firmware/keyboard.h'
 */


// left hand letter key block
#define  T_q        q
#define  T_w        w
#define  T_e        e
#define  T_r        r
#define  T_t        t
#define  T_a        a
#define  T_s        s
#define  T_d        d
#define  T_f        f
#define  T_g        g
#define  T_z        z
#define  T_x        x
#define  T_c        c
#define  T_v        v
#define  T_b        b

// right hand letter key block
#define  T_y        y
#define  T_u        u
#define  T_i        i
#define  T_o        o
#define  T_p        p
#define  T_h        h
#define  T_j        j
#define  T_k        k
#define  T_l        l
#define  T_semicol  semicol
#define  T_n        n
#define  T_m        m
#define  T_comma    comma
#define  T_period   period
#define  T_slash    slash

// right hand outer key block
#define  T_bkslash  bkslash
#define  T_quote    quote


#include "./templates/kinesis-mod.c.h"

