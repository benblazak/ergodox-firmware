/* ----------------------------------------------------------------------------
 * ergoDOX controller: Teensy 2.0 specific exports
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak
 * Released under The MIT License (MIT) (see "license.md") at
 * <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include <avr/io.h>  // for the register macros


#ifndef TEENSY_2_0_h
#define TEENSY_2_0_h


// LED control
#define TEENSY_LED1_ON             (OCR1A = 0xFF)
#define TEENSY_LED1_OFF            (OCR1A = 0x00)
#define TEENSY_LED1_SET(n)         (OCR1A = (uint8_t)(n))
#define TEENSY_LED1_SET_PERCENT(n) (OCR1A = (uint8_t)((n) * 0xFF))
#define TEENSY_LED2_ON             (OCR1B = 0xFF)
#define TEENSY_LED2_OFF            (OCR1B = 0x00)
#define TEENSY_LED2_SET(n)         (OCR1B = (uint8_t)(n))
#define TEENSY_LED2_SET_PERCENT(n) (OCR1B = (uint8_t)((n) * 0xFF))
#define TEENSY_LED3_ON             (OCR1C = 0xFF)
#define TEENSY_LED3_OFF            (OCR1C = 0x00)
#define TEENSY_LED3_SET(n)         (OCR1C = (uint8_t)(n))
#define TEENSY_LED3_SET_PERCENT(n) (OCR1C = (uint8_t)((n) * 0xFF))


void teensy_init(void);


#endif

