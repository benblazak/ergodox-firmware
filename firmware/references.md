## Electronics Stuff

* [Resistor Color Codes]
  (http://www.ladyada.net/wiki/lib/exe/fetch.php?hash=a2c6a9&w=501&h=785&media=http%3A%2F%2Fwww.ladyada.net%2Fimages%2Fmetertutorial%2Frescolorcode.jpg)
  : image

    * from [the Multimeter Tutorial]
      (http://www.ladyada.net/learn/multimeter/resistance.html)
      (on <http://ladyada.net/>)

* [Schematic Symbols]
  (http://img.docstoccdn.com/thumb/orig/28066054.png)
  : image

* [Vcc, Vdd, Vss, etc.]
  (http://encyclobeamia.solarbotics.net/articles/vxx.html)  
  A neat little discussion of the symbols and where they came from.

* [Very Basic Circuits]
  (http://www.seattlerobotics.org/encoder/mar97/basics.html)
  : column by Kevin Ross for Encoder  
  Includes a short thing about pull-up resistors.

* [Powering Light Emitting Diodes (LEDs)]
  (http://wolfstone.halloweenhost.com/Lighting/litlpo_PoweringLEDs.html)  
  Can you use one resistor for multiple parallel LEDs?  No.  Or, you can, but
  it's not the best idea.

    * can also be reached via <http://thewolfstone.com/>
      -> [ENTER] ('http://thewolfstone.com/Welcome/Home.html)
      -> [Wolfstone's Haunted Halloween Page]
         (http://thewolfstone.com/_ar/Halloween.html)
      -> [technology]
         (http://wolfstone.halloweenhost.com/Navigation/TechBase.html)
      -> [powering LEDs]
         (http://wolfstone.halloweenhost.com/Lighting/litlpo_PoweringLEDs.html)

* [Notes on LEDs]
  (http://www.gizmology.net/LEDs.htm)  
  Talks about different types of LEDs, mentioning typical brightnesses,
  voltages, and other interesting stuff.

* [All About Circuits : Reference]
  (http://www.allaboutcircuits.com/vol_5/index.html)  
  Looks like a great collection of info; didn't get to read much of it.

* [Effects of Varying I2C Pull-Up Resistors]
  (http://dsscircuits.com/articles/effects-of-varying-i2c-pull-up-resistors.html) : article by Wayne Truchsess  
  Great discussion on the topic, with oscilloscope graphs.  The practical
  takeaway is that 4.7kΩ is a good value for 100kHz I&sup2;C, and 2.2kΩ is good
  for 400kHz.


## C Stuff

* [comp.lang.c Frequently Asked Questions]
  (http://c-faq.com/index.html)  
  Really good information, if they happen to address the question you have.

* [The C Preprocessor]
  (http://gcc.gnu.org/onlinedocs/gcc-2.95.3/cpp_1.html#SEC1)
  (on <http://gcc.gnu.org/>)  
  One of my main references.

* [The GNU C Preprocessor]
  (http://tigcc.ticalc.org/doc/cpp.html#SEC27)  
  A modified version on a different site.  Has a few really useful things that
  I don't think I saw in the official documentation.

* [C Library Reference]
  (http://www.cplusplus.com/reference/)
  (on <http://cplusplus.com>)

* [C Operators/Expressions]
  (http://www.lix.polytechnique.fr/~liberti/public/computing/prog/c/C/CONCEPT/expressions.html)
  (on <http://www.lix.polytechnique.fr/>)

* [Bitwise Operators in C and C++: A Tutorial]
  (http://www.cprogramming.com/tutorial/bitwise_operators.html)
  (on <http://cprogramming.com/>)

* [AVR Tutorials - \[TUT\] \[C\] Bit manipulation (AKA "Programming 101")]
  (http://www.avrfreaks.net/index.php?name=PNphpBB2&file=printview&t=37871&start=0)

* [In C++ is "const" after type ID acceptable?]
  (http://stackoverflow.com/questions/988069/in-c-is-const-after-type-id-acceptable)
  (on <http://stackoverflow.com/>)

* [Arrays and pointers in C]
  (http://www.ibiblio.org/pub/languages/fortran/append-c.html)
  (on <http://www.ibiblio.org/>)

* [how to use array of function pointers?]
  (http://stackoverflow.com/questions/252748/how-to-use-array-of-function-pointers)
  (on <http://stackoverflow.com/>)

* [The Function Pointer Tutorials]
  (http://www.newty.de/fpt/index.html)

* [C preprocessor and concatenation]
  (http://stackoverflow.com/questions/1489932/c-preprocessor-and-concatenation)
  (on <http://stackoverflow.com/>)

* [The New C: Inline Functions]
  (http://drdobbs.com/184401540)
  by Randy Meyers
  (on <http://drdobbs.com/>)

* [gcc: why the -lm flag is needed to link the math library?]
  (http://stackoverflow.com/questions/4606301/gcc-why-the-lm-flag-is-needed-to-link-the-math-library)
  (on <http://stackoverflow.com/>)

* [cdecl]
  (http://cdecl.org)  
  Nice little web interface to a really helpful (when you're dealing with
  confusing type signatures in C) command line program.

* [changing a 16-bit binary number into two 8-bit binary numbers]
  (http://arduino.cc/forum/index.php/topic,44830.0.html)  
  (on <http://arduino.cc/>)

* [what happens in os when we dereference a null pointer in c]
  (http://stackoverflow.com/questions/12645647/what-happens-in-os-when-we-dereference-a-null-pointer-in-c)  
  Doesn't apply to AVRs really (since what happens in implementation defined
  according to the C standard, and I didn't see AVRs mentioned; and AVRs don't
  typically run an OS anyway), but still quite interesting.

* [Signed to unsigned conversion in C - is it always safe?]
  (http://stackoverflow.com/questions/50605/signed-to-unsigned-conversion-in-c-is-it-always-safe)  
  What happens if you return `-1` from a `uint8_t` function (or assign `-1` to
  a `uint8_t`)?

  * [Mod Function and Negative Numbers]
    (http://mathforum.org/library/drmath/view/52343.html)  
    `(-1)%5` in python returns `4` (just like it should)

* [Is it safe to free a `void *`?]
  (http://stackoverflow.com/a/2182522/2360353)  
  Yes.  The memory manager keeps track of the size of allocations - and the
  pointer you pass to `free()` is cast to `void *` before deallocation anyway.

* [Why exactly should I not call free() on variables not allocated by malloc()?]
  (http://stackoverflow.com/questions/2688377/why-exactly-should-i-not-call-free-on-variables-not-allocated-by-malloc)  
  But it's not safe to call `free()` on non-`malloc()`ed things.

* [Why do we need C Unions?]
  (http://stackoverflow.com/questions/252552/why-do-we-need-c-unions)  
  Some examples of what unions are good for.

* [Using and Abusing Unions]
  (http://critical.eschertech.com/2010/03/12/using-and-abusing-unions/)  
  A good discussion on when to use unions and when not to.

* [C preprocessor, recursive macros]
  (http://stackoverflow.com/questions/5641836/c-preprocessor-recursive-macros)  
  I'm not entirely sure I understand what's going on... but be it known that
  function like macros that expand into other function like macros are tricky
  business.

* [Declaring and Using Bit Fields in Structures]
  (http://publib.boulder.ibm.com/infocenter/macxhelp/v6v81/index.jsp?topic=%2Fcom.ibm.vacpp6m.doc%2Flanguage%2Fref%2Fclrc03defbitf.htm)

* [Bitwise shifting in C]
  (http://stackoverflow.com/a/8422852/2360353)  
  Shifting unsigned values is safe, left or right.  Shifting signed values is
  not always safe.

* [The signedness of `char`]
  (http://stackoverflow.com/questions/2054939/char-is-signed-or-unsigned-by-default)  
  Is undefined by the standard, and done differently in different compilers.
  avr-gcc appears to treat it as signed, by default, unless `-funsigned-char`
  is specified on the command line.  But then you have a non-default default
  behavior... which doesn't strike me as particularly clean.  Better to use
  `uint8_t`s when operating on things then, when possible, and to just not
  bitshift `char`s.

* [GCC docs : Variable Attributes]
  (http://gcc.gnu.org/onlinedocs/gcc/Variable-Attributes.html)  
  How to byte align variables in GCC (among other things...)

* [Bit-fields in C99]
  (http://blog.reverberate.org/2009/06/bit-fields-in-c99.html)  
  Bit-fields [can be dangerous]
  (http://avr.2057.n7.nabble.com/Bit-field-packing-order-changed-between-avrgcc-implementations-td19193.html).
  Most things are implementation defined, and [can change]
  (http://avr.2057.n7.nabble.com/Bit-field-packing-order-changed-between-avrgcc-implementations-td19193.html)
  even between different versions of the same compiler.  It seems to me that if
  you depend on binary layout, you should take care of that manually.  But the
  syntax is very nice compared to bit-shifting and bit-masking if you're going
  to do a lot of it, and there are many useful situations where they'll do
  exactly what you expect, so... use caution, but don't neglect them all
  together :) .  Kind of like `goto`.

* [Pointer comparisons in C. Are they signed or unsigned?]
  (http://stackoverflow.com/questions/6702161/pointer-comparisons-in-c-are-they-signed-or-unsigned)  
  Pointer comparisons in C are interesting...  Have to be careful with them.

* [Saturating Addition in C]
  (http://stackoverflow.com/a/3431717)  
  Saturated addition is kind of difficult in C.  This is my favorite of the
  methods I saw.

### C++ Stuff

* [Google C++ Style Guide]
  (http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml)  
  Useful overview of C++ stuff.  I'd been away from it for long enough that I
  needed a review.

* [Haiku : Coding Guidelines]
  (https://www.haiku-os.org/development/coding-guidelines)

* [C++ Language Tutorial]
  (http://www.cplusplus.com/doc/tutorial/)
  (on <http://www.cplusplus.com/>)

### For the AVR

* [AVR Newbie guide]
  (http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&t=70673)
  by stu_san (on <http://www.avrfreaks.net/>)  
  Didn't read much of it, but it looks like a great collection of info.

* [AVR Libc Library Reference]
  (http://www.nongnu.org/avr-libc/user-manual/modules.html)  
  One of my main references.

* [AVR : Data in Program Space]
  (http://www.nongnu.org/avr-libc/user-manual/pgmspace.html)  
  How to use '<avr/pgmspace.h>'.

* [avr-libc/include/avr/iom32u4.h]
  (http://svn.savannah.nongnu.org/viewvc/trunk/avr-libc/include/avr/iom32u4.h?revision=2288&root=avr-libc&view=markup)  
  List of registers and associated bit numbers for the ATmega32U4

* [A Brief Tutorial on Programming the AVR without Arduino]
  (https://www.mainframe.cx/~ckuethe/avr-c-tutorial/)
  by Chris Kuethe  
  Goes over a bunch of stuff pretty generally.  Useful to me because it was
  talking about exactly what I was trying to do (e.g. program the thing
  directly instead of messing around with gratuitous libraries).

* [Optimisations of AVR programs using avr-gcc]
  (http://www.tty1.net/blog/2008-04-29-avr-gcc-optimisations_en.html)  
  About compiling and stuff.

* [Using the EEPROM memory in AVR-GCC]
  (http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&t=38417)
  : tutorial by [Dean Camera] (http://fourwalledcubicle.com/AboutMe.php)
  (on <http://www.avrfreaks.net/>)  
  The EEPROM is non-volatile data memory that can withstand 100,000 writes and
  is byte accessible from within the program.  On the Teensy 2.0 there's only
  1,024 bytes of it though (compared to 32,256 bytes of flash, and 2,560 bytes
  of RAM), so you have to use it sparingly.  It's useful because flash
  (program) memory is not really something that's meant to be written to (it
  can only withstand 10,000 writes, and has to be written in pages using
  instructions meant for the bootloader), and RAM is volatile.

    * updated version available as a pdf at
      [Four Walled Cubicle : AVR Articles]
      (http://www.fourwalledcubicle.com/AVRArticles.php), along with a few
      other good articles on AVR programming

* [Components of the AVR-GCC Toolchain]
  (http://www.avrfreaks.net/wiki/index.php/Documentation:AVR_GCC/AVR_GCC_Tool_Collection)  
  Nice picture, and short descriptions of the relevent command line tools.

* [A Very Simple Arduino Task Manager]
  (http://bleaklow.com/2010/07/20/a_very_simple_arduino_task_manager.html)  
  A nice little write up on cooperative multitasking with an AVR.

* [A small discussion on AVR endianness]
  (http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&p=337752#337752)

* [Another discussion on AVR endianness]
  (http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&p=337747)  
  Wherin it is well argued that AVRs are neither big endian nor little endian,
  since all atomic arithmetic operators work on 8-bit data types only.
  Apparently, where there are (other) native multi-byte things going on,
  endinness is inconsistent.  It seems like most things though (or at least the
  most common things?) are little endian.  The LSB of a `uint16_t`, for
  instance, is stored in the lower memory address (which is apparently
  consistent with the way GCC typically does things).

* [Wide characters and unicode on the AVR]
  (http://www.avrfreaks.net/index.php?name=PNphpBB2&file=printview&t=64431&start=0)

* [`char` is signed, by default, in avr-gcc]
  (http://www.avrfreaks.net/index.php?name=PNphpBB2&file=printview&t=119944&start=0)  
  Apparently, treating `char` as signed is more common than treating it as
  unsigned.  It can be changed to unsigned, by default, with a compiler option.

* [EmbeddedGurus: Experts on Embedded Software]
  (http://embeddedgurus.com)  
  Seems like a good resource, with lots of general tips on embedded
  programming.


## Protocol Stuff

### I&sup2;C

* [Arduino I&sup2;C Expansion IO]
  (http://www.neufeld.newton.ks.us/electronics/?p=241)
  (from [Keith's Electronics Blog]
  (http://www.neufeld.newton.ks.us/electronics/))  
  Didn't use this much, but it's nice (if you're using the Arduino 'Wire'
  library), and it has pictures.

* [Arduino Playground :: Wire Library, Explored]
  (http://arduino.cc/playground/Main/WireLibraryDetailedReference)  
  More about the Wire library.  If you're not using interrupts, I think you'll
  be better off looking throught the datasheet and writing your own trivial
  library in C.  It really is trivial, almost all the code is in the datasheet
  (at least for the ATmega32U4), and it'll make more sense to you that way :) .

### USB

* About Keyboard [Scan Codes]
  (http://geekhack.org/showwiki.php?title=Scan+Codes)
  (on <http://geekhack.org/>)  
  Interesting discussion.  For practical purposes, if you're just dealing with
  USB, you can skip this and go straight to the keyboard usage page in the HID
  Usage Tables (see below).

* [USB - boot mode, NKRO, compatibility, etc...]
  (http://geekhack.org/showthread.php?13162-USB-boot-mode-NKRO-compatibility-etc/page2)
  : old thread by [Soarer]
  (http://geekhack.org/member.php?4274-Soarer)
  (on <http://geekhack.org/>)  
  Discussion about getting NKRO to work over USB and still be compatible with
  various BIOSs.

* [USB 2.0 Specification]
  (http://www.usb.org/developers/docs/usb_20_101111.zip)
  : zip (from <http://www.usb.org/developers/docs/>)

* [HID Device Class Definition]
  (http://www.usb.org/developers/devclass_docs/HID1_11.pdf)
  : pdf (from <http://www.usb.org/developers/hidpage>)
    * HID = Human Interface Device

* [HID Usage Tables]
  (http://www.usb.org/developers/devclass_docs/Hut1_12v2.pdf)
  : pdf (from <http://www.usb.org/developers/hidpage>)

### UTF-8

* [Reading Unicode (UTF-8) in C]
  (http://zaemis.blogspot.com/2011/06/reading-unicode-utf-8-by-hand-in-c.html)  
  A short discussion on the subject.

* [wikipedia: Hexadecimal Code Input (for the 3 major OSs)]
  (http://en.wikipedia.org/wiki/Unicode_input#Hexadecimal_code_input)  
  Note that both OS X and Windows require a little OS side setup for this to
  work.

### Other
 
* [Journaling and Logging File Systems]
  (http://www.eecs.harvard.edu/~margo/cs161/notes/fs-logs-slides.pdf)  
  PowerPoint-ish overview of a couple file system design strategies


## Other People's Code

### Keyboard Firmware

* github: [cub-uanic / tmk_keyboard]
  (https://github.com/cub-uanic/tmk_keyboard)  
  A port of Hasu's keyboard firmware to the ErgoDox, by Oleg Kostyuk
  ("cub-uanic").

* zip: [Phantom Firmware from PrinsValium]
  (http://geekhack.org/attachment.php?attachmentid=38982&d=1327895092)  
  Pretty basic (unless I'm missing nuances, which is entirely possible).
  Helped me a lot when I was learning how to initialize stuff on the Teensy.

    * mentioned in the [Building Phantom Hardware and Firmware Mods]
      (http://geekhack.org/showwiki.php?title=Island:26742)
      article (on <http://geekhack.org/>)

* github: [tmk / tmk_keyboard]
  (https://github.com/tmk/tmk_keyboard)  
  Firmware by [hasu] (http://geekhack.org/member.php?3412-hasu) on geekhack.
  Supports NKRO and mouse movements.

    * forked by [Pyrolistical / tmk_keyboard]
      (https://github.com/Pyrolistical/tmk_keyboard/tree/master/fourway)

        * mentioned in the [KeyPoard]
          (http://geekhack.org/showwiki.php?title=Island:26845)
          article on <http://geekhack.org/>

    * forked by [riffautae / tmk_keyboard]
      (https://github.com/riffautae/tmk_keyboard)

        * mentioned on the [Teensy Keyboard Firmware Discussion]
          (http://geekhack.org/showthread.php?26730-Teensy-Keyboard-Firmware-Discussion/page2)
          thread on <http://geekhack.org/>

* github: [humblehacker / keyboard]
  (https://github.com/humblehacker/keyboard)  
  Looks like it has some cool ideas, but I haven't read through it well enough
  to know what's going on.

    * mentioned on [the humblehacker keyboard website]
      (http://humblehacker.com/keyboard/)

    * mentioned on [the humblehacker geekhack page]
      (http://geekhack.org/showwiki.php?title=Island:6292)

    * mentioned on [the designer's blog]
      (http://humblehacker.com/blog/)

* githug: [chrisandreae / kinesis-firmware]
  (https://github.com/chrisandreae/kinesis-firmware)  
  Another firmware using the ATMega32u4.

    * mentioned in [this post] (http://deskthority.net/post106621.html#p106621)
      by [vvp] (http://deskthority.net/vvp-u3812/) on
      <http://deskthority.net/>.  he's thinking about using it on a hardware
      modded ErgoDox.

### USB Libraries

* [LUFA (2012) (Lightweight USB Framework for AVRs)]
  (http://www.fourwalledcubicle.com/LUFA.php)  
  Very well known USB library for AVRs.  And it looks like it'd be really good
  too, but the documentation is hard to get into, and the examples don't seem
  to have enough explanation for me, since I don't have any background in what
  USB is doing in the first place.

* zip: [PJRC: usb_keyboard]
  (http://pjrc.com/teensy/usb_keyboard.zip)  
  From the [LUFA Library : Alternative USB AVR Stacks]
  (http://www.fourwalledcubicle.com/files/LUFA/Doc/110528/html/_page__alternative_stacks.html)
  page: "Not so much a complete stack as a collection of USB enabled demos,
  this library is specifically designed for the PJRC Teensy line of USB AVRs,
  and thus may need to be modified for other USB AVR chips. These minimal code
  samples shows the inner workings of the USB controller, without all the
  abstraction present in most other USB AVR stacks."

    * mentioned on [the PJRC website]
      (http://pjrc.com/teensy/usb_keyboard.html)

* [V-USB]
  (http://vusb.wikidot.com/driver-api)  
  From the [LUFA Library : Alternative USB AVR Stacks]
  (http://www.fourwalledcubicle.com/files/LUFA/Doc/110528/html/_page__alternative_stacks.html)
  page: "Well regarded and complete USB 1.1 software stack for several AVR
  models, implementing Low Speed HID. Used in many commercial and
  non-commercial designs, with user-submitted projects available for viewing on
  the company's website. Uses C language code mixed with assembly for
  time-critical sections."  
  Also, it has really good documentation.

### TWI Libraries

* github: [TWI library in C]
  (https://github.com/arduino/Arduino/tree/master/libraries/Wire/utility)
  : (arduino / Arduino / libraries / Wire / utility)  
  Well done (as far as I can tell) and complete (includes code for interrupt
  handling).  Meant to be used through the Arduino 'Wire' library interface,
  but you can use it alone as well.  The version on github pulls in a whole
  bunch of Arduino dependencies though, if you're just going to use the
  library look for an older version that doesn't (like the one included in the
  version of Arduino in the Ubuntu 11.10 repos).

* zip: [i2cmaster]
  (http://homepage.hispeed.ch/peterfleury/i2cmaster.zip)
  (by Peter Fleury, on [his homepage]
  (http://homepage.hispeed.ch/peterfleury/))  
  Good I2C library.  Includes stuff both in assembly and C (though, I didn't
  look at the assembly code).  I still think you're better off writing your
  own, it's not that hard and you'll understand it better.  Also, this library
  is under the GPL (from what it says on his site; couldn't find a licence in
  the code).

* forum: [Interfacing MCP23018 io expander via Arduino]
  (http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1282150189)  
  Contains a quick MCP23017 library in C++.  Didn't end up looking at it too
  hard.

* github: [maniacbug / Arduino / libraries / MCP23018]
  (https://github.com/maniacbug/Arduino/tree/master/libraries/MCP23018)  
  Library in C++.  Don't think I ended up looking through this one at all.

### Other

* [Soarer's Converter (XT/AT/PS2/Terminal to USB Converter with NKRO)]
  (http://geekhack.org/showwiki.php?title=Island:17458)  
  No code for the part that talks over USB though.  Code only available for the
  tools that allow you to change the keymap and stuff, I think.

* zip: [PJRC: blinky]
  (http://pjrc.com/teensy/blinky.zip)  
  Little baby example project for the Teensy.  Quite nice.

    * mentioned on [the PJRC website]
      (http://pjrc.com/teensy/gcc.html)


## Hardware Documentation

* [Microchip: Analog & Interface Product Selector Guide]
  (http://ww1.microchip.com/downloads/en/DeviceDoc/21060z.pdf)

    * from [the Microchip website (MCP23017 product listing page)]
      (http://www.microchip.com/wwwproducts/Devices.aspx?dDocName=en023499)

* [MCP23017 / MCP23S17 Data Sheet]
  (http://ww1.microchip.com/downloads/en/DeviceDoc/21952b.pdf)

    * from [the Microchip website]
      (http://www.microchip.com/wwwproducts/Devices.aspx?dDocName=en023499)

* [MCP23018 / MCP23S18 Data Sheet]
  (http://ww1.microchip.com/downloads/en/DeviceDoc/22103a.pdf)

    * from [the Microchip website]
      (http://www.microchip.com/wwwproducts/Devices.aspx?dDocName=en537375)

* [Teensy 2.0 (ATMEGA32U4) Data Sheet]
  (http://pjrc.com/teensy/atmega32u4.pdf)

    * from [the PJRC website]
      (http://pjrc.com/teensy/datasheets.html)

* [Teensy++ 2.0 (AT90USB1286) Data Sheet]
  (http://pjrc.com/teensy/at90usb1286.pdf)

    * from [the PJRC website]
      (http://pjrc.com/teensy/datasheets.html)

* [Teensy 2.0 Pin Assignments, Using C]
  (http://pjrc.com/teensy/card2a.pdf)

    * from [the PJRC website]
      (http://pjrc.com/teensy/datasheets.html)

* [Teensy 2.0 Pin Assignments, Using Arduino]
  (http://pjrc.com/teensy/card2b.pdf)

    * from [the PJRC website]
      (http://pjrc.com/teensy/datasheets.html)

* [Cherry MX Series Keyswitches : Specifications]
  (http://www.cherrycorp.com/english/switches/key/mx.htm)


## Miscellaneous

### Keyboard Testing Tools

* [Understanding Rollover]
  (http://gadzikowski.com/nkeyrollover.html)  
  Includes 3 different tests (2 of which are web based) to see which keys are
  actually registering as pressed.

    * mentioned on the [Default:NKey Rollover]
      (http://geekhack.org/showwiki.php?title=NKey+Rollover+-+Overview+Testing+Methodology+and+Results)
      page (on <http://geekhack.org/>)

### Typical Keyboard Information

* [Keyboard Scan Rates]
  (http://geekhack.org/showwiki.php?title=Keyboard+scan+rates)
  list (on <http://geekhack.org/>)  
  Keyboards seem to typically scan at rates from a little below 100Hz to about
  300Hz, with the most common values a little below 100Hz.  The [PJRC
  usb_keyboard] (http://pjrc.com/teensy/usb_keyboard.html) example
  documentation has a limit of 1000 packets (so 500 presses -> releases) per
  second, but says that even that speed might overwhelm host software, which
  expects keystrokes to come much more slowly.  And, a debounce time of 5ms
  (which is the spec'ed high value for Cherry MX switches) would give us a max
  scan rate of 200Hz.

* [Cherry MX debounce times]
  (http://geekhack.org/index.php?topic=42385.msg861321#msg861321)  
  Interesting discussion.  Oscilloscope diagrams of bounce for a few different
  switches near the beginning :) .

### Other Awesome Keyboard Projects

* [My DIY keyboard collection (or how I became a KB-geek...)]
  (http://deskthority.net/workshop-f7/my-diy-keyboard-collection-or-how-i-became-a-kb-geek-t2534.html)
  : post by [suka] (http://deskthority.net/suka-u434/)
  on <http://deskthority.net/>  
  If I ever decide to do a keyboard completely by myself, I'm going back to
  this link and starting with this.  Looks really well done.

    * linked to in [a post]
      (http://geekhack.org/showthread.php?22780-Interest-Check-Custom-split-ergo-keyboard&p=582593&viewfull=1#post582593)
      on the ergoDOX geekhack thread

### Documentation and Design Tools

* [Markdown: Syntax]
  (http://daringfireball.net/projects/markdown/syntax)  
  A necessity if your code is on github :) .

* [KiCAD Tutorial]
  (http://teholabs.com/knowledge/kicad.html)
  (on <http://teholabs.com/>)  
  I like the tool.  Didn't need the functionality just for a little circuit
  diagram though, so I forwent the learning curve and used Inkscape.

    * mentioned on the [circuit/block-diagram drawing]
      (http://stackoverflow.com/questions/6422603/circuit-block-diagram-drawing)
      question (on <http://stackoverflow.com/>)

* [Ti<i>k</i>Z and PGF]
  (http://www.texample.net/tikz/)
  : a TeX graphics package  
  This is really cool.  And I wish i knew more about LaTeX (and all its
  variations) so that it would have been time effective for me to use it.  If I
  ever need to do automatic diagram generation, I'm going to give this a more
  serious try.

    * mentioned on the [circuit/block-diagram drawing]
      (http://stackoverflow.com/questions/6422603/circuit-block-diagram-drawing)
      question (on <http://stackoverflow.com/>)

    * [Documentation (for version 2010-09-28)]
      (http://www.texample.net/media/pgf/builds/pgfmanualCVS2010-09-28.pdf)
      : pdf

    * [Example: Block diagram line junctions]
      (http://www.texample.net/tikz/examples/line-junctions/)

* [Inkscape : Connector tool tutorial]
  (http://wiki.inkscape.org/wiki/index.php/UsingTheConnectorTool)  
  The open source vector graphics tool.  Not the _best_ for diagrams (though,
  see the link; as that tool improves it will hopefully become much better),
  but it works and I like it :) .

### Web Stuff

* [Raphaël—JavaScript Library]
  (http://raphaeljs.com)  
  A library for working with SVG (and VML, on IE I think) graphics - drawing
  them, animating them, adding events...  Looks really nice :)

  * also [on github] (https://github.com/DmitryBaranovskiy/raphael/)

* [An Introduction to the Raphaël JS Library]
  (http://net.tutsplus.com/tutorials/javascript-ajax/an-introduction-to-the-raphael-js-library/)  
  A good tutorial, it looks like.

* [YAML (official site)]
  (http://www.yaml.org)  
  YAML is a great data serilization language.

* [JS-YAML : online demo]
  (http://nodeca.github.com/js-yaml/)  
  The demo page of a YAML parser written in JavaScript.

* [Lively Kernel]
  (http://www.lively-kernel.org)  
  I read about this a while ago, and just remembered it again while thinking
  about how I would write a keymap making thing in javascript.  Not sure how
  good it'd be for that specifically, but the concept is just so **awesome**!

### Hardware Mods to the ErgoDox (horribly incomplete list)

* [LEDs on the left (MCP23018) side]
  (http://geekhack.org/index.php?topic=22780.msg873819#msg873819)  
  : post by [Unix Guru] (http://geekhack.org/index.php?action=profile;u=24565)
  on <http://geekhack.org/>  

### Hardware and DIY Stuff (for the keyboard case, and such)

* [Working with Acrylic]
  (http://www.bcae1.com/plexi.htm)

    * mentioned in [this post]
      (http://geekhack.org/index.php?topic=22780.msg782192#msg782192)
      by [sordna] (http://geekhack.org/index.php?action=profile;u=9426)
      (on <http://geekhack.org/>)

    * also see [this post]
      (http://geekhack.org/index.php?topic=22780.msg782080#msg782080)
      by [kurplop] (http://geekhack.org/index.php?action=profile;u=17045)
      (on <http://geekhack.org/>)

* [Kurplop's finishing of the aluminum case (from Massdrop round 1)]
  (http://geekhack.org/index.php?topic=22780.msg854128#msg854128)

* [Geekhack: DIY resources]
  (http://geekhack.org/index.php?topic=33298.0)  
  A nice short list of things one might want to know for keyboard hardware
  projects.

### Some Random Stuff

* [Tutorial: Metacompilers Part 1]
  (http://www.bayfronttechnologies.com/mc_tutorial.html)  
  Probably doesn't have anything to do with microprocessors *or* web
  development (at least at the moment)... but the concept is really awesome :)
  .  I included it here because, as I was writing in C, the thought "I could
  write a script to generate this code in Python *so* easily..." went through
  my head quite often.

* [Towards Moore's Law Software: Part 1 of 3]
  (http://www.moserware.com/2008/04/towards-moores-law-software-part-1-of-3.html)  
  Great article on programming in general, and where it might be going in the
  future.  Along the same lines as the Metacompilers tutorial, in that it talks
  about using domain specific languages.  Also talks about different
  programming paradigms that are being explored right now.

* [What are the available interactive languages that run in tiny memory?]
  (http://stackoverflow.com/questions/1082751/what-are-the-available-interactive-languages-that-run-in-tiny-memory)
  (on <http://stackoverflow.com/>)  
  Didn't really see anything other than ooc and FORTH that might work for an
  application like this firmware.

* [ooc]
  (http://ooc-lang.org)
  : a programming language targeting C99  
  This project doesn't seem like it's been very active in the last year or
  so... not that it looks dead (and, acutally, I didn't check the IRC channel
  or forums or anything, so I could be completely wrong), just not very active.
  And the documentation's fairly incomplete (which is sad, it looks like a
  really cool language...).

* [Plover, the Open Source Steno Program]
  (http://plover.stenoknight.com)  
  One of the only good reasons I've seen to want NKRO ;)



-------------------------------------------------------------------------------

Copyright &copy; 2012, 2013, 2014 Ben Blazak <benblazak.dev@gmail.com>  
Released under The MIT License (see "doc/licenses/MIT.md")  
Project located at <https://github.com/benblazak/ergodox-firmware>

