/* ----------------------------------------------------------------------------
 * ergoDOX : keyboard specific options
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef KEYBOARD__ERGODOX__OPTIONS_h
	#define KEYBOARD__ERGODOX__OPTIONS_h

	// --------------------------------------------------------------------

	/*
	 * DRIVE_ROWS and DRIVE_COLUMNS
	 * - Select which pins will drive (alternate between hi-Z and drive
	 *   low) and which will be inputs
	 *
	 * Notes
	 * - You must set exactly one of each 'TEENSY' macro, and of each
	 *   'MCP23018' macro
	 * - If you are using internal diodes (inside the key switches)... then
	 *   i don't know what to tell you.  You will set one chip to drive
	 *   rows, and the other to drive columns, but i don't have a key
	 *   switch to check which at the moment, and i couldn't seem to find
	 *   it online.
	 * - If the diode cathode is towards the square solder pad, set
	 *   #define  TEENSY__DRIVE_COLUMNS    1
	 *   #define  MCP23018__DRIVE_COLUMNS  1
	 * - If the diode cathode is towards the circular solder pad, set
	 *   #define  TEENSY__DRIVE_ROWS       1
	 *   #define  MCP23018__DRIVE_ROWS     1
	 */
	#define  TEENSY__DRIVE_ROWS       0
	#define  TEENSY__DRIVE_COLUMNS    1
	#define  MCP23018__DRIVE_ROWS     0
	#define  MCP23018__DRIVE_COLUMNS  1

#endif
