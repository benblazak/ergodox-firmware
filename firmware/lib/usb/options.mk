# -----------------------------------------------------------------------------
# Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
# Released under The MIT License (see "doc/licenses/MIT.md")
# Project located at <https://github.com/benblazak/ergodox-firmware>
# -----------------------------------------------------------------------------

##                                                                  description
# USB keyboard options
#
# This file is meant to be included by '.../firmware/makefile'
#


SRC += $(wildcard $(CURDIR)/$(MCU)/*.c)

ifeq '$(MCU)' 'atmega32u4'
	SRC += $(wildcard $(CURDIR)/$(MCU)/keyboard/from-pjrc/*.c)
endif

