# Notes from the HID Device Class Definition, version 1.11


* sec 4.1 (The HID Class)
    * The `bInterfaceClass` member of an Interface descriptor is always 3 for
      HID class devices.

* sec 4.2 (Subclass)
    * The `bInterfaceSubClass` member declares whether a device supports a boot interface.
        * 0 => no subclass
        * 1 => boot interface subclass
        * 2..255 => reserved

* sec 4.3 (Protocols)
    * The `bInterfaceProtocol` member of an Interface descriptor only has meaning if the `bInterfaceSubClass` member declares that the device supports a boot interface, otherwise it is 0.
        * 0 => none
        * 1 => keyboard
        * 2 => mouse
        * 3..255 => reserved


-------------------------------------------------------------------------------

Copyright &copy; 2012 Ben Blazak <benblazak.dev@gmail.com>  
Released under The MIT License (MIT) (see "license.md")  
Project located at <https://github.com/benblazak/ergodox-firmware>

