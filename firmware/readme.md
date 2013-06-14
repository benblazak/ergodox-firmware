<!-- TODO: everything ... -->

## TODO
- include versions for all build environment programs

- generate documentation
    - include a collection of all "namespace" prefixes, and where they belong
    - write a note in "main.c" about where that file is (and about other
      documentation that would help in understanding the code)
    - write a note about where options are described, how they're included, how
      i have makefiles set up, etc.
    - write a mediumly thorough note about my workflow (vim, ...)

- add a note in the docs somewhere that SDA and SCL need to have a pull-up
  resistor on them, or `mcp23018__init()` will hang (or something like that)

- add notes to directories, explaining why things are organized the way they
  are; specifically, why the directory structure is so deep

## Dependencies
- the gnu avr toolchain
- python 3
  - markdown `sudo pip install markdown`
- git (for cleaning)


-------------------------------------------------------------------------------

Copyright &copy; 2012, 2013 Ben Blazak <benblazak.dev@gmail.com>  
Released under The MIT License (see "doc/licenses/MIT.md")  
Project located at <https://github.com/benblazak/ergodox-firmware>

