# Documentation : Teensy 2.0

## Pinout and Pin assignments

* `+` indicates pin
* `o` indicates unused pin
* `-`s inserted between some of the pin functions for readability
* `OC**` pins enclosed in parenthesis had lines over them in the pinout

### Teensy 2.0

                              GND +---.....---+ Vcc
                           SS PB0 +           + PF0 ADC0
                         SCLK PB1 +           + PF1 ADC1
                         MOSI PB2 +           + PF4 ADC4
                         MISO PB3 +  +     +  + PF5 ADC5
    RTS  OC1C  OC0A --------- PB7 + PE6  AREF + PF6 ADC6
               OC0B  INT0 SCL PD0 + AIN0      + PF7 ADC7
                     INT1 SDA PD1 + INT6      + PB6 ADC13 OC1B  OC4B
    RXD1 ----------- INT2 --- PD2 +           + PB5 ADC12 OC1A (OC4B)
    TXD1 ----------- INT3 --- PD3 +           + PB4 ADC11
         OC3A (OC4A) -------- PC6 +           + PD7 ADC10 T0 -- OC4D
    ICP3 ----- OC4A --------- PC7 +-+-+-+-+-+-+ PD6 ADC9  T1 - (OC4D) onboardLED
                     CTS XCK1 PD5 --/ | | | \-- PD4 ADC8 ------------ ICP1
                Vcc ------------------/ | \-------------- RST
                GND --------------------/

### Teensy 2.0 Pin Assignments

              power_negative  GND +---.....---+ Vcc  power_positive
                     column6  PB0 +           + PF0  row0
                              PB1 o           + PF1  row1
                              PB2 o           + PF4  row2
                              PB3 o  o     o  + PF5  row3
                 (OC1C) LED3  PB7 + PE6  AREF + PF6  row4
                  (SCL)  I2C  PD0 +           + PF7  row5
                  (SDA)  I2C  PD1 +           + PB6  LED2 (OC1B)
                     column3  PD2 +           + PB5  LED1 (OC1A)
                     column4  PD3 +           + PB4  column0
                     column1  PC6 +           + PD7  column5
                     column2  PC7 +-o-o-o-o-o-+ PD6  onboardLED
                              PD5 --/ | | | \-- PD4
                              Vcc ----/ | \---- RST
                              GND-------/

* notes:
  * SCL and SDA: Need external pull-up resistors.  Sometimes the Teensy
    internal pull-ups are enough (see datasheet section 20.5.1), but i think
    for this project we'll want external ones.  The general recommendation for
    400kHz I&sup2;C seems to be 2.2kΩ.


## Notes about Registers

### General I/O (see datasheet section 10.2.1)

    DDRxn  function  PORTxn  function
    1      output    1       drive high
                     0       drive low
    0      input     1       internal pull-up on
                     0       internal pull-up off

    PINxn  action   function
           write 1  toggles the value of PORTxn
           read     returns the logical value (1|0) of the pin

* notes:
  * Unused pins should be set as input, with internal pullup enabled in order
    to give them a defined level (see datasheet section 10.2.6).
  * PD6 (the onboard LED) already has a defined level (low), so there's no
    reason to set internal pull-up enabled on it.  If we do, it will source
    current to the LED, which is fine, but unnecessary.
  * We want the row pins 'hi-Z' initially (set as input with pull-up disabled),
    and the column pins set as input with internal pull-up enabled.  We'll
    cycle through driving the row pins low (setting them as output) and
    checking the column pins in the update function.
    * Switching the row pins between hi-Z and drive low (treating them as if
      they were open drain) seems just as good as, and a little safer than,
      driving them high when the row's not active.

### PWM on ports OC1(A|B|C) (see datasheet section 14.10)

* notes: settings:
  * PWM pins should be set as outputs.
  * we want Waveform Generation Mode 5  
    (fast PWM, 8-bit)  
    (see table 14-5)
    * set `TCCRB[4,3],TCCRA[1,0]` to `0,1,0,1`
  * we want "Compare Output Mode, Fast PWM" to be `0b10`  
    "Clear OCnA/OCnB/OCnC on compare match, set OCnA/OCnB/OCnC at TOP"  
    (see table 14-3)  
    this way higher values of `OCR1(A|B|C)` will mean longer 'on' times for the
    LEDs (provided they're hooked up to GND; other way around if they're hooked
    up to Vcc)
    * when in a fast PWM mode, set `TCCR1A[7,6,5,4,3,2]` to `1,0,1,0,1,0`
  * we want "Clock Select Bit Description" to be `0b001`  
    "clkI/O/1 (No prescaling)"  
    (see table 14-6)
    * set `TCCR1B[2,1,0]` to `0,0,1`
    * LEDs will be at minimum brightness until OCR1(A|B|C) are changed (since
      the default value of all the bits in those registers is 0)

* notes: behavior:
  * The pins source current when on, and sink current when off.  They aren't
    set to high impediance for either.
  * In Fast PWM mode setting `OCR1(A|B|C)` to `0` does not make the output on
    `OC1(A|B|C)` constant low; just close.  Per the datasheet, this isn't true
    for every PWM mode.

* abbreviations:
  * OCR = Output Compare Register
  * TCCR = Timer/Counter Control Register

-------------------------------------------------------------------------------

Copyright &copy; 2012 Ben Blazak <benblazak.dev@gmail.com>  
Released under The MIT License (MIT) (see "license.md")
Project located at <https://github.com/benblazak/ergodox-firmware>

