# [ergodox-firmware][]: Firmware for the [ErgoDox keyboard][]

Also see the [geekhack]
(http://geekhack.org/showthread.php?22780-Interest-Check-Custom-split-ergo-keyboard)
and [deskthority]
(http://deskthority.net/workshop-f7/split-ergonomic-keyboard-project-t1753.html)
discussion threads.

[ergodox-firmware]: https://github.com/benblazak/ergodox-firmware
[ergodox keyboard]: http://ergodox.org/


## About this File

If you're viewing this on github, please note that directory links will only
work if you're viewing this from the directory, and file links will only work
if you're viewing this as a file.  This is true for all the '.md' files here.
The limitation is due to the way github addresses directories and files, and
the fact that Markdown doesn't have any way (that I know of) to rewrite the
URLs as would be required.


## Features (on the ErgoDox)
* 6KRO
* Teensy 2.0, MCP23018 I/O expander
* ~167 Hz scan rate (last time I measured it) (most of which is spent
  communicating via I&sup2;C)
* firmware level layers


## About this Project

This project is still definitely a work in progress, but it's getting towards
something I'll be happy with when the keyboard finally goes into group buy.
The 'master' branch should always contain the most recent "stable" release of
the code.  The 'dev' branch may have new things, but it may also have
expiremental or not yet fixed things.  Code on the 'master' branch should also
tend to be more thoroughly tested.  Please see the source (and especially the
accompanying '.md' files) for documentation.  And [references.md]
(references.md) contains lots of good links, along with descriptions.

If you're just trying to compile, jump to the bottom of the file and read the
[Dependencies] (#dependencies-for-building-from-source) section.  Once that's
taken care of, navigate to the [src] (src) directory (*not* the toplevel
directory), compile using Make, and fire up your teensy loader to transfer the
'.hex' file.  Just to be safe, you should also check the '.eep' file.  If it's
larger than 0 bytes, you need to load it too.

Open issues, feature requests, and such are tracked [on github]
(/benblazak/ergodox-firmware/issues).


## About this Project (more technical)

If you're looking to hack on the source, or just feel like reading it:

* The [makefile] (./makefile) and [build-scripts] (./build-scripts) folder in
  the toplevel directory are for building the collection of files that are
  posted on the [downloads]
  (https://github.com/benblazak/ergodox-firmware/downloads) page.  They are not
  guaranteed to work on non-Unix systems, and may be more hackish than the
  stuff in [src] (./src).  They help me out though.
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



## HowTo

These instructions (or notes, rather) are meant for people who's googling
skills and patience are directly proportional to the amount of C programming
they don't already know :) .  I've done my best to organize and comment things
though, so I hope that just about anyone who manages to find their way all the
way here will be able to figure out a good deal from context.


### Change the Direction of the Diodes

That is, how to change whether the rows or the columns are being driven.  This can be done for each side of the keyboard separately.

* See [src/keyboard/ergodox/options.h] (src/keyboard/ergodox/options.h)


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


-------------------------------------------------------------------------------

Copyright &copy; 2012 Ben Blazak <benblazak.dev@gmail.com>  
Released under The MIT License (MIT) (see "license.md")  
Project located at <https://github.com/benblazak/ergodox-firmware>

