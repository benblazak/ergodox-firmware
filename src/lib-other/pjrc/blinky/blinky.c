/* LED Blink Example with USB Debug Channel for Teensy USB Development Board
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2008, 2010 PJRC.COM, LLC
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "usb_debug_only.h"
#include "print.h"


// Teensy 2.0: LED is active high
#if defined(__AVR_ATmega32U4__) || defined(__AVR_AT90USB1286__)
#define LED_ON		(PORTD |= (1<<6))
#define LED_OFF		(PORTD &= ~(1<<6))

// Teensy 1.0: LED is active low
#else
#define LED_ON	(PORTD &= ~(1<<6))
#define LED_OFF	(PORTD |= (1<<6))
#endif

#define LED_CONFIG	(DDRD |= (1<<6))
#define CPU_PRESCALE(n)	(CLKPR = 0x80, CLKPR = (n))
#define DIT 80		/* unit time for morse code */

void morse_character(char c);
void morse_P(const char *s);
const unsigned char morse_code_table[];


int main(void)
{
	unsigned char i;

	// set for 16 MHz clock, and make sure the LED is off
	CPU_PRESCALE(0);
	LED_CONFIG;
	LED_OFF;

	// initialize the USB, but don't want for the host to
	// configure.  The first several messages sent will be
	// lost because the PC hasn't configured the USB yet,
	// but we care more about blinking than debug messages!
	usb_init();

	// blink morse code messages!
	while (1) {
		for (i=0; i<6; i++) {
			morse_P(PSTR("SOS"));
			_delay_ms(1500);
		}
		morse_P(PSTR("DOES ANYBODY STILL KNOW MORSE CODE?"));
		_delay_ms(4000);
	}
}

// blink a single character in Morse code
void morse_character(char c)
{
	unsigned char code, count;

	if (c == ' ') {
		print("Space\n");
		_delay_ms(DIT * 7);
		return;
	}
	if (c < 'A' || c > 'Z') {
		print("Opps, unsupported character: ");
		pchar(c);
		print("\n");
		return;	
	}
	print("Char ");
	pchar(c);
	pchar(':');
	code = pgm_read_byte(morse_code_table + (c - 'A'));
	for (count = code & 0x07; count > 0; count--) {
		LED_ON;
		if (code & 0x80) {
			print(" dah");
			_delay_ms(DIT * 3);
		} else {
			print(" dit");
			_delay_ms(DIT);
		}
		LED_OFF;
		_delay_ms(DIT);
		code = code << 1;
	}
	print("\n");
	_delay_ms(DIT * 2);
}

// blink an entire message in Morse code
// the string must be in flash memory (using PSTR macro)
void morse_P(const char *s)
{
	char c;
	
	while (1) {
		c = pgm_read_byte(s++);
		if (!c) break;
		morse_character(c);
	}
	print("\n");
}

// lookup table for all 26 letters.  Upper 5 bits are the pulses
// to send (MSB first), and the lower 3 bits are the number of
// bits to send for this letter.
const unsigned char PROGMEM morse_code_table[] = {
	0x40 + 2,	// A: .-
	0x80 + 4,	// B: -...
	0xA0 + 4,	// C: -.-.
	0x80 + 3,	// D: -..
	0x00 + 1,	// E: .
	0x20 + 4,	// F: ..-.
	0xC0 + 3,	// G: --.
	0x00 + 4,	// H: ....
	0x00 + 2,	// I: ..
	0x70 + 4,	// J: .---
	0xA0 + 3,	// K: -.-
	0x40 + 4,	// L: .-..
	0xC0 + 2,	// M: --
	0x80 + 2,	// N: -.
	0xE0 + 3,	// O: ---
	0x60 + 4,	// P: .--.
	0xD0 + 4,	// Q: --.-
	0x40 + 3,	// R: .-.
	0x00 + 3,	// S: ...
	0x80 + 1,	// T: -
	0x20 + 3,	// U: ..-
	0x10 + 4,	// V: ...-
	0x60 + 3,	// W: .--
	0x90 + 4,	// X: -..-
	0xB0 + 4,	// Y: -.--
	0xC0 + 4	// Z: --..
};

