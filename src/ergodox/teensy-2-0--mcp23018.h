/* ----------------------------------------------------------------------------
 * ergodox controller (Teensy 2.0 and MCP23018) specific stuff
 * - public things are prefixed by `controller_` or `CONTROLLER_`
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak
 * Released under The MIT License (MIT) (see "license.md") at
 * <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


// LEDs
#define CONTROLLER_LED1_ON             (OCR1A = 0xFFFF)
#define CONTROLLER_LED1_OFF            (OCR1A = 0x0000)
#define CONTROLLER_LED1_SET(n)         (OCR1A = (uint16_t)(n))
#define CONTROLLER_LED1_SET_PERCENT(n) (OCR1A = (uint16_t)((n) * 0xFFFF))
#define CONTROLLER_LED2_ON             (OCR1B = 0xFFFF)
#define CONTROLLER_LED2_OFF            (OCR1B = 0x0000)
#define CONTROLLER_LED2_SET(n)         (OCR1B = (uint16_t)(n))
#define CONTROLLER_LED2_SET_PERCENT(n) (OCR1B = (uint16_t)((n) * 0xFFFF))
#define CONTROLLER_LED3_ON             (OCR1C = 0xFFFF)
#define CONTROLLER_LED3_OFF            (OCR1C = 0x0000)
#define CONTROLLER_LED3_SET(n)         (OCR1C = (uint16_t)(n))
#define CONTROLLER_LED3_SET_PERCENT(n) (OCR1C = (uint16_t)((n) * 0xFFFF))


// init
void controller_init();

