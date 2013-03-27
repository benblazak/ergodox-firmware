# -----------------------------------------------------------------------------
# Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
# Released under The MIT License (see "doc/licenses/MIT.md")
# Project located at <https://github.com/benblazak/ergodox-firmware>
# -----------------------------------------------------------------------------

##                                                                  description
# A central place for all ErgoDox-specific Makefile-level things
#
# This file is meant to be included by '.../firmware/makefile'
#


include ../../../firmware/lib/twi/options.mk
include ../../../firmware/lib/usb/options.mk
include ../../../firmware/lib/layout/key-functions/options.mk
# TODO: add other 'options.mk' files as they appear


BINARY_FORMAT := ihex
# the binary format to generate

MCU := atmega32u4
# processor type (for the teensy 2.0)

F_CPU := 16000000
# processor speed, in Hz; max value is 16000000 (16MHz)

KEYBOARD_LAYOUT := qwerty-kinesis-mod
# default layout for this keyboard

KEYBOARD_LAYOUTS := \
	colemak-symbol-mod \
	dvorak-kinesis-mod \
	qwerty-kinesis-mod
# a list of all available layouts for this keyboard

# -----------------------------------------------------------------------------

SCR += $(wildcard *.c)
SRC += $(wildcard controller/*.c)
SRC += $(wildcard layout/$(KEYBOARD_LAYOUT)*.c)

CFLAGS += -include $(wildcard options.h)

