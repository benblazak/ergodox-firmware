## TODO

- fix and expand the ability of keys to do different things depending on what
  kind of key was pressed before
- fix the issue with shifted keys sometimes causing subsequent keys to be
  shifted, when typing quickly (shift should probably be released when the next
  key is pressed, in this case, if the original shifted key hasn't been
  released)
- maybe implement a separate per-key debounce, so that keys are scanned
  quickly, but can only be pressed 1 time every 15 (or something) milliseconds.

### Tutorials
- basic key functions
    - mention where people should look for more information; probably, the usb, key_functions, and keys headers; and others?
- sticky keys
    - maybe write a chordmak (or asetniop) layaout, on top of a standard
      colemak layout, using chained sticky keys for the modifiers
- macros
- chorded keys
- timed keys
- automatic repetition of utf-8 sequence keys
- layers
- making layouts
- changing the meaning of the LEDs

-------------------------------------------------------------------------------

Copyright &copy; 2014 Ben Blazak <benblazak.dev@gmail.com>  
Released under The MIT License (see "doc/licenses/MIT.md")  
Project located at <https://github.com/benblazak/ergodox-firmware>

