# -----------------------------------------------------------------------------
# This is mostly a stub at the moment, but I'm keeping it separate so I can
# mess with it later without changing the original
# -----------------------------------------------------------------------------
# Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
# Released under The MIT License (MIT) (see "license.md")
# Project located at <https://github.com/benblazak/ergodox-firmware>
# -----------------------------------------------------------------------------


TARGET = test

EXTRAINCDIRS = .

TEENSY_MAKE = $(MAKE) -f '../lib-other/pjrc/blinky/Makefile' \
	      TARGET='$(TARGET)' \
	      EXTRAINCDIRS='$(EXTRAINCDIRS)'

.PHONY: test_pwm test_twi

test_pwm:
	$(TEENSY_MAKE) all \
		SRC='test_pwm.c'

test_twi:
	$(TEENSY_MAKE) all \
		SRC='test_twi.c'

.PHONY: clean

clean:
	$(TEENSY_MAKE) clean \
		SRC='$(shell find -name '*.c')'

