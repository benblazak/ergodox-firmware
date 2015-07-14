# [Firmware][ergodox-firmware] for the [ErgoDox keyboard][]

The official website is [ergodox.org] (http://www.ergodox.org).  
Also see the [geekhack]
(http://geekhack.org/showthread.php?22780-Interest-Check-Custom-split-ergo-keyboard)
and [deskthority]
(http://deskthority.net/workshop-f7/split-ergonomic-keyboard-project-t1753.html)
discussion threads.  
Kits are periodically for sale [on Massdrop] (https://www.massdrop.com/buy/ergodox),
who also hosts [build instructions] (https://www.massdrop.com/ext/ergodox/assembly.php)
and a [web UI] (https://www.massdrop.com/ext/ergodox)
for configuring layouts.


### Notes
A rewrite is currently underway (see the 'partial-rewrite' branch) and so this
branch isn't quite receiving the attention it used to.  Things that have
changed since this document was last properly updated:
* Ryan Prince ([judascleric] (https://github.com/judascleric)) implemented
  sticky keys, and added a Colemak layout using them.
* Revision 2 of the firmware (on the 'partial-rewrite' branch) is working!  Not
  ready for merging or a general release though, and I'm not ready to declare
  anything final, so you may not want to switch yet; but developers may want to
  think about checking it out. :)
* Ryan Prince ([judascleric] (https://github.com/judascleric)) implemented 3
  media keys (play/pause, previous track, and next track) in Revision 1, using
  a bit of code from [hasu's tmk firmware]
  (https://github.com/tmk/tmk_keyboard).  Revision 2 probably won't have this
  functionality for a while.
* Gyuri Horak implemented NKRO and mouse keys in [his branch]
  (https://github.com/dyuri/ergodox-firmware) of rev-2.  Not merged, but I plan
  to implement the features later, if I can.  See [Pull Request #28]
  (https://github.com/benblazak/ergodox-firmware/pull/28).
* Oleg Kostyuk (cub-uanic) [ported the TMK firmware]
  (https://github.com/cub-uanic/tmk_keyboard)
  (written by "hasu") to the ErgoDox!
* Jacob McIntosh ([nacitar](https://github.com/nacitar)) implemented 4 more
  media keys (stop, mute, vol_up, and vol_down) in rev-1, fixed a media key
  bug, and implemented workman-p.



### Table of Contents
*generated with [DocToc](http://doctoc.herokuapp.com/)*

- [About This File](#about-this-file)
- [About This Project](#about-this-project)
	- [Downloading Binaries](#downloading-binaries)
	- [Compiling](#compiling)
	- [Issues and Feature Requests](#issues-and-feature-requests)
	- [Features (on the ErgoDox)](#features-on-the-ergodox)
- [About This Project (more technical)](#about-this-project-more-technical)
- [Dependencies (for building from source)](#dependencies-for-building-from-source)
- [HowTo](#howto)
	- [Load Firmware onto the Teensy](#load-firmware-onto-the-teensy)
	- [Change the Direction of the Diodes](#change-the-direction-of-the-diodes)
	- [Compile the Source Code](#compile-the-source-code)
	- [Create a New Keymap](#create-a-new-keymap)
	- [Add Code for a Different Type of Keyboard](#add-code-for-a-different-type-of-keyboard)


## About This File

If you're viewing this on github, please note that directory links will only
work if you're viewing this from the directory, and file links will only work
if you're viewing this as a file.  This is true for all the '.md' files here.
The limitation is due to the way github addresses directories and files, and
the fact that Markdown doesn't have any way (that I know of) to rewrite the
URLs as would be required.


## About This Project

This project is meant to be a usable firmware for the [ErgoDox keyboard][].  I
started writing it because, at the time, it was the easiest way for me to get
I&sup2;C working, and I very much wanted to avoid having the designers put a
16-pin connector (or something awful like that) between the two halves :) .  It
was also my first project in pure C (though I'm planning to rewrite it in C++),
and my first attempt at anything remotely this close to hardware.  I've done my
best to put decent documentation everywhere, in the hope that my perspective as
a n00b to this area might be useful for others.

The 'master' branch is meant to be stable - the one you want if you're going to
update your keyboard firmware, and usually the one you want if you're going to
fork.  This is a small project, so there may be times when other branches have
a bunch going on, and 'master' doesn't, and things sort of fall out of sync...
but I'll try to avoid that.  See the other branches for what's going on there.

Also, lots of other documentation can be found intermixed with the source
(especially in the accompanying '.md' files), and [references.md]
(references.md) contains lots of good links, along with descriptions.

### Downloading Binaries
If you're just looking for binaries, they can be downloaded [here]
[dropbox-download-page].

### Compiling
If you're just trying to compile, jump to the How To: [Compile the Source Code]
(#compile-the-source-code) section.

### Issues and Feature Requests
Open issues, feature requests, and such are tracked [on github]
(/benblazak/ergodox-firmware/issues).

### Features (on the ErgoDox)
* 6KRO (conforms to the USB boot specification)
* Teensy 2.0, MCP23018 I/O expander
* ~167 Hz scan rate (last time I measured it) (most of which is spent
  communicating via I&sup2;C)
* firmware level layers


## About This Project (more technical)

If you're looking to hack on the source, or just feel like reading it:

* The [makefile] (./makefile) and [build-scripts] (./build-scripts) folder in
  the toplevel directory are for building a collection of files for easy
  distribution.  They are not guaranteed to work on non-Unix systems, and may
  be (read: are) more hackish than the stuff in [src] (./src).  They help me
  out though.
* [src/lib] (src/lib) is for generally useful stuff relating to the firmware.
  [src/lib-other] (src/lib-other) is for generally useful stuff that I didn't
  write myself.  The TWI and USB libraries are in there, along with the files
  containing key press and release functions.
* [src/keyboard] (src/keyboard) is for keyboard specific stuff.  All the chip
  initialization code is there, along with the layout files, the software
  matrix to hardware matrix mapping, and hardware specific documentation.
* [src/main.c] (src/main.c) ties it all together, and provides a few higher
  level functions that are useful in the key press and release functions.


A few concepts that might be different:

* The layer stack

  When activated, layers are pushed onto the top of a stack.  When deactivated,
  layers are popped out from wherever they are in the stack.  Layers may be
  active in the stack more than once.  When a keypress occures, the top layer
  is used to determine what actions to take.

* Keypresses are functions

  Each time a key is pressed, the "press" function assigned to that key on the
  current layer is called.  When the key is released, the "release" function
  (from the same layer the key was on when it was pressed) is called.  These
  functions may do pretty much anything - from sending multiple different
  keypresses to the host, to changing the firmware state in some way, to
  activating a new layer.  They may also be "transparent", i.e. execute the
  function assigned to the key on the layer one down from the top layer
  (allowing for layers that are effectively "masks" over whatever layer was
  active before them).


## Dependencies (for building from source)

* See the PJRC [Getting Started] (http://pjrc.com/teensy/first_use.html) page
  for instructions on how to set up an AVR programming environment (be sure to
  click through all the subsections (in the navigation bar on the left), as
  there is essential information in each one).  This project uses C (not
  Arduino), and Make.  I'm compiling with GNU tools under OS X, but other
  environments (especially Linux, appropriately set up, or [WinAVR]
  (http://winavr.sourceforge.net/) under Windows) should work too.

* I also assume that you are using [git] (http://git-scm.com/) (for `make
  clean`).



## HowTo

Most of these instructions (or notes, rather) are meant for people who's
googling skills and patience are directly proportional to the amount of C
programming they don't already know :) .  I've done my best to organize and
comment things though, so I hope that just about anyone who manages to find
their way all the way here will be able to figure out a good deal from context.


### Load Firmware onto the Teensy
(beginner)

Before beginning, make sure:

* Your Teensy is plugged into your computer via USB

* You have the appropriate version of [the Teensy loader application]
  (http://www.pjrc.com/teensy/loader.html) from PJRC installed.

* You know what the "reset button" (a.k.a. the "tiny pushbutton") on the Teensy
  is.  See the "HalfKay Bootloader Mode" section of the [Teensy First Use]
  (http://www.pjrc.com/teensy/first_use.html) page on the PJRC website.

After getting set up:

* Run the Teensy loader program.
    * This will give you a window, as shown on the website.

* Click the "Auto" button on the upper right hand side of the window.
    * The button will light up brighter green.
    * This tells the loader program to load its current file whenever the
      Teensy is ready for it.

* Locate your '.eep' and '.hex' files.
    * If you don't have any, you can grab the latest ones [here]
      [dropbox-download-page] (in a '.zip' file).  Choose the newest file who's
      name contains the name of the keymap you want (look for "qwerty" if
      you're not sure).

* Drag and drop the '.eep' file onto the Teensy loader window.
    * The information bar at the bottom of the window should now read
      "firmware.eep" followed by the percentage of the Teensy memory that will
      be used by this file.

* Press and release the Teensy reset button (a.k.a. the "tiny pushbutton").
    * The Teensy loader should inform you that it is loading the file.  Wait
      until it's done: it shouldn't take long.

* Drag and drop the '.hex' file onto the Teensy loader window.

* Press and release the Teensy reset button (a.k.a. the "tiny pushbutton").

* Your firmware is now loaded!  Press a few buttons on your keyboard to make
  sure everything worked out all right, and enjoy :)

Notes:

* It may not be necessary to load the '.eep' file (if the file is 0 bytes, and
  the Teensy doesn't have anything loaded into its EEPROM already, it doesn't
  make any difference), but it's good to do so anyway, just to be safe.  It
  won't hurt anything either way.

* Now that your firmware is loaded, there should be a keyboard shortcut you can
  press instead of the Teensy reset button.  See the documentation on your
  layout for more information.


### Change the Direction of the Diodes
(intermediate)

That is, how to change whether the rows or the columns are being driven.  This can be done for each side of the keyboard independently.

* See [src/keyboard/ergodox/options.h] (src/keyboard/ergodox/options.h)

* After this, you'll need to recompile.  See the [About This Project]
  (#about-this-project) section above.


### Compile the Source Code
(brief notes)

Note: This relates to compiling in the [src] (src) directory.  The toplevel
build process (for generating the ui-info file and such) isn't really intended
to be portable; but you could probably get it working without *too* much
trouble, if you're familiar with programming in a Unix environment.  I'd
suggest looking through the toplevel Makefile, as a staring point, if that's
your goal.

* Read the [Dependencies] (#dependencies-for-building-from-source) section.

* Take a quickish glance at the [About This Project (more technical)]
  (#about-this-project-more-technical) section.

* Navigate to the [src] (src) directory (*not* the toplevel directory) in a
  terminal, and type `make`.

* If everything worked, the '.hex' and '.eep' files will be in the [src] (src)
  directory (where you currently are).


### Create a New Keymap

* Files to reference:
    * Keycode macros: see the file
      [src/lib/usb/usage-page/keyboard--short-names.h]
      (src/lib/usb/usage-page/keyboard--short-names.h).
        * See [keyboard.h] (src/lib/usb/usage-page/keyboard.h) for the actual
          values, with references to the specification.
    * Keyboard functions: see all files in the folder
      [src/lib/key-functions/public] (src/lib/key-functions/public).
    * Template layout files: see the QWERTY keymap source files in the folder
      [src/keyboard/ergodox/layout] (src/keyboard/ergodox/layout)
        * Currently [qwerty-kinesis-mod.c]
          (src/keyboard/ergodox/layout/qwerty-kinesis-mod.c) and
          [qwerty-kinesis-mod.h]
          (src/keyboard/ergodox/layout/qwerty-kinesis-mod.h)).
        * You'll probably want to make a copy of each to use as a template.

* You will need to set the `LAYOUT` variable in [src/makefile-options]
  (src/makefile-options) to the base name of your new layout files before you
  recompile.  ('.h' files may be called what you wish, but '.c' files must all
  have the same prefix (i.e. "base name") or they won't be compiled).

* Among other things, the '.h' layout file defines the macros that control the
  meaning of each of the LEDs on the keyboard (capslock, etc.).  They may be
  changed freely (or removed, to disable that LED).

* The '.c' layout file defines the values (keycode|value, press function,
  release function) assigned to each key, for each layer.
    * If a "press" function is set to NULL for a given layer, nothing will be
      called when the key is pressed on that layer.  Likewise for "release"
      functions.  If both are set to `NULL`, nothing will happen when the key
      is pressed in either event, so it doesn't matter what the keycode|value
      is for that layer - but you should probably pick something like `0` and
      stick to it, just for clarity.
    * The default number of layers is 10 (defined in
      [default--matrix-control.h]
      (src/keyboard/ergodox/layout/default--matrix-control.h) - you can
      override it in the layout's '.h' file, if you like).  You don't have to
      define all of them in the '.c' layout file, just the ones you want (C
      sets the uninitialized portions of the matrices to 0).
    * Make sure that in layer-0 **nothing is transparent** (see [About this
      Project (more technical)] (#about-this-project-more-technical).  Behavior
      is undefined if this occurs (off the top of my head, it'll probably cause
      an infinite loop - and you'll have to reset your keyboard (unplug it and
      plug it in again)).
    * Be careful how you assign things.  Pay **close attention** to the
      possible combinations of keypresses that could occur.  It's perfectly
      possible, for example, to make a layout that can shift to layer 2 (or
      some layer that doesn't even exist) and can't shift back, or that fails
      to tell the host when keys are released.  It's fairly unlikely that
      anything bad will happen if you mess up (though you could theoretically
      generate a sequence of keypresses that accidentally do very bad things on
      your machine), but it's important to have the possibility in mind.
      Please consider yourself warned :) .


### Add Code for a Different Type of Keyboard

* All the function prototypes and macro definitions required by the rest of the
  code should be in the following files (using the ergodox code as an example):
    * [controller.h] (src/keyboard/ergodox/controller.h)
    * [layout.h] (src/keyboard/ergodox/layout.h) (which in the ergodox code
      only exists to include 
      [layout/default--led-control.h]
      (src/keyboard/ergodox/layout/default--led-control.h) and
      [layout/default--matrix-control.h]
      (src/keyboard/ergodox/layout/default--matrix-control.h))
    * [matrix.h] (src/keyboard/ergodox/matrix.h)

* (In broad terms, you'll need to define functions that initialize and update
  the matrix, LED control macros, macros defining matrix dimensions, and
  keycode | key-lookup macros (or functions).)

* You will need to set the `KEYBOARD` variable in [src/makefile-options]
  (src/makefile-options) to the name of your new keyboard folder before you
  recompile.  You may also wish to change some of the other options in that
  file.

* The '.h' files listed above *must* exist, with those names, in the toplevel
  of your keyboard's directory (e.g. in `src/keyboard/new-keyboard-name`).
  They may include other '.h' files if you wish to put various definitions or
  prototypes in other places.  They will be included (with the help of some
  handy macros) in the corresponding files in [src/keyboard] (src/keyboard),
  which are in turn the files included by "main" and the keyboard functions.

* If you change the way things are included, be careful for circular includes.
  "main", the keyboard functions, and the keyboard code all need various
  parts of each other.

* Make sure to keep your eye on the `SRC` variable in [src/makefile]
  (src/makefile), to make sure all your '.c' files are getting compiled.



[dropbox-download-page]: https://www.dropbox.com/sh/8bbol6fkvydmtmg/QLudrdEyc9
[ergodox-firmware]: https://github.com/benblazak/ergodox-firmware
[ergodox keyboard]: http://ergodox.org/

-------------------------------------------------------------------------------

Copyright &copy; 2012 Ben Blazak <benblazak.dev@gmail.com>  
Released under The MIT License (MIT) (see "license.md")  
Project located at <https://github.com/benblazak/ergodox-firmware>

