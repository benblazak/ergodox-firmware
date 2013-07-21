/**                                                                 description
 * The PJRC USB keyboard interface
 *
 * See the '.c' file for copyright and such
 *
 * Modified 2013, Ben Blazak
 *
 * Should be included only by those files that wrap parts of it to conform with
 * '.../firmware/lib/usb.h'
 *
 * Notes:
 * - 'description' added
 * - `usb_keyboard_press()` removed
 * - the empty macros for `usb_debug_putchar()` and `usb_debug_flush_output()`
 *   removed
 * - keycode macros removed
 */

// ----------------------------------------------------------------------------

#ifndef usb_serial_h__
#define usb_serial_h__

#include <stdint.h>

// general
void usb_init(void);			// initialize everything
uint8_t usb_configured(void);		// is the USB port configured

// keyboard
int8_t usb_keyboard_send(void);
extern uint8_t keyboard_modifier_keys;
extern uint8_t keyboard_keys[6];
extern volatile uint8_t keyboard_leds;

// mouse
extern uint8_t usb_mouse_protocol;
extern uint8_t mouse_buttons;

int8_t usb_mouse_send(int8_t x, int8_t y, int8_t wheel_v, int8_t wheel_h, uint8_t buttons);
void usb_mouse_buttons(uint8_t buttons);

// ----------------------------------------------------------------------------

// Everything below this point is only intended for usb_serial.c
#ifdef USB_SERIAL_PRIVATE_INCLUDE
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#define EP_TYPE_CONTROL			0x00
#define EP_TYPE_BULK_IN			0x81
#define EP_TYPE_BULK_OUT		0x80
#define EP_TYPE_INTERRUPT_IN		0xC1
#define EP_TYPE_INTERRUPT_OUT		0xC0
#define EP_TYPE_ISOCHRONOUS_IN		0x41
#define EP_TYPE_ISOCHRONOUS_OUT		0x40

#define EP_SINGLE_BUFFER		0x02
#define EP_DOUBLE_BUFFER		0x06

#define EP_SIZE(s)	((s) == 64 ? 0x30 :	\
			((s) == 32 ? 0x20 :	\
			((s) == 16 ? 0x10 :	\
			             0x00)))

#define MAX_ENDPOINT     4
#define UERST_MASK       0x1E

#define LSB(n) (n & 255)
#define MSB(n) ((n >> 8) & 255)

#if defined(__AVR_AT90USB162__)
#define HW_CONFIG() 
#define PLL_CONFIG() (PLLCSR = ((1<<PLLE)|(1<<PLLP0)))
#define USB_CONFIG() (USBCON = (1<<USBE))
#define USB_FREEZE() (USBCON = ((1<<USBE)|(1<<FRZCLK)))
#elif defined(__AVR_ATmega32U4__)
#define HW_CONFIG() (UHWCON = 0x01)
#define PLL_CONFIG() (PLLCSR = 0x12)
#define USB_CONFIG() (USBCON = ((1<<USBE)|(1<<OTGPADE)))
#define USB_FREEZE() (USBCON = ((1<<USBE)|(1<<FRZCLK)))
#elif defined(__AVR_AT90USB646__)
#define HW_CONFIG() (UHWCON = 0x81)
#define PLL_CONFIG() (PLLCSR = 0x1A)
#define USB_CONFIG() (USBCON = ((1<<USBE)|(1<<OTGPADE)))
#define USB_FREEZE() (USBCON = ((1<<USBE)|(1<<FRZCLK)))
#elif defined(__AVR_AT90USB1286__)
#define HW_CONFIG() (UHWCON = 0x81)
#define PLL_CONFIG() (PLLCSR = 0x16)
#define USB_CONFIG() (USBCON = ((1<<USBE)|(1<<OTGPADE)))
#define USB_FREEZE() (USBCON = ((1<<USBE)|(1<<FRZCLK)))
#endif

// standard control endpoint request types
#define GET_STATUS			0
#define CLEAR_FEATURE			1
#define SET_FEATURE			3
#define SET_ADDRESS			5
#define GET_DESCRIPTOR			6
#define GET_CONFIGURATION		8
#define SET_CONFIGURATION		9
#define GET_INTERFACE			10
#define SET_INTERFACE			11
// HID (human interface device)
#define HID_GET_REPORT			1
#define HID_GET_IDLE			2
#define HID_GET_PROTOCOL		3
#define HID_SET_REPORT			9
#define HID_SET_IDLE			10
#define HID_SET_PROTOCOL		11
#define HID_REPORT_INPUT		1
#define HID_REPORT_OUTPUT		2
#define HID_REPORT_FEATURE		3
// CDC (communication class device)
#define CDC_SET_LINE_CODING		0x20
#define CDC_GET_LINE_CODING		0x21
#define CDC_SET_CONTROL_LINE_STATE	0x22
// HID feature selectors
#define DEVICE_REMOTE_WAKEUP		1
#define ENDPOINT_HALT			0
#define TEST_MODE			2


/*------------------------------------------------------------------*
 * Keyboard descriptor setting
 *------------------------------------------------------------------*/
#define KBD_INTERFACE		0
#define KBD_ENDPOINT		1
#define KBD_SIZE		8
#define KBD_BUFFER		EP_DOUBLE_BUFFER
#define KBD_REPORT_KEYS		(KBD_SIZE - 2)

// secondary keyboard
#ifdef NKRO_ENABLE
#define KBD2_INTERFACE		2
#define KBD2_ENDPOINT		3
#define KBD2_SIZE		16
#define KBD2_BUFFER		EP_DOUBLE_BUFFER
#define KBD2_REPORT_KEYS	(KBD2_SIZE - 1)
#endif

// mouse
#define MOUSE_INTERFACE		1
#define MOUSE_ENDPOINT		2
#define MOUSE_SIZE		8
#define MOUSE_BUFFER		EP_DOUBLE_BUFFER

#endif
#endif
