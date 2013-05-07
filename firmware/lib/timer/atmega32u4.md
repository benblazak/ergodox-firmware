## 8-bit Timer/Counter Register Description (see datasheet section 13.8)

    TCCR0A : Timer/Counter Control Register A
    .---------------------------------------------------------------.
    |   7   |   6   |   5   |   4   |   3   |   2   |   1   |   0   |
    |---------------------------------------------------------------|
    | COM0A | COM0A | COM0B | COM0B |    Reserved   |  WGM1 |  WGM0 |
    '---------------------------------------------------------------'

    TCCR0B : Timer/Counter Control Register B
    .---------------------------------------------------------------.
    |   7   |   6   |   5   |   4   |   3   |   2   |   1   |   0   |
    |---------------------------------------------------------------|
    | FOC0A | FOC0B |    Reserved   | WGM02 |  CS02 |  CS01 |  CS00 |
    '---------------------------------------------------------------'

    * We want:
        * `COM0A` = `0b10` : Clear `OC0A` on Compare Match
        * `COM0B` = `0b00` : Normal port operation, `OC0B` disconnected
        * `WGM` = `0b010` : CTC (see section 13.6.2 "Clear Timer on Compare
          Match (CTC) Mode")
        * `CS` = `0b011` : clk_i/o / 64 (from prescaler)


    TIMSK0 : Timer/Counter Interrupt Mask Register
    .-----------------------------------------------------------------.
    |   7   |   6   |   5   |   4   |   3   |   2    |   1    |   0   |
    |-----------------------------------------------------------------|
    |                Reserved               | OCIE0B | OCIE0A | TOIE0 |
    '-----------------------------------------------------------------'

    * We want:
        * `OCIE0A` = `0b1` : enable  the Timer/Counter0 Compare Match A
          interrupt


    * We also want to set `OCR0A` (Output Compare Register A) to `250`

    * Since we're using CTC mode with `OCIE0A` enabled, we will be using the
      `TIMER0_COMPA_vect` interrupt vector (see
      [the avr-libc documentation on interrupts]
      (http://www.nongnu.org/avr-libc/user-manual/group__avr__interrupts.html)).


## Other Notes

* References:

    * [Newbie's Guide to AVR Timers]
      (http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&t=50106)
      : tutorial lby Deana Camera


* For a CPU frequency of 16 MHz:

    --------------------------------------------
     prescale value       ticks per millisecond
    ----------------     -----------------------
     1                    16000
     8                     2000
     64                     250
     256                     62.5
     1024                    15.625
    --------------------------------------------

    * So if we set the prescaler to 64, we can just barely get to a millisecond
      within the range of an 8-bit counter (2^8-1 = 255, and we need 250
      ticks).


* Abbreviations:
    * `COM`: Compare
    * `CS`: Clock Select
    * `FOC`: Force Output Compare
    * `TCCR: Timer/Counter Control Register
    * `TIMSK`: Timer/Counter Interrupt Mask Register
    * `WGM`: Waveform Generation Module


-------------------------------------------------------------------------------

Copyright &copy; 2013 Ben Blazak <benblazak.dev@gmail.com>  
Released under The MIT License (see "doc/licenses/MIT.md")  
Project located at <https://github.com/benblazak/ergodox-firmware>

