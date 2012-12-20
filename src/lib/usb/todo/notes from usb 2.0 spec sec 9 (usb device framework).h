/* ----------------------------------------------------------------------------
 * Notes from the USB 2.0 specification
 *
 * Written as a header file because I was going to actually use it.  Changed my
 * mind because it's simpler to use uint8_t arrays for things than to use
 * structs.  it's also easier i think to keep the least and most significant
 * bits of uint16_t values separate initially instead of separating them later.
 * Kept it as a header because it looks cleaner this way than i could make it
 * look as an .md file.
 *
 * - conventions from the spec
 *   - variable prefixes
 *     - 'b'   : bits or bytes; dependent on context
 *     - 'bcd' : binary-coded decimal
 *     - 'bm'  : bitmap
 *     - 'd'   : descriptor
 *     - 'i'   : index
 *     - 'w'   : word
 *
 * - conventions used in this file
 *   - everything prefixed with or `USB_` (for non-function-like macros) or
 *     `usb_` (for everything else)
 *
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef USB_DATA_STRUCTURES_h
	#define USB_DATA_STRUCTURES_h

	#pragma pack(push)
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


#include <stdint.h>


// ----------------------------------------------------------------------------

/* - spec sec 9.3 (USB Device Requests)
 *   - table 9-2 (Format of Setup Data)
 */
struct usb_setup_data {
	uint8_t  bmRequestType;
	/* value: bitmap
	 * - data transfer direction, type, recipient
	 *   (see macros below)
	 */

	uint8_t  bRequest;
	/* value: value
	 * - type of request (depending on bmRequestType)
	 *   (see spec table 9-3 (Standard Device Requests))
	 */

	uint16_t wValue;
	/* value: value
	 * - varies according to request; used to pass a request specific
	 *   parameter to the device
	 */

	uint16_t wIndex;
	/* value: index or offset
	 * - varies according to request; often used to specify an endpoint or
	 *   an interface
	 *   (see spec figure 9-2 and 9-3, copied below)
	 */

	uint16_t wLength;
	/* value: count
	 * - number of bytes to transfer if there is a data stage
	 */
};


/* - spec sec 9.3 (USB Device Requests)
 *   - table 9-2 (Format of Setup Data)
 *     - bmRequestType
 *
 * .-------------------------------------------------------.
 * |     D7     | D6 | D5 |     D4 | D3 | D2 | D1 | D0     |
 * |-------------------------------------------------------|
 * | direction  |  type   |           recipient            |
 * '-------------------------------------------------------'
 *
 * - direction: 0 => host to device
 *              1 => device to host
 *
 * - type: 0 => standard
 *         1 => class
 *         2 = vendor
 *         3 = reserved
 *
 * - recipient: 0 => device
 *              1 => interface
 *              2 => endpoint
 *              3 => other
 *              4..31 => reserved
 */
// --- data transfer direction
#define usb_bmRequestType_hostToDevice(val) (((val) & (0b1<<7)) == (0<<7))
#define usb_bmRequestType_deviceToHost(val) (((val) & (0b1<<7)) == (1<<7))
// --- type
#define usb_bmRequestType_standard(val)     (((val) & (0b11<<5)) == (0<<5))
#define usb_bmRequestType_class(val)        (((val) & (0b11<<5)) == (1<<5))
#define usb_bmRequestType_vendor(val)       (((val) & (0b11<<5)) == (2<<5))
#define usb_bmRequestType_reserved(val)     (((val) & (0b11<<5)) == (3<<5))
// --- recipient
#define usb_bmRequestType_device(val)       (((val) & (0b11111<<0)) == (0<<0))
#define usb_bmRequestType_interface(val)    (((val) & (0b11111<<0)) == (1<<0))
#define usb_bmRequestType_endpoint(val)     (((val) & (0b11111<<0)) == (2<<0))
#define usb_bmRequestType_other(val)        (((val) & (0b11111<<0)) == (3<<0))
#define usb_bmRequestType_reserved(val)     (((val) & (0b11100<<0)) != (0<<0))


/* - spec sec 9.3.4 (wIndex)
 *   - figure 9-2 (format when specifying an endpoint)
 *
 * .-------------------------------------------------------.
 * |    D7     |     D6 | D5 | D4      | D3 | D2 | D1 | D0 |
 * |-------------------------------------------------------|
 * | direction | reserved (reset to 0) |  endpoint number  |
 *  >-----------------------------------------------------<
 * |      D15 | D14 | D13 | D12 | D11 | D10 | D9 | D8      |
 * |-------------------------------------------------------|
 * |                 reserved (reset to 0)                 |
 * '-------------------------------------------------------'
 *
 * - direction: 0 => out (to device), 1 => in (to host)
 */
#define usb_wIndex_endpoint(direction, endpoint_number) \
	( (uint16_t) (((direction)<<7) | (endpoint_number)) )


/* - spec sec 9.3.4 (wIndex)
 *   - figure 9-3 (format when specifying an interface)
 *
 * .-------------------------------------------------------.
 * |      D7  | D6  | D5  | D4  | D3  | D2  | D1 | D0      |
 * |-------------------------------------------------------|
 * |                   interface number                    |
 *  >-----------------------------------------------------<
 * |      D15 | D14 | D13 | D12 | D11 | D10 | D9 | D8      |
 * |-------------------------------------------------------|
 * |                 reserved (reset to 0)                 |
 * '-------------------------------------------------------'
 */
#define usb_wIndex_interface(interface_number) \
	( (uint16_t) (interface_number) )


// ----------------------------------------------------------------------------

/* - spec table 9-4 (Standard Request Codes)
 */
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

/* - spec table 9-5 (Descriptor Types)
 */
#define USB_DEVICE                    1
#define USB_CONFIGURATION             2
#define USB_STRING                    3
#define USB_INTERFACE                 4
#define USB_ENDPOINT                  5
#define USB_DEVICE_QUALIFIER          6
#define USB_OTHER_SPEED_CONFIGURATION 7
#define USB_INTERFACE_POWER           8

/* - spec table 9-6 (Standard Feature Selectors)
 */
#define USB_DEVICE_REMOTE_WAKEUP 1  // recipient: device
#define USB_ENDPOINT_HALT        0  // recipient: endpoint
#define USB_TEST_MODE            2  // recipient: device


/* - spec sec 9.4.5 (Standard Device Requests / Get Status)
 *   - figure 9-4 (information returned by a GetStatus() request to a device)
 *
 * .------------------------------------------------------------.
 * | D7 | D6 | D5 | D4 | D3 | D2 |       D1      |      D0      |
 * |------------------------------------------------------------|
 * |    reserved (reset to 0)    | remote wakeup | self powered |
 *  >----------------------------------------------------------<
 * |        D15 | D14 | D13 | D12 | D11 | D10 | D9 | D8         |
 * |------------------------------------------------------------|
 * |                   reserved (reset to 0)                    |
 * '------------------------------------------------------------'
 *
 * - remote wakeup: 0 => ability of device to signal remote wakeup disabled
 *                       (default)
 *                  1 => ability ................................. enabled
 *
 * - self powered: 0 => device is bus powered
 *                 1 => device is self powered
 */
#define usb_getStatus_device(remote_wakeup, self_powered) \
	( (uint16_t) (((remote_wakeup)<<1) | (self_powered)) )


/* - spec sec 9.4.5 (Standard Device Requests / Get Status)
 *   - figure 9-5 (information returned by a GetStatus() request to an
 *     interface)
 *
 * .------------------------------------------------------------.
 * |        D7  | D6  | D5  | D4  | D3  | D2  | D1 | D0         |
 * |------------------------------------------------------------|
 * |                   reserved (reset to 0)                    |
 *  >----------------------------------------------------------<
 * |        D15 | D14 | D13 | D12 | D11 | D10 | D9 | D8         |
 * |------------------------------------------------------------|
 * |                   reserved (reset to 0)                    |
 * '------------------------------------------------------------'
 */
#define usb_getStatus_interface() ( (uint16_t) 0 )


/* - spec sec 9.4.5 (Standard Device Requests / Get Status)
 *   - figure 9-6 (information returned by a GetStatus() request to an
 *     endpoint)
 *
 * .------------------------------------------------------------.
 * |        D7  | D6  | D5  | D4  | D3  | D2  | D1 |     D0     |
 * |------------------------------------------------------------|
 * |                 reserved (reset to 0)         |    halt    |
 *  >----------------------------------------------------------<
 * |        D15 | D14 | D13 | D12 | D11 | D10 | D9 | D8         |
 * |------------------------------------------------------------|
 * |                   reserved (reset to 0)                    |
 * '------------------------------------------------------------'
 *
 * - halt: 0 => endpoint not currently halted
 *             1 => endpoint currently halted
 */
#define usb_getStatus_endpoint(halt) ( (uint16_t) (halt) )


/* - spec sec 9.4.9 (Set Feature)
 *   - table 9-7 (Test Mode Selectors)
 *
 * - in the case of a SetFeature(TEST_MODE...):
 *   - the most significant byte of wIndex is used to specify the test mode
 *   - the lower byte of wIndex must be zero, because the recipient must be the
 *     device
 */
// (reserved):                                              (0x0000)
#define USB_TEST_MODE_wIndex_Test_J            ( (uint16_t) (0x0100) )
#define USB_TEST_MODE_wIndex_Test_K            ( (uint16_t) (0x0200) )
#define USB_TEST_MODE_wIndex_Test_SE0_NAK      ( (uint16_t) (0x0300) )
#define USB_TEST_MODE_wIndex_Test_Packet       ( (uint16_t) (0x0400) )
#define USB_TEST_MODE_wIndex_Test_Force_Enable ( (uint16_t) (0x0500) )
// (reserved for standard test selectors):                  (0x0600)..(0x3F00)
// (reserved):                                              (0x3F00)..(0xBF00)
// (reserved for vendor-specific test modes):               (0xC000)..(0xFF00)


// ----------------------------------------------------------------------------

/* - spec sec 9.6.1 (Standard USB Descriptor Definitions / Device)
 *   - table 9-8 (Standard Device Descriptor)
 */
struct usb_device_descriptor {
	uint8_t bLength;
	/* value: number
	 * - size of this descriptor in bytes
	 */

	uint8_t bDescriptorType;
	/* value: constant
	 * - DEVICE Descriptor Type
	 * - a high speed capable device will set this to 2.0 (0x0200).  if the
	 *   device is full-speed or low-speed only, this version number only
	 *   means that it'll send a request error when asked for the
	 *   device_qualifier descriptor
	 */
	
	uint16_t bcdUSB;
	/* value: binary coded decimal
	 * - usb spec release number
	 * - format: 0xJJMN, where JJ = major version, M = minor version,
	 *   N = sub-minor version; e.g. version 2.1.3 => 0x0213
	 */

	uint8_t bDeviceClass;
	/* value: class
	 * - class code (assigned by the USB-IF)
	 * - 0x00 => each interface within a configuration specifies its own
	 *   class information and the various interfaces operate independently
	 * - 0x01..0xFE => the device supports different class specifications
	 *   on different interfaces and the interfaces may not operate
	 *   independently.  this value identifies the class definition used
	 *   for the aggregate interfaces
	 * - 0xFF => the device class is vendor-specific
	 */

	uint8_t bDeviceSubClass;
	/* value: subclass
	 * - subclass code (assigned by the USB-IF)
	 * - qualified by bDeviceClass
	 * - if bDeviceClass is reset to 0, this field must be also
	 * - if bDeviceClass != 0xFF , all values are reserved for assignment
	 *   by the USB-IF
	 */

	uint8_t bDeviceProtocol;
	/* value: protocol
	 * - protocol code (assigned by the USB-IF)
	 * - qualified by bDeviceClass and bDeviceSubClass
	 * - if a device supports class-specific protocols on a device basis as
	 *   opposed to an interface basis, this code identifies the protocols
	 *   that the device uses as defined by the specification of the device
	 *   class
	 * - 0x00 => the device does not use class-specific protocols on a
	 *   device basis.  however, it may use class-specific protocols on an
	 *   interface basis
	 * - 0xFF => the device uses a vendor-specific protocol on a device
	 *   basis
	 */

	uint8_t bMaxPacketSize0;
	/* value: number
	 * - max packet size for endpoint 0
	 * - only 8, 16, 32, or 64 are valid
	 * - if operating at high-speed, the value must be 64
	 */

	uint16_t idVendor;
	/* value: id
	 * - vendor ID (assigned by the USB-IF)
	 */

	uint16_t idProduct;
	/* value: id
	 * - product ID (assigned by the manufacturer)
         */

	uint16_t bcdDevice;
	/* value: binary coded decimal
	 * - device release number
	 */

	uint8_t iManufacturer;
	/* value: index
	 * - index of string descriptor describing manufacturer
	 */

	uint8_t iProduct;
	/* value: index
	 * - index of string descriptor describing product
	 */

	uint8_t iSerialNumber;
	/* value: index
	 * - index of string descriptor describing the device's serial number
	 */

	uint8_t bNumConfigurations;
	/* value: number
	 * - number of possible configurations (at the current operating speed)
	 */
};


// ----------------------------------------------------------------------------

/* - spec sec 9.6.2 (Standard USB Descriptor Definitions / Device_Qualifier)
 *   - table 9-9 (Device_Qualifier Descriptor)
 *
 * - required if the device has different device information for full-speed and
 *   high-speed
 *
 * - not valid for a full-speed only device (with a device descriptor version
 *   number equal to 0x0200); if requested, the device must respond with a
 *   request error
 */
struct usb_device_qualifier_descriptor {
	uint8_t bLength;
	/* value: number
	 * - size of descriptor
	 */

	uint8_t bDescriptorType;
	/* value: constant
	 * - device qualifier type
	 */

	uint16_t bcdUSB;
	/* value: binary coded decimal
	 * - usb spec release number
	 * - format: (see note for usb_device_descriptor.bcdUSB)
	 * - must be at least 2.0 (0x0200) for this descriptor
	 */

	uint8_t bDeviceClass;
	/* value: class
	 */

	uint8_t bDeviceSubClass;
	/* value: subclass
	 */

	uint8_t bDeviceProtocol;
	/* value: protocol
	 */

	uint8_t bMaxPacketSize0;
	/* value: number
	 * - max packet size for other speed
	 */

	uint8_t bNumConfigurations;
	/* value: number
	 * - number of other-speed configurations
	 */

	uint8_t bReserved;
	/* value: 0
	 * - reserved for future use
	 */
};


// ----------------------------------------------------------------------------

/* - spec sec 9.6.3 (Standard USB Descriptor Definitions / Configuration)
 *   - table 9-10 (Standard Configuration Descriptor)
 *
 * - spec sec 9.6.4 (Standard USB Descriptor Definitions /
 *   Other_Speed_Configuration)
 *   - table 9-11 (Other_Speed_Configuration Descriptor)
 *
 * - both descriptors have the same structure.  the only specified difference
 *   is the value of the bDescriptorType constant.
 */
struct usb_configuration_descriptor {
	uint8_t bLength;
	/* value: number
	 * - size of this descriptor in bytes

	uint8_t bDescriptorType;
	 * value: constant
	 * - CONFIGURATION Descriptor Type
	 *   (for Standard Configuration Descriptor)
	 * - OTHER_SPEED_CONFIGURATION Type
	 *   (for Other Speed Configuration Descriptor)
	 */

	uint16_t wTotalLength;
	/* value: number
	 * - total length of data returned for this configuration.  includes
	 *   the combined length of all descriptors (configuration, interface,
	 *   endpoint, and class- or vendor-specific) returned for this
	 *   configuration.
	 */

	uint8_t bNumInterfaces;
	/* value: number
	 * - number of interfaces supported by this configuration
	 */

	uint8_t bConfigurationValue;
	/* value: number
	 * - value to use as an argument to the SetConfiguration() request to
	 *   select this configuration
	 */

	uint8_t iConfiguration;
	/* value: index
	 * - index of string descriptor describing this configuration
	 */

	uint8_t bmAttributes;
	/* value: bitmap
	 * - self-powered, remote wakeup
	 *   (see macro below)
	 */

	uint8_t bMaxPower;
	/* value: mA
	 * - max power consumption of the USB device from the bus
	 *   (configuration specific) (when device is fully operational)
	 * - format: expressed in 2 mA units (i.e. value=50 => 100mA)
	 * - note: a device configuration reports whether the configuration is
	 *   bus-powered or self-powered.  device status reports whether the
	 *   device is currently self-powered.  if a device is disconnected
	 *   from its external power source, it updates device status to
	 *   indicate that.  it may not increase its power draw from the bus
	 *   beyond the amount reported by its configuration.  if it can
	 *   continue to operate, it does so.  if not, it fails operations it
	 *   can no longer support, and the host software can determine the
	 *   cause of failure by checking the status and noting the loss of the
	 *   device's external power.
	 */
};


/* - spec sec 9.6.3 (Standard USB Descriptor Definitions / Configuration)
 *   - table 9-10 (Standard Configuration Descriptor)
 *     - bmAttributes
 *
 * .--------------------------------------------------------.
 * |     D7     |   D6    |   D5   | D4 | D3 | D2 | D1 | D0 |
 * |--------------------------------------------------------|
 * |  reserved  |  self   | remote |        reserved        |
 * | (set to 1) | powered | wakeup |      (reset to 0)      |
 * '--------------------------------------------------------'
 *
 * - D7: must be set to 1 for historical reasons
 *
 * - self powered: 0 => false
 *                 1 => true
 *   - a device configuration that uses both bus and local power must report a
 *     non-zero value in bMaxPower (to indicate the amount of bus power
 *     required) and set D6 = 1
 *
 * - remote wakeup: 0 => not supported by configuration
 *                  1 => supported by configuration
 */
#define usb_configuration_bmAttributes(self_powered, remote_wakeup) \
	( (uint8_t) ((1<<7) | ((self_powered)<<6) | ((remote_wakeup)<<5)) )


// ----------------------------------------------------------------------------

/* - spec sec 9.6.5 (Standard USB Descriptor Definitions / Interface)
 *   - table 9-12 (Standard Interface Descriptor)
 */
struct usb_interface_descriptor {
	uint8_t bLength;
	/* value: number
	 * - size of this descriptor in bytes
	 */

	uint8_t bDescriptorType;
	/* value: constant
	 * - INTERFACE Descriptor Type
	 */

	uint8_t bInterfaceNumber;
	/* value: number
	 * - number of this interface
	 * - zero-based value identifying the index in the array of concurrent
	 *   interfaces supported by this configuration
	 */

	uint8_t bAlternateSetting;
	/* value: number
	 * - value used to select this alternate setting for the interface
	 *   identified in the prior field
	 */

	uint8_t bNumEndpoints;
	/* value: number
	 * - number of endpoints used by this interface (excluding endpoint
	 *   zero)
	 * - if this value is zero, this interface only uses the Default
	 *   Control Pipe
	 */

	uint8_t bInterfaceClass;
	/* value: class
	 * - class code (assigned by the USB-IF)
	 * - 0x00 => reserved for future standardization
	 * - 0xFF => interface class is vendor specific
	 * - [others] => reserved for assignment by the USB-IF
	 */

	uint8_t bInterfaceSubClass;
	/* value: subclass
	 * - subclass code (assigned by the USB-IF)
	 * - qualified by the value of the bInterfaceClass field
	 * - if the bInterfaceClass field is reset to zero, this field must be
	 *   also
	 * - if the bInterfaceClass field is not set to 0xFF, all values are
	 *   reserved for assignment by the USB-IF
	 */

	uint8_t bInterfaceProtocol;
	/* value: protocol
	 * - protocol code (assigned by the USB)
	 * - qualified by the values of the bInterfaceClass and
	 *   bInterfaceSubClass fields
	 * - if an interface supports class-specific requests, this code
	 *   identifies the protocols that the device uses as defined by the
	 *   specification of the device class.
	 * - 0x00 => the device does not use a class-specific protocol on this
	 *   interface
	 * - 0xFF => the device uses a vendor-specific protocol for this
	 *   interface
	 */

	uint8_t iInterface;
	/* value: index
	 * - index of string descriptor describing this interface
	 */
};


// ----------------------------------------------------------------------------

/* - spec sec 9.6.6 (Standard USB Descriptor Definitions / Endpoint)
 *   - table 9-13 (Standard Endpoint Descriptor)
 *
 * - a feedback endpoint (explicit or implicit) needs to be associated with one
 *   (or more) isochronous data endpoints to which it provides feedback
 *   service.  the association is based on endpoint number matching.  a
 *   feedback endpoint always has the opposite direction from the data
 *   endpoint(s) it services.  if multiple data endpoints are to be serviced by
 *   the same feedback endpoint, the data endpoints must have ascending ordered
 *   (but not necessarily consecutive) endpoint numbers.  the first data
 *   endpoint and the feedback endpoint must have the same endpoint number (and
 *   opposite direction).  this ensures that a data endpoint can uniquely
 *   identify its feedback endpoint by searching for the first feedback
 *   endpoint that has an endpoint number equal or less than its own endpoint
 *   number.
 *   - see spec figures 9-7 and 9-8
 */
struct usb_endpoint_descriptor {
	uint8_t bLength;
	/* value: number
	 * - size of this descriptor in bytes
	 */

	uint8_t bDescriptorType;
	/* value: constant
	 * - ENDPOINT Descriptor Type
	 */

	uint8_t bEndpointAddress;
	/* value: endpoint
	 * - the address and direction of the endpoint described
	 *   (see macro below)
	 */

	uint8_t bmAttributes;
	/* value: bitmap
	 * - endpoint's attributes when it is configured using the
	 *   bConfigurationValue
	 *   - includes: transfer type
	 *   - if transfer type == isochronous, also includes:
	 *     synchronization type, usage type
	 * - (see spec chapter 5 for more information)
	 * - (see macros below)
	 */

	uint16_t wMaxPacketSize;
	/* value: number
	 * - max packet size this endpoint is capable of sending or receiving
	 *   when this configuration is selected
	 * - for isochronous endpoints, this value is used to reserve the bus
	 *   time in the schedule, required for the per-(micro)frame data
	 *   payloads.  the pipe may, on an ongoing basis, actually use less
	 *   bandwidth than reserved.  the device reports, if necessary, the
	 *   actual bandwidth used via its normal, non-USB defined mechanisms
	 * - (see spec chapter 5 for more information)
	 * - (see macro below)
	 */

	uint8_t bInterval;
	/* value: number
	 * - interval for polling endpoint for data transfers
	 * - expressed in frames or microframes, depending on the device
	 *   operating speed (i.e. either 1 ms or 125 μs units)
	 * - for (full|high)-speed isochronous endpoints and high-speed
	 *   interrupt endpoints, this value must be between 1..16 .  this
	 *   value is used as the exponent for a 2^(bInterval-1) value (e.g. a
	 *   bInterval of 4 => a period of 8 == 2^(4-1))
	 * - for (full|low)-speed interrupt endpoints, this value may be
	 *   between 1..255
	 * - for high-speed bulk/control OUT endpoints, this value must specify
	 *   the max NAK rate of the endpoint.  a value of 0 => the endpoint
	 *   never NAKs.  other values indicate at most 1 NAK each bInterval
	 *   number of microframes.  this value must be between 0..255
	 * - for high-speed bulk and control OUT endpoints, this field is only
	 *   used for compliance purposes (the host controller is not required
	 *   to change its behavior based on the value in this field)
	 * - (see spec chapter 5 description of periods for more detail)
	 */
};


/* - spec sec 9.6.6 (Standard USB Descriptor Definitions / Endpoint)
 *   - table 9-13 (Standard Endpoint Descriptor)
 *     - bEndpointAddress
 *
 * .-------------------------------------------------------.
 * |     D7    |     D6 | D5 | D4      | D3 | D2 | D1 | D0 |
 * |-------------------------------------------------------|
 * | direction | reserved (reset to 0) |  endpoint number  |
 * '-------------------------------------------------------'
 *
 * - D7: 0 => OUT endpoint
 *       1 => IN endpoint
 *   - ignored for control endpoints
 */
#define usb_endpoint_bEndpointAddress(direction, endpoint_number) \
	( (uint8_t) ((direction)<<7) | (endpoint_number) )


/* - spec sec 9.6.6 (Standard USB Descriptor Definitions / Endpoint)
 *   - table 9-13 (Standard Endpoint Descriptor)
 *     - bmAttributes
 *
 * .------------------------------------------------------------------------.
 * |   D7 | D6    |     D5 | D4      |       D3 | D2        |    D1 | D0    |
 * |------------------------------------------------------------------------|
 * |   reserved   |    usage type    | synchronization type | transfer type |
 * | (reset to 0) | (if isochronous) |   (if isochronous)   |               |
 * |              |(else reset to 0) |  (else reset to 0)   |               |
 * '------------------------------------------------------------------------'
 *
 * - transfer type: 0b00 => control
 *                  0b01 => isochronous
 *                  0b10 => bulk
 *                  0b11 => interrupt
 *
 * - synchronization type: 0b00 => no synchronization
 *                         0b01 => asynchronous
 *                         0b10 => adaptive
 *                         0b11 => synchronous
 *   - if transfer type != isochronous, field is reset to 0
 *
 * - usage type: 0b00 => data endpoint
 *               0b01 => feedback endpoint
 *               0b10 => implicit feedback data endpoint
 *               0b11 => reserved
 *   - if transfer type != isochronous, field is reset to 0
 *
 * - if usage type == feedback endpoint, then transfer type must be isochronous
 *   and synchronization type must be no synchronization
 */
#define usb_endpoint_bmAttributes(transfer_type) \
	( (uint8_t) (transfer_type) )
#define usb_endpoint_bmAttributes_isochronous( \
		synchronization_type, usage_type ) \
	( (uint8_t) (0b01 | ((synchronization_type)<<2) | ((usage_type)<<4)) )


/* - spec sec 9.6.6 (Standard USB Descriptor Definitions / Endpoint)
 *   - table 9-13 (Standard Endpoint Descriptor)
 *     - wMaxPacketSize
 *
 * .-----------------------------------------------------------------.
 * |             D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0               |
 * |-----------------------------------------------------------------|
 * |                         max packet size                         |
 * |                            (D10..D0)                            |
 * |                                                                 |
 *  >---------------------------------------------------------------<
 * | D15 | D14 | D13 |          D12 | D11          |  D10 | D9 | D8  |
 * |-----------------------------------------------------------------|
 * |    reserved     |    number of additional     | max packet size |
 * |  (reset to 0)   |  transaction opportunities  |    (D10..D0)    |
 * |                 |       per microframe        |   (continued)   |
 * |                 | (for high-speed isochronous |                 |
 * |                 |   and interrupt endpoints)  |                 |
 * '-----------------------------------------------------------------'
 *
 * - D12..D11 (additional transaction opportunities for each microframe
 *   specified by bInterval):
 *       0b00 => none (1 transaction per microframe)
 *            => max packet size: 1..1024
 *       0b01 => 1 additional (2 per microframe)
 *            => max packet size: 513..1024
 *       0b10 => 2 additional (3 per microframe)
 *            => max packet size: 683..1024
 *       0b11 => reserved
 *   - for high-speed isochronous and interrupt endpoints only.  else reset to
 *     0, and max packet size can be any allowed value (as defined in spec
 *     chapter 5)
 */
#define usb_endpoint_wMaxPacketSize(adtl_trans_ops, max_packet_size) \
	( (uint16_t) (((adtl_trans_ops)<<11) | max_packet_size) )


// ----------------------------------------------------------------------------

/* - spec sec 9.6.7 (Standard USB Descriptor Definitions / String)
 *   - table 9-15 (String Descriptor Zero, Specifying Languages Supported by
 *     the Device)
 *
 * - string descriptors are optional.  if a device does not support them, all
 *   references to them within all descriptors must be reset to 0 .
 *
 * - string descriptors use unicode encodings (as defined in version 3.0 of the
 *   unicode standard)
 *
 * - the strings may support multiple languages.  when requesting a string
 *   descriptor, the requester specifies the desired language using a 16 bit
 *   language ID (LANGID) (defined by the USB-IF; see
 *   <http://www.usb.org/developers/docs.html>).
 *
 * - string index 0 for all languages returns a string descriptor that contains
 *   an array of two-byte LANGID codes supported by the device.  USB devices
 *   that omit all string descriptors must not return an array of LANGID codes.
 */
struct usb_string_descriptor_zero {
	uint8_t bLength;
	/* value: N+2
	 * - the size of this descriptor in bytes (which equals the size of the
	 *   array of LANGIDs (in bytes) plus two)
	 */

	uint8_t bDescriptorType;
	/* value: constant
	 * - STRING Descriptor Type
	 */

	uint16_t (* wLANGID_ptr)[];
	/* value: a pointer to the array of supported LANGID codes
	 * - note: these must be transmitted as part of the descriptor; a
	 *   pointer is used here to avoid using variable length struct members
	 *   + malloc()
	 */
};

/* - spec sec 9.6.7 (Standard USB Descriptor Definitions / String)
 *   - table 9-16 (UNICODE String Descriptor)
 */
struct usb_string_descriptor {
	uint8_t bLength;
	/* value: number
	 * - the size of this descriptor in bytes (which equals the size of the
	 *   string (in bytes) plus two)
	 */

	uint8_t bDescriptorType;
	/* value: constant
	 * - STRING Descriptor Type
	 */

	uint8_t bString;
	/* value: number
	 * - UNICODE encoded string
	 */
};


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
	#pragma pack(pop)
#endif

