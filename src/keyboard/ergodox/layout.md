# Documentation : layout

Different layouts are included by modifying a variable in the makefile.

To write a new one:
* You must implement everything defined in [layout.h] (layout.h).  Take a look
  at existing layouts in the 'layout' subdir.
    * Currently, see [qwerty.c] (layout/qwerty.c) and [qwerty.h]
      (layout/qwerty.h).  The latter is only important if you want more than
      one layer.  And I still need to write the functions to make that possible
      (though that shouldn't be hard, I just haven't gotten to it yet).  But
      (at least for the QWERTY and Dvorak layouts I'd really like to include)
      if you indicate it clealy in the layout, and provide complete
      initializations for `kb_layout[][][]`, `kb_layout_press[][][]`, and
      `kb_layout_release[][][]`, I'll make sure it gets working.
* The number of layers must be defined in the layout *.h file.
* Use `0` for no-operation (unused) keys, and `NULL` for no-operation (unused)
  functions.
* See [matrix.md] (matrix.md) for how the key matrix maps to hardware.
* See [keyboard-usage-page--short-names.h]
  (../../lib/_usb/keyboard-usage-page--short-names.h) for available keycodes.
* See [key-functions.c] (../../lib/_key-functions.c) for what functions keys
  can call.
* See [_defaults.h] (layout/_defaults.h) for default function layers and
  aliases.


## notes

* Each full layer takes 420 bytes of memory, wherever it's stored.  (The matrix
  size is 12x7, keycodes are 1 byte each, and function pointers are 2 bytes
  each.)

-------------------------------------------------------------------------------

Copyright &copy; 2012 Ben Blazak <benblazak.dev@gmail.com>  
Released under The MIT License (MIT) (see "license.md")  
Project located at <https://github.com/benblazak/ergodox-firmware>

