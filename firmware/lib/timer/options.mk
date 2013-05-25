# -----------------------------------------------------------------------------
# Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
# Released under The MIT License (see "doc/licenses/MIT.md")
# Project located at <https://github.com/benblazak/ergodox-firmware>
# -----------------------------------------------------------------------------

##                                                                  description
# timer options
#
# This file is meant to be included by '.../firmware/makefile'
#


SRC += $(wildcard $(CURDIR)/*.c)
SRC += $(wildcard $(CURDIR)/device/$(MCU).c)

