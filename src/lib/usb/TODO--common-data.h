/* ----------------------------------------------------------------------------
 * Common data structures, macros, and other definitions from the USB spec and
 * related documents
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


#ifndef USB_DATA_STRUCTURES_h
	#define USB_DATA_STRUCTURES_h
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


#include "lib/data-types.h"


// - spec sec 9.3 (USB Device Requests)
//   - table 9-2 (Format of Setup Data)
struct usb_setup_data {
	uint8_t  bmRequestType;
	// value: bitmap
	// - data transfer direction, type, recipient
	//   (see macros below)

	uint8_t  bRequest;
	// value: value
	// - type of request (depending on bmRequestType)
	//   (see spec table 9-3 (Standard Device Requests))

	uint16_t wValue;
	// value: value
	// - varies according to request; used to pass a request specific
	//   parameter to the device

	uint16_t wIndex;
	// value: index or offset
	// - varies according to request; often used to specify an endpoint or
	//   an interface
	//   (see spec figure 9-2 and 9-3, copied below)

	uint16_t wLength;
	// value: count
	// - number of bytes to transfer if there is a data stage
};

// - table 9-2 (Format of Setup Data)
//   - bmRequestType
// --- data transfer direction
#define usb_bmRequestType_hostToDevice(val) (((val) & 0x80) == 0x00)
#define usb_bmRequestType_deviceToHost(val) (((val) & 0x80) == 0x80)
// --- type
#define usb_bmRequestType_standard(val)     (((val) & 0x60) == 0x00)
#define usb_bmRequestType_class(val)        (((val) & 0x60) == 0x20)
#define usb_bmRequestType_vendor(val)       (((val) & 0x60) == 0x40)
#define usb_bmRequestType_reserved(val)     (((val) & 0x60) == 0x60)
// --- recipient
#define usb_bmRequestType_device(val)       (((val) & 0x1F) == 0x00)
#define usb_bmRequestType_interface(val)    (((val) & 0x1F) == 0x01)
#define usb_bmRequestType_endpoint(val)     (((val) & 0x1F) == 0x02)
#define usb_bmRequestType_other(val)        (((val) & 0x1F) == 0x03)
#define usb_bmRequestType_reserved(val)     (((val) & 0x1C) != 0x00)

// - spec sec 9.3.4 (wIndex)
//   - figure 9-2 (format when specifying an endpoint)
// .-------------------------------------------------------.
// |    D7     |      D6 | D5 | D4     | D3 | D2 | D1 | D0 |
// |-------------------------------------------------------|
// | direction | reserved (reset to 0) |  endpoint number  |
//  >-----------------------------------------------------<
// |      D15 | D14 | D13 | D12 | D11 | D10 | D9 | D8      |
// |-------------------------------------------------------|
// |                 reserved (reset to 0)                 |
// '-------------------------------------------------------'
// - direction bit: 0 => out (to device), 1 => in (to host)
#define usb_wIndex_endpoint(direction, endpoint_number) \
	( (uint16_t) (((direction) << 7) | (endpoint_number)) )

// - spec sec 9.3.4 (wIndex)
//   - figure 9-3 (format when specifying an interface)
// .-------------------------------------------------------.
// |      D7  | D6  | D5  | D4  | D3  | D2  | D1 | D0      |
// |-------------------------------------------------------|
// |                   interface number                    |
//  >-----------------------------------------------------<
// |      D15 | D14 | D13 | D12 | D11 | D10 | D9 | D8      |
// |-------------------------------------------------------|
// |                 reserved (reset to 0)                 |
// '-------------------------------------------------------'
#define usb_wIndex_interface(interface_number) \
	( (uint16_t) (interface_number) )

// - spec table 9-4 (Standard Request Codes)
#define USB_GET_STATUS         0
#define USB_CLEAR FEATURE      1
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

// - spec sec 9.4.5 (Standard Device Requests / Get Status)
//   - figure 9-4 (information returned by a GetStatus() request to a device)
// .------------------------------------------------------------.
// | D7 | D6 | D5 | D4 | D3 | D2 |       D1      |      D0      |
// |------------------------------------------------------------|
// |    reserved (reset to 0)    | remote wakeup | self powered |
//  >----------------------------------------------------------<
// |        D15 | D14 | D13 | D12 | D11 | D10 | D9 | D8         |
// |------------------------------------------------------------|
// |                   reserved (reset to 0)                    |
// '------------------------------------------------------------'
// - remote wakeup bit: 0 => ability of device to signal remote wakeup disabled
//                           (default)
//                      1 => ability ................................. enabled
// - self powered bit: 0 => device is bus powered, 1=> device is self powered
#define usb_getStatus_device(remote_wakeup, self_powered) \
	( (uint16_t) (((remote_wakeup) << 1) | (self_powered)) )

// - spec sec 9.4.5 (Standard Device Requests / Get Status)
//   - figure 9-5 (information returned by a GetStatus() request to an
//     interface)
// .------------------------------------------------------------.
// |        D7  | D6  | D5  | D4  | D3  | D2  | D1 | D0         |
// |------------------------------------------------------------|
// |                   reserved (reset to 0)                    |
//  >----------------------------------------------------------<
// |        D15 | D14 | D13 | D12 | D11 | D10 | D9 | D8         |
// |------------------------------------------------------------|
// |                   reserved (reset to 0)                    |
// '------------------------------------------------------------'
#define usb_getStatus_interface() ( (uint16_t) 0 )

// - spec sec 9.4.5 (Standard Device Requests / Get Status)
//   - figure 9-6 (information returned by a GetStatus() request to an
//     endpoint)
// .------------------------------------------------------------.
// |        D7  | D6  | D5  | D4  | D3  | D2  | D1 |     D0     |
// |------------------------------------------------------------|
// |                 reserved (reset to 0)         |    halt    |
//  >----------------------------------------------------------<
// |        D15 | D14 | D13 | D12 | D11 | D10 | D9 | D8         |
// |------------------------------------------------------------|
// |                   reserved (reset to 0)                    |
// '------------------------------------------------------------'
// - halt bit: 0 => endpoint not currently halted
//             1 => endpoint currently halted
#define usb_getStatus_endpoint(halt) ( (uint16_t) (halt) )

// - spec sec 9.4.9 (Set Feature)
//   - table 9-7 (Test Mode Selectors)
// - in the case of a SetFeature(TEST_MODE...):
//   - the most significant byte of wIndex is used to specify the test mode
//   - the lower byte of wIndex must be zero, because the recipient must be the
//     device
// (reserved):                                 (0x0000)
#define USB_TEST_MODE_wIndex_Test_J            (0x0100)
#define USB_TEST_MODE_wIndex_Test_K            (0x0200)
#define USB_TEST_MODE_wIndex_Test_SE0_NAK      (0x0300)
#define USB_TEST_MODE_wIndex_Test_Packet       (0x0400)
#define USB_TEST_MODE_wIndex_Test_Force_Enable (0x0500)
// (reserved for standard test selectors):     (0x0600)..(0x3F00)
// (reserved):                                 (0x3F00)..(0xBF00)
// (reserved for vendor-specific test modes):  (0xC000)..(0xFF00)

// - spec sec 9.6.1 (Standard USB Descriptor Definitions / Device)
//   - table 9-8 (Standard Device Descriptor)
struct usb_standard_device_descriptor {
	uint8_t bLength;
	// value: number
	// - size of this descriptor in bytes

	uint8_t bDescriptorType;
	// value: constant
	// - DEVICE Descriptor Type
	// - a high speed capable device will set this to 2.0 (0x0200).  if the
	//   device is full-speed or low-speed only, this version number only
	//   means that it'll send a request error when asked for the
	//   device_qualifier descriptor
	
	uint16_t bcdUSB;
	// value: BCD (binary coded decimal)
	// - usb spec release number
	// - format: 0xJJMN, where JJ = major version, M = minor version,
	//   N = sub-minor version; e.g. version 2.1.3 => 0x0213

	uint8_t bDeviceClass;
	// value: class
	// - class code (assigned by the USB-IF)
	// - 0x00 => each interface within a configuration specifies its own
	//   class information and the various interfaces operate independently
	// - 0x01..0xFE => the device supports different class specifications
	//   on different interfaces and the interfaces may not operate
	//   independently.  this value identifies the class definition used
	//   for the aggregate interfaces
	// - 0xFF => the device class is vendor-specific

	uint8_t bDeviceSubClass;
	// value: subclass
	// - subclass code (assigned by the USB-IF)
	// - qualified by bDeviceClass
	// - if bDeviceClass is reset to 0, this field must be also
	// - if bDeviceClass != 0xFF , all values are reserved for assignment
	//   by the USB-IF

	uint8_t bDeviceProtocol;
	// value: protocol
	// - protocol code (assigned by the USB-IF)
	// - qualified by bDeviceClass and bDeviceSubClass
	// - if a device supports class-specific protocols on a device basis as
	//   opposed to an interface basis, this code identifies the protocols
	//   that the device uses as defined by the specification of the device
	//   class
	// - 0x00 => the device does not use class-specific protocols on a
	//   device basis.  however, it may use class-specific protocols on an
	//   interface basis
	// - 0xFF => the device uses a vendor-specific protocol on a device
	//   basis

	uint8_t bMaxPacketSize0;
	// value: number
	// - max packet size for endpoint 0
	// - only 8, 16, 32, or 64 are valid
	// - if operating at high-speed, the value must be 64

	uint16_t idVendor;
	// value: id
	// - vendor ID (assigned by the USB-IF)

	uint16_t idProduct;
	// value: id
	// - product ID (assigned by the manufacturer)

	uint16_t bcdDevice;
	// value: BCD (binary coded decimal)
	// - device release number

	uint8_t iManufacturer;
	// value: index
	// - index of string descriptor describing manufacturer

	uint8_t iProduct;
	// value: index
	// - index of string descriptor describing product

	uint8_t iSerialNumber;
	// value: index
	// - index of string descriptor describing the device's serial number

	uint8_t bNumConfigurations;
	// value: number
	// - number of possible configurations (at the current operating speed)
};

// - spec sec 9.6.2 (Standard USB Descriptor Definitions / Device_Qualifier)
//   - table 9-9 (Device_Qualifier Descriptor)
// - required if the device has different device information for full-speed and
//   high-speed
// - not valid for a full-speed only device (with a device descriptor version
//   number equal to 0x0200); if requested, the device must respond with a
//   request error
struct usb_device_qualifier_descriptor {
	uint8_t bLength;
	// value: number
	// - size of descriptor

	uint8_t bDescriptorType;
	// value: constant
	// - device qualifier type

	uint16_t bcdUSB;
	// value: BCD (binary coded decimal)
	// - usb spec release number
	// - format: (see note for usb_standard_device_descriptor.bcdUSB)
	// - must be at least 2.0 (0x0200) for this descriptor

	uint8_t bDeviceClass;
	// value: class

	uint8_t bDeviceSubClass;
	// value: subclass

	uint8_t bDeviceProtocol;
	// value: protocol

	uint8_t bMaxPacketSize0;
	// value: number
	// - max packet size for other speed

	uint8_t bNumConfigurations;
	// value: number
	// - number of other-speed configurations

	uint8_t bReserved;
	// value: 0
	// - reserved for future use
};

// - spec sec 9.6.4 (Standard USB Descriptor Definitions /
//   Other_Speed_Configuration)
//   - table 9-10 (Standard Configuration Descriptor)
// TODO


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif

