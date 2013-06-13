# -----------------------------------------------------------------------------
# Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
# Released under The MIT License (see "doc/licenses/MIT.md")
# Project located at <https://github.com/benblazak/ergodox-firmware>
# -----------------------------------------------------------------------------

##                                                                  description
# eeprom options
#
# This file is meant to be included by the using '.../options.mk'
#


# TODO: add `call`s like this to other files that depend on things implicitly
$(call include_options_once,lib/timer)

SRC += $(wildcard $(CURDIR)/$(MCU).c)

