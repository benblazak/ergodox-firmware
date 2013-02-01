# -----------------------------------------------------------------------------
# Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
# Released under The MIT License (see "doc/licenses/MIT.md")
# Project located at <https://github.com/benblazak/ergodox-firmware>
# -----------------------------------------------------------------------------

##                                                                  description
# A central place for all `main()` related Makefile-level options
#
# This file is meant to be included by '.../firmware/makefile'
#


SRC += $(wildcard ../main.c)
SRC += $(wildcard main/*.c)

CFLAGS += -include $(wildcard options.h)

