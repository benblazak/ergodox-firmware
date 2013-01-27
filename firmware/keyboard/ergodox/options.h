/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * A central place for all ErgoDox source-level options
 *
 * Prefixes: `OPT__`
 *
 * This file is meant to be globally included on the command line.
 */


#ifndef ERGODOX_FIRMWARE__FIRMWARE__KEYBOARD__ERGODOX__OPTIONS__H
#define ERGODOX_FIRMWARE__FIRMWARE__KEYBOARD__ERGODOX__OPTIONS__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// firmware/main
// ----------------------------------------------------------------------------

#define  OPT__DEBOUNCE_TIME  5
/**                                       macros/OPT__DEBOUNCE_TIME/description
 * in milliseconds; 5ms should be good for cherry mx switches (per the
 * keyswitch spec)
 */

// ----------------------------------------------------------------------------
// firmware/keyboard/controller
// ----------------------------------------------------------------------------

#define  OPT__TEENSY__DRIVE_ROWS     0
#define  OPT__TEENSY__DRIVE_COLUMNS  1
#define  OPT__MCP23018__DRIVE_ROWS     0
#define  OPT__MCP23018__DRIVE_COLUMNS  1
/**                              macros/(group) pin drive direction/description
 * Select which set of pins will drive (alternate between hi-Z and drive low)
 * and which will be inputs (hi-Z)
 *
 * Members:
 * - `OPT__TEENSY__DRIVE_ROWS`
 * - `OPT__TEENSY__DRIVE_COLUMNS`
 * - `OPT__MCP23018__DRIVE_ROWS`
 * - `OPT__MCP23018__DRIVE_COLUMNS`
 * 
 *
 * Notes:
 * 
 * - You must set exactly one of each 'TEENSY' variable, and one of each
 *   'MCP23018' variable, to '1', and the other must be set to '0'
 * 
 * - If you are using internal diodes (inside the key switches), set
 *   OPT__TEENSY__DRIVE_COLUMNS := 1
 *   OPT__MCP23018__DRIVE_ROWS  := 1
 * 
 * - If the diode cathode is towards the square solder pad, set
 *   OPT__TEENSY__DRIVE_COLUMNS   := 1
 *   OPT__MCP23018__DRIVE_COLUMNS := 1
 * 
 * - If the diode cathode is towards the circular solder pad, set
 *   OPT__TEENSY__DRIVE_ROWS   := 1
 *   OPT__MCP23018__DRIVE_ROWS := 1
 */


// ----------------------------------------------------------------------------
// firmware/keyboard/led
// ----------------------------------------------------------------------------

#define  OPT__LED_BRIGHTNESS  0.5
/**                                     macros/MAKE__LED_BRIGHTNESS/description
 * a multiplier, with 1 being the max
 */


// ----------------------------------------------------------------------------
// firmware/lib/twi
// ----------------------------------------------------------------------------

#define  OPT__TWI_FREQENCY  400000
/**                                       macros/OPT__TWI__FREQENCY/description
 * in Hz; max value is 400000 (400kHz) (Teensy datasheet sec 20.1)
 */


// ----------------------------------------------------------------------------
// firmware/lib/from-pjrc/usb_keyboard
// ----------------------------------------------------------------------------

#define  OPT__USB__STR_MANUFACTURER  L"custom"
#define  OPT__USB__STR_PRODUCT       L"ErgoDox ergonomic keyboard"
#define  OPT__USB__VENDOR_ID         0x1d50  // Openmoko, Inc.
#define  OPT__USB__PRODUCT_ID        0x6028  // ErgoDox ergonomic keyboard
/**                                              macros/(group) USB/description
 * USB identifier information
 *
 * Members:
 * - `OPT__USB__STR_MANUFACTURER`
 * - `OPT__USB__STR_PRODUCT`
 * - `OPT__USB__VENDOR_ID`
 * - `OPT__USB__PRODUCT_ID`
 */


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__FIRMWARE__KEYBOARD__ERGODOX__OPTIONS__H


