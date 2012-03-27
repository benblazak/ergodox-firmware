# -----------------------------------------------------------------------------
# This is mostly a stub at the moment, but I'm keeping it separate so I can
# mess with it later without changing the original
# -----------------------------------------------------------------------------
# Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
# Released under The MIT License (MIT) (see "license.md")
# Project located at <https://github.com/benblazak/ergodox-firmware>
# -----------------------------------------------------------------------------


TARGET = ergodox-firmware

SRC = $(shell find -maxdepth 1 -name '*.c') \
      $(shell find ./keyboard  -name '*.c') \
      $(shell find ./lib       -name '*.c') \
      ./lib-other/peter-fleury/i2cmaster/twimaster.c \
      ./lib-other/pjrc/blinky/print.c \
      ./lib-other/pjrc/blinky/usb_debug_only.c \
      ./lib-other/arduino/arduino/libraries/Wire/utility/twi.c
      

EXTRAINCDIRS = .

TEENSY_MAKE = $(MAKE) -f 'lib-other/pjrc/blinky/Makefile' \
	      TARGET='$(TARGET)' \
	      SRC='$(SRC)' \
	      EXTRAINCDIRS='$(EXTRAINCDIRS)'


.PHONY: all clean

all:
	$(TEENSY_MAKE) all

clean:
	$(TEENSY_MAKE) clean

