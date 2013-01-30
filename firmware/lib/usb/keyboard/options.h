/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * USB keyboard options
 *
 * Prefix: `OPT__`
 *
 * This file is meant to be included by the using '.../options.h'
 */


#ifndef ERGODOX_FIRMWARE__FIRMWARE__LIB__USB__KEYBOARD__OPTIONS__H
#define ERGODOX_FIRMWARE__FIRMWARE__LIB__USB__KEYBOARD__OPTIONS__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


#ifndef OPT__USB__STR_MANUFACTURER
    #error "OPT__USB__STR_MANUFACTURER not defined"
#endif
#ifndef OPT__USB__STR_PRODUCT
    #error "OPT__USB__STR_PRODUCT not defined"
#endif
#ifndef OPT__USB__VENDOR_ID
    #error "OPT__USB__VENDOR_ID not defined"
#endif
#ifndef OPT__USB__PRODUCT_ID
    #error "OPT__USB__PRODUCT_ID not defined"
#endif


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__FIRMWARE__LIB__USB__KEYBOARD__OPTIONS__H

