/* ----------------------------------------------------------------------------
 * USB 2.0 common macros and definitions
 *
 * See "notes from usb 2.0 spec sec 9 (usb device framework).h".
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef USB_COMMON_h
	#define USB_COMMON_h
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


// - spec table 9-4 (Standard Request Codes)
#define USB_GET_STATUS         0
#define USB_CLEAR_FEATURE      1
// (reserved for future use):  2
#define USB_SET_FEATURE        3
// (reserved for future use):  4
#define USB_SET_ADDRESS        5
#define USB_GET_DESCRIPTOR     6
#define USB_SET_DESCRIPTOR     7
#define USB_GET_CONFIGURATION  8
#define USB_SET_CONFIGURATION  9
#define USB_GET_INTERFACE     10
#define USB_SET_INTERFACE     11
#define USB_SYNCH_FRAME       12

// - spec table 9-5 (Descriptor Types)
#define USB_DEVICE                    1
#define USB_CONFIGURATION             2
#define USB_STRING                    3
#define USB_INTERFACE                 4
#define USB_ENDPOINT                  5
#define USB_DEVICE_QUALIFIER          6
#define USB_OTHER_SPEED_CONFIGURATION 7
#define USB_INTERFACE_POWER           8

// - spec table 9-6 (Standard Feature Selectors)
#define USB_DEVICE_REMOTE_WAKEUP 1  // recipient: device
#define USB_ENDPOINT_HALT        0  // recipient: endpoint
#define USB_TEST_MODE            2  // recipient: device


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif

