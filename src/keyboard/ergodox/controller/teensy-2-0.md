# Documentation : Teensy 2.0

## Pinout and Pin assignments

* `+` indicates connected pin
* `o` indicates unconnected pin
* `=` is used to list other things the pin is connected to
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
                    column_7  PB0 +           + PF0  row_5
                    column_8  PB1 +           + PF1  row_4
                    column_9  PB2 +           + PF4  row_3
                    column_A  PB3 +  o     o  + PF5  row_2
                (OC1C) LED_3  PB7 + PE6  AREF + PF6  row_1
                 (SCL)   I2C  PD0 +           + PF7  row_0
                 (SDA)   I2C  PD1 +           + PB6  LED_2 (OC1B)
                    column_B  PD2 +           + PB5  LED_1 (OC1A)
                    column_C  PD3 +           + PB4  = Vcc
                    column_D  PC6 +           o PD7
                              PC7 o-o-o-o-o-o-+ PD6  onboardLED = GND
                              PD5 --/ | | | \-- PD4
                              Vcc ----/ | \---- RST
                              GND-------/

* notes:
    * Row and column assignments are to matrix positions, which may or may
      or may not correspond to the physical position of the key: e.g. the key
      where `row_4` and `column_2` cross will be scanned into the matrix at
      `[4][2]`, wherever it happens to be located on the keyboard.  Mapping
      from one to the other (which only matters for defining layouts) is
      handled elsewhere.
    * LEDs are labeled using numbers (starting with '1') instead of letters
      (starting with 'A') as on the PCB.
    * SCL and SDA: Need external pull-up resistors.  Sometimes the Teensy
      internal pull-ups are enough (see datasheet section 20.5.1), but i think
      for this project we'll want external ones.  The general recommendation
      for 400kHz I&sup2;C seems to be 2.2kΩ.


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
    * Initially, we want either columns or rows (see <../options.h>) set as
      hi-Z without pull-ups, and the other set of pins set as input with
      pull-ups.  During the update function, we'll cycle through setting the
      first set low and checking each pin in the second set.
        * To set a pin hi-Z on this board, set it as input with pull-up
          disabled.
        * Switching the driving pins (the first set of pins) between hi-Z and
          drive low (treating them as if they were open drain) seems just as
          good as, and a little safer than, driving them high when they're not
          active.
    * We need to delay for at least 1 μs between changing the column pins and
      reading the row pins.  I would assume this is to allow the pins time to
      stabalize.
        * Thanks to [hasu] (http://geekhack.org/member.php?3412-hasu)
          for the suggestion [here]
          (http://geekhack.org/showthread.php?22780-Interest-Check-Custom-split-ergo-keyboard&p=606415&viewfull=1#post606415),
          and [PrinsValium] (http://geekhack.org/member.php?6408-PrinsValium)
          for noting that his firmware had erratic behavior without the delays
          [here]
          (http://geekhack.org/showthread.php?22780-Interest-Check-Custom-split-ergo-keyboard&p=606426&viewfull=1#post606426).
          DOX tried it and confirmed that it worked for his protoype PCB (as of
          3 June 2012) [here]
          (http://geekhack.org/showthread.php?22780-Interest-Check-Custom-split-ergo-keyboard&p=606865&viewfull=1#post606865).
          Before adding a delay we were having [strange problems with ghosting]
          (http://geekhack.org/showthread.php?22780-Interest-Check-Custom-split-ergo-keyboard&p=605857&viewfull=1#post605857).
          

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
      this way higher values of `OCR1(A|B|C)` will mean longer 'on' times for
      the LEDs (provided they're hooked up to GND; other way around if they're
      hooked up to Vcc)
        * when in a fast PWM mode, set `TCCR1A[7,6,5,4,3,2]` to `1,0,1,0,1,0`
    * we want "Clock Select Bit Description" to be `0b001`  
      "clkI/O/1 (No prescaling)"  
      (see table 14-6)
        * set `TCCR1B[2,1,0]` to `0,0,1`
        * LEDs will be at minimum brightness until OCR1(A|B|C) are changed
          (since the default value of all the bits in those registers is 0)

* notes: behavior:
    * The pins source current when on, and sink current when off.  They aren't
      set to high impediance for either.
    * In Fast PWM mode setting `OCR1(A|B|C)` to `0` does not make the output on
      `OC1(A|B|C)` constant low; just close.  Per the datasheet, this isn't
      true for every PWM mode.

* abbreviations:
    * OCR = Output Compare Register
    * TCCR = Timer/Counter Control Register

-------------------------------------------------------------------------------

Copyright &copy; 2012 Ben Blazak <benblazak.dev@gmail.com>  
Released under The MIT License (MIT) (see "license.md")  
Project located at <https://github.com/benblazak/ergodox-firmware>

