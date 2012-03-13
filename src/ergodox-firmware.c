/* ----------------------------------------------------------------------------
 * Firmware for the ergoDOX keyboard
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak
 * Released under The MIT License (MIT) (see "license.md") at
 * <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/* ----------------------------------------------------------------------------
 * Matrix [row.column] assignments
 * - row and column numbers are in hex
 * - coordinates without brackets are unused
 * - left and right hands are mirrored, with `row += 6` for left hand rows
 * ----------------------------------------------------------------------------
 * .......           rows x columns = positions;  assigned,  unassigned .......
 * ....... per hand:    6 x 7       = 42;         38,        4          .......
 * .......    total:   12 x 7       = 84;         76,        8          .......
 * ----------------------------------------------------------------------------
 * [66][65][64][63][62][61][60]                [00][01][02][03][04][05][06]
 * [76][75][74][73][72][71][70]                [10][11][12][13][14][15][16]
 * [86][85][84][83][82][81] 80                  20 [21][22][23][24][25][26]
 * [96][95][94][93][92][91][90]                [30][31][32][33][34][35][36]
 * [A6][A5][A4][A3][A2] A1  A0                  40  41 [42][43][44][45][46]
 *                       [B1]     B0      50     [51]
 *                       [B3]    [B2]    [52]    [53]
 *                       [B6][B5][B4]    [54][55][56]
 * ------------------------------------------------------------------------- */

/* ----------------------------------------------------------------------------
 * Pinouts and Pin assignments
 * ===========================
 * - '+' indicates pin
 * - 'o' indicates unused pin
 * - '-'s inserted between some of the pin names for readability
 * - 'OC**' pins enclosed in parenthesis had lines over them in the pinout
 * ----------------------------------------------------------------------------
 *  Teensy 2.0
 *  ==========               GND +---.....---+ VCC
 *                        SS PB0 +           + PF0 ADC0
 *                      SCLK PB1 +           + PF1 ADC1
 *                      MOSI PB2 +           + PF4 ADC4
 *                      MISO PB3 +  +     +  + PF5 ADC5
 * RTS  OC1C  OC0A --------- PB7 + PE6  AREF + PF6 ADC6
 *            OC0B  INT0 SCL PD0 + AIN0      + PF7 ADC7
 *                  INT1 SDA PD1 + INT6      + PB6 ADC13 OC1B  OC4B
 * RXD1 ----------- INT2 --- PD2 +           + PB5 ADC12 OC1A (OC4B)
 * TXD1 ----------- INT3 --- PD3 +           + PB4 ADC11
 *      OC3A (OC4A) -------- PC6 +           + PD7 ADC10 T0 -- OC4D
 * ICP3 ----- OC4A --------- PC7 +-+-+-+-+-+-+ PD6 ADC9  T1 - (OC4D) onboardLED
 *                  CTS XCK1 PD5 --/ | | | \-- PD4 ADC8 ------------ ICP1
 *             VCC ------------------/ | \-------------- RST
 *             GND --------------------/
 * ----------------------------------------------------------------------------
 *  MCP23018
 *  ========            Vss(GND) +01---.---28+ NC
 *                          GPNC +02       27+ GPAC
 *                          GPB0 +03       26+ GPA6
 *                          GPB1 +04       25+ GPAC
 *                          GPB2 +05       24+ GPAC
 *                          GPB3 +06       23+ GPAC
 *                          GPB4 +07       22+ GPAC
 *                          GPB5 +08       21+ GPAC
 *                          GPB6 +09       20+ GPAC
 *                          GPB7 +10       19+ INTC
 *                      Vdd(Vcc) +11       18+ INTC
 *                           SCL +12       17+ NC
 *                           SDA +13       16+ RESET
 *                            NC +14-------15+ ADDR
 * ----------------------------------------------------------------------------
 * ----------------------------------------------------------------------------
 *  Teensy 2.0 Pin Assignments
 *  ==========================
 *           power_negative  GND +---.....---+ Vcc   power_positive
 *                 column6   PB0 +           + PF0   row0
 *                               o           + PF1   row1
 *                               o           + PF4   row2
 *                               o  o     o  + PF5   row3
 *                    LED3  OC1C +           + PF6   row4
 *                     I2C   SCL +           + PF7   row5
 *                     I2C   SDA +           + OC1B  LED2
 *                 column3   PD2 +           + OC1A  LED1
 *                 column4   PD3 +           + PB4   column0
 *                 column1   PC6 +           + PD7   column5
 *                 column2   PC7 +-o-o-o-o-o-o
 * ----------------------------------------------------------------------------
 *  MCP32018 Pin Assignments
 *  ========================
 *      power_negative  Vss(GND) +01---.---28o
 *                               o02       27o
 *             column0      GPB0 +03       26o
 *             column1      GPB1 +04       25+ GPA5   row5
 *             column2      GPB2 +05       24+ GPA4   row4
 *             column3      GPB3 +06       23+ GPA3   row3
 *             column4      GPB4 +07       22+ GPA2   row2
 *             column5      GPB5 +08       21+ GPA1   row1
 *             column6      GPB6 +09       20+ GPA0   row0
 *                               o10       19+ INTA   ?TODO
 *      power_positive  Vdd(Vcc) +11       18+ INTB   ?TODO
 *                 I2C       SCL +12       17o
 *                 I2C       SDA +13       16+ RESET  ?TODO
 *                               o14-------15+ ADDR   ?TODO
 * ------------------------------------------------------------------------- */


#include "lib/twi.h"
#include "lib/print.h"


// processor frequency (from <http://www.pjrc.com/teensy/prescaler.html>)
#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define CPU_16MHz       0x00
#define CPU_8MHz        0x01
#define CPU_4MHz        0x02
#define CPU_2MHz        0x03
#define CPU_1MHz        0x04
#define CPU_500kHz      0x05
#define CPU_250kHz      0x06
#define CPU_125kHz      0x07
#define CPU_62kHz       0x08

// pins
// TODO: write some pretty macros


// TODO:
// - initialize pins
void init() {
	CPU_PRESCALE(CPU_16MHz);  // speed should match F_CPU in makefile
}


#define KB_LAYERS   1
#define KB_ROWS    12  // don't change
#define KB_COLUMNS  7  // don't change

uint8_t is_pressed[KB_ROWS][KB_COLUMNS] = {
// --- right hand ---
// column 0    1    2    3    4    5    6
	  0,   0,   0,   0,   0,   0,   0, //row 0x0
	  0,   0,   0,   0,   0,   0,   0, //row 0x1
	  0,   0,   0,   0,   0,   0,   0, //row 0x2
	  0,   0,   0,   0,   0,   0,   0, //row 0x3
	  0,   0,   0,   0,   0,   0,   0, //row 0x4
	  0,   0,   0,   0,   0,   0,   0, //row 0x5

// --- left hand ---
// column 0    1    2    3    4    5    6
	  0,   0,   0,   0,   0,   0,   0, //row 0x6
	  0,   0,   0,   0,   0,   0,   0, //row 0x7
	  0,   0,   0,   0,   0,   0,   0, //row 0x8
	  0,   0,   0,   0,   0,   0,   0, //row 0x9
	  0,   0,   0,   0,   0,   0,   0, //row 0xA
	  0,   0,   0,   0,   0,   0,   0, //row 0xB
}

// TODO: this belongs in program space
uint8_t kb_maps[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {
// --- layer: default ---
// column 0    1    2    3    4    5    6
	  0,   0,   0,   0,   0,   0,   0, //row 0x0
	  0,   0,   0,   0,   0,   0,   0, //row 0x1
	  0,   0,   0,   0,   0,   0,   0, //row 0x2
	  0,   0,   0,   0,   0,   0,   0, //row 0x3
	  0,   0,   0,   0,   0,   0,   0, //row 0x4
	  0,   0,   0,   0,   0,   0,   0, //row 0x5
	  0,   0,   0,   0,   0,   0,   0, //row 0x6
	  0,   0,   0,   0,   0,   0,   0, //row 0x7
	  0,   0,   0,   0,   0,   0,   0, //row 0x8
	  0,   0,   0,   0,   0,   0,   0, //row 0x9
	  0,   0,   0,   0,   0,   0,   0, //row 0xA
	  0,   0,   0,   0,   0,   0,   0, //row 0xB
}


void main() {
	init();
}


