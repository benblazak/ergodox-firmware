# [ergodox-firmware][]: Firmware for the [ergoDOX keyboard][]

[ergodox-firmware]: https://github.com/benblazak/ergodox-firmware
[ergodox keyboard]: http://geekhack.org/showthread.php?22780-Interest-Check-Custom-split-ergo-keyboard


## About this File

If you're viewing this on github, please note that directory links will only
work if you're viewing this from the directory, and file links will only work
if you're viewing this as a file.  This is true for all the '.md' files here.
The limitation is due to the way github addresses directories and files, and
the fact that Markdown doesn't have any way (that I know of) to rewrite the
URLs as would be required.


## About this Project

This project is definitely in beta, but I'll do my best to keep the 'master'
branch working.  Please see the source (and especially the accompanying '.md'
files) for documentation.  And [references.md] (references.md) contains lots of
good links, along with descriptions.

If you're just trying to compile, jump to the bottom of the file and read the
[Dependencies] (#dependencies-for-building-from-source) section.  Once that's
taken care of, navigate to the [src] (src) directory, compile using Make, and
fire up your teensy loader to transfer the '.hex' file.  Just to be safe, you
should also check the '.eep' file.  If it's larger than 0 bytes, you need to
load it too.

If you're looking to hack on the source, or just feel like reading it, you
probably don't need much direction for a small project like this.  I'll try to
write more later (for people who are new to AVR programming, like I was when I
started this project), but for now:
* [src/lib] (src/lib) is for generally useful stuff.  The TWI and USB libraries
  are in there, along with the file containing basic key press and release
  functions.
* [src/keyboard] (src/keyboard) is for keyboard specific stuff.  All the chip
  initialization code is there, along with the layout files, the software
  matrix to hardware matrix mapping, and hardware specific documentation.
* [src/main.c] (src/main.c) ties it all together.

Open issues and such are tracked [on github]
(/benblazak/ergodox-firmware/issues).


## Notes

### (2012-04-11) (first major release on branch 'main')
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
  project uses C (not Arduino), and Make.  I'm compiling with GNU tools under
  Ubuntu, but other environments (especially [WinAVR]
  (http://winavr.sourceforge.net/) under Windows) should work too.

* I also assume that you are using [git] (http://git-scm.com/) (for `make
  clean`).


-------------------------------------------------------------------------------

Copyright &copy; 2012 Ben Blazak <benblazak.dev@gmail.com>  
Released under The MIT License (MIT) (see "license.md")  
Project located at <https://github.com/benblazak/ergodox-firmware>

