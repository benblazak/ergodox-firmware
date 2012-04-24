# Documentation : layout

## notes

* Assuming 560 bytes for everything else in RAM space, there's 2000 bytes left
  for the layout.  This should be enough for about 7 layers.  Watch your RAM
  usage if you're getting close.

  * The layout matricies could be moved to flash memory (program space, instead
    of data space), but that doesn't seem necessary at the moment.  It would
    also be slightly slower, though that probably shouldn't be a concern.

-------------------------------------------------------------------------------

Copyright &copy; 2012 Ben Blazak <benblazak.dev@gmail.com>  
Released under The MIT License (MIT) (see "license.md")  
Project located at <https://github.com/benblazak/ergodox-firmware>

