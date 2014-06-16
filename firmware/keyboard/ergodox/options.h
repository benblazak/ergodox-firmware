/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * A central place for all ErgoDox source-level options
 *
 * Prefix: `OPT__`
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
// in milliseconds


// ----------------------------------------------------------------------------
// firmware/keyboard/controller
// ----------------------------------------------------------------------------

// --- if the diode cathode is towards the square solder pad
#define  OPT__TEENSY__DRIVE_ROWS     0
#define  OPT__TEENSY__DRIVE_COLUMNS  1
#define  OPT__MCP23018__DRIVE_ROWS     0
#define  OPT__MCP23018__DRIVE_COLUMNS  1
// ............................................................................
// --- if the diode cathode is towards the circular solder pad
// #define  OPT__TEENSY__DRIVE_ROWS     1
// #define  OPT__TEENSY__DRIVE_COLUMNS  0
// #define  OPT__MCP23018__DRIVE_ROWS     1
// #define  OPT__MCP23018__DRIVE_COLUMNS  0
// ............................................................................
// --- if you are using internal diodes (inside the key switches)
// #define  OPT__TEENSY__DRIVE_ROWS     0
// #define  OPT__TEENSY__DRIVE_COLUMNS  1
// #define  OPT__MCP23018__DRIVE_ROWS     1
// #define  OPT__MCP23018__DRIVE_COLUMNS  0
// ............................................................................
// ............................................................................
// pin drive direction


// ----------------------------------------------------------------------------
// firmware/keyboard/led
// ----------------------------------------------------------------------------

#define  OPT__LED_BRIGHTNESS  0.5
// a multiplier, with '1' being max


// ----------------------------------------------------------------------------
// firmware/keyboard
// ----------------------------------------------------------------------------

#define  OPT__KB__ROWS     6
#define  OPT__KB__COLUMNS  14


// ----------------------------------------------------------------------------
// firmware/lib/...
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

#define  OPT__TWI__FREQUENCY  400000


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

#define  OPT__USB__STR_MANUFACTURER  L"DIY"
#define  OPT__USB__STR_PRODUCT       L"ErgoDox Ergonomic Keyboard"
#define  OPT__USB__VENDOR_ID         0x1d50  // Openmoko, Inc.
#define  OPT__USB__PRODUCT_ID        0x6028  // ErgoDox Ergonomic Keyboard


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

#define  OPT__EEPROM__EEPROM_MACRO__START  0
#define  OPT__EEPROM__EEPROM_MACRO__END    1023


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__FIRMWARE__KEYBOARD__ERGODOX__OPTIONS__H

