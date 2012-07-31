# Documentation : layout

Different layouts are included by modifying a variable in the makefile.

To write a new one:
* Create new layout files under [layout] (layout) (see [qwerty.h]
  (layout/qwerty.h) and [qwerty.c] (layout/qwerty.c)).
* Use `0` for no-operation (unused) keys, and `NULL` for no-operation (unused)
  functions.
* See [matrix/mapping.h] (matrix/mapping.h) for how the key matrix maps to
  hardware.
* See [keyboard-usage-page--short-names.h]
  (../../lib/_usb/keyboard-usage-page--short-names.h) for available keycodes.
* See [key-functions.c] (../../lib/key-functions.c) for what functions keys
  can call.


## notes

* Each full layer takes 420 bytes of memory (the matrix size is 12x7, keycodes
  are 1 byte each, and function pointers are 2 bytes each).

-------------------------------------------------------------------------------

Copyright &copy; 2012 Ben Blazak <benblazak.dev@gmail.com>  
Released under The MIT License (MIT) (see "license.md")  
Project located at <https://github.com/benblazak/ergodox-firmware>

