# [ergodox-firmware][]: Firmware for the [ergoDOX keyboard][]

[ergodox-firmware]: https://github.com/benblazak/ergodox-firmware
[ergodox keyboard]: http://geekhack.org/showthread.php?22780-Interest-Check-Custom-split-ergo-keyboard


This project is definitely in beta, but I'll do my best to keep the 'master'
branch working.  Please see the source (and especially the accompanying '*.md'
files) for documentation.


## Notes

### (2012-04-11)
As of now, it looks like we have a working 6-KRO keyboard firmware for a Teensy
2.0 with a MCP23018 I/O expander.  It's scanning at ~167 Hz, most of which is
spent communicating over I&sup2;C.  This should be fast enough, I think.
Slight improvements might be possible (without finding a microprocessor capable
of > 400 kHz I&sup2;C or using SPI, that is, which I imagine would speed things
up a lot - but it'd also be much less convenient).  I'll attempt them if I see
the need.

Also, layers are implemented, but untested, as no keymaps are written to use
them yet.  Implementing on-keyboard hardware remapping seems like it'd be very
possible too, but I'd need to try it (and learn how to programmatically store
stuff in program space) to see if it'd work; and I'm not sure of a good way to
do the interface, since different people will likely have different keycap
layouts on the ergoDOX.

Getting to N-KRO is a goal, but I honestly have no idea whether it'll be
accomplished.  Ideally, I'd like a variable-KRO, where the keyboard is 6-KRO
till you press the 7th key (so if you're worried about compatibility, just
don't press more than 6 keys at a time).  From what I've read, it might be
possible, but I just finished everything else (so I'm slightly tired), and the
USB spec is scary.

Discussions about the project as a whole are going on at the forum page (linked
in the title) so if you have any imput (or want to participate in the group
buy!), please stop by.  :) .


## Dependencies (for building from source)

* See the PJRC [Getting Started] (http://pjrc.com/teensy/first_use.html) page
  for instructions on how to set up an AVR programming environment.  This
  project uses C (not Arduino).


-------------------------------------------------------------------------------

Copyright &copy; 2012 Ben Blazak <benblazak.dev@gmail.com>  
Released under The MIT License (MIT) (see "license.md")  
Project located at <https://github.com/benblazak/ergodox-firmware>

