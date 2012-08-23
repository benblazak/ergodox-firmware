/* ----------------------------------------------------------------------------
 * key functions : device specific : code
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include <avr/interrupt.h>
#include <util/delay.h>
#include "../public.h"


// ----------------------------------------------------------------------------
// descriptions
// ----------------------------------------------------------------------------

/*
 * [name]
 *   Jump to Bootloader
 *
 * [description]
 *   For reflashing the controller
 */
void kbfun_jump_to_bootloader(void);


// ----------------------------------------------------------------------------
#if MAKEFILE_BOARD == teensy-2-0
// ----------------------------------------------------------------------------

// from PJRC (slightly modified)
// <http://www.pjrc.com/teensy/jump_to_bootloader.html>
void kbfun_jump_to_bootloader(void) {
	// --- for all Teensy boards ---

	cli();

	// disable watchdog, if enabled
	// disable all peripherals
	UDCON = 1;
	USBCON = (1<<FRZCLK);  // disable USB
	UCSR1B = 0;
	_delay_ms(5);

	// --- Teensy 2.0 specific ---

	EIMSK = 0; PCICR = 0; SPCR = 0; ACSR = 0; EECR = 0; ADCSRA = 0;
	TIMSK0 = 0; TIMSK1 = 0; TIMSK3 = 0; TIMSK4 = 0; UCSR1B = 0; TWCR = 0;
	DDRB = 0; DDRC = 0; DDRD = 0; DDRE = 0; DDRF = 0; TWCR = 0;
	PORTB = 0; PORTC = 0; PORTD = 0; PORTE = 0; PORTF = 0;
	asm volatile("jmp 0x7E00");
}


// ----------------------------------------------------------------------------
#else
// ----------------------------------------------------------------------------

void kbfun_jump_to_bootloader(void) {}


// ----------------------------------------------------------------------------
#endif
// ----------------------------------------------------------------------------

