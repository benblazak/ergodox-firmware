# -----------------------------------------------------------------------------
# This is mostly a stub at the moment, but I'm keeping it separate so I can
# mess with it later without changing the original
# -----------------------------------------------------------------------------
# Copyright (c) 2012 Ben Blazak
# Released under The MIT License (MIT) (see "license.md") at
# <https://github.com/benblazak/ergodox-firmware>
# -----------------------------------------------------------------------------


SRC = firmware.c

TEENSY_MAKE = $(MAKE) -f 'lib/teensy-makefile' SRC='$(SRC)'


.PHONY: all clean

all:
	$(TEENSY_MAKE) all

clean:
	$(TEENSY_MAKE) clean

