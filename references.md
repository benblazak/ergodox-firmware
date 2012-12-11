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
  voltages, and other intersting stuff.

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


## Other People's Code

### Keyboard Firmware

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

### Other Awesome Keyboard Projects

* [My DIY keyboard collection ( or how I became a KB-geek...)]
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


-------------------------------------------------------------------------------

Copyright &copy; 2012 Ben Blazak <benblazak.dev@gmail.com>  
Released under The MIT License (MIT) (see "license.md")  
Project located at <https://github.com/benblazak/ergodox-firmware>

