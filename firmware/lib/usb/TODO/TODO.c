/* ----------------------------------------------------------------------------
 * TODO: not sure where this stuff should be yet.  a lot of it (depending on
 * what ends up here) will likely be device and application specific.
 *
 * - The following document versions were used, unless otherwise noted:
 *   - USB Specification: revision 2.0
 *   - HID Usage Tables: version 1.12
 *   - Device Class Definition for Human Interface Devices (HID): version 1.11
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


// TODO: does stuff from spec sec 9.4.* belong directly in an interrupt vector?

// - spec sec 9.4.1 (Standard Device Requests / Clear Feature) (pg 252)

// - spec sec 9.4.2 (Standard Device Requests / Get Configuration) (pg 253)

// - spec sec 9.4.3 (Standard Device Requests / Get Descriptor) (pg 253)

// - spec sec 9.4.4 (Standard Device Requests / Get Interface) (pg 254)

// - spec sec 9.4.5 (Standard Device Requests / Get Status) (pg 254)

// - spec sec 9.4.6 (Standard Device Requests / Set Address) (pg 256)

// - spec sec 9.4.7 (Standard Device Requests / Set Configuration) (pg 257)

// - spec sec 9.4.8 (Standard Device Requests / Set Descriptor) (pg 257)

// - spec sec 9.4.9 (Standard Device Requests / Set Feature) (pg 258)

// - spec sec 9.4.10 (Standard Device Requests / Set Interface) (pg 259)

// - spec sec 9.4.11 (Standard Device Requests / Synch Frame) (pg 260)

// TODO
// - read the hid device class definition .pdf
// - set USB vendor  ID = 0x1d50  // Openmoko, Inc.
//       USB product ID = 0x6028  // ErgoDox ergonomic keyboard

// DONE
// - read the hid usage tables .pdf
//   - i think this is more for reference and implementation than
//     understanding.  i've copied the relevant (i think) tables ones into
//     headers.  the unicode usage page, i'll have to look into more later: i'm
//     not sure if it can be used with keyboards.  if so though, i'll have to
//     look on the unicode website, or elsewhere, coz this .pdf doesn't list
//     anything about them out, it just references the unicode spec.

