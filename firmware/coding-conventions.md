# Coding Conventions


## Comments
`/** ... */` comments are to be written in YAML, so they can be processed by
external tools to generate documentation, and for other purposes.


## "Namespace" prefixes
"Namespace" prefixes are prepended to variables and macros (in lower and upper
case, respectively), sometimes hierarchically, separated by `__`.  I call them
what I do because this is somewhat similar to using `::` for namespace
separation as in C++.

* `KB`: from `firmware/keyboard/...`

* `MAKE`: passed to the compiler by `make` (i.e. a global option)


-------------------------------------------------------------------------------

Copyright &copy; 2012 Ben Blazak <benblazak.dev@gmail.com>  
Released under The MIT License (see "license.md")  
Project located at <https://github.com/benblazak/ergodox-firmware>

