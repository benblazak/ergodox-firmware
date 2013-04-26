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


BINARY_FORMAT := ihex
# the binary format to generate

MCU := atmega32u4
# processor type (for the teensy 2.0)

F_CPU := 16000000
# processor speed, in Hz; max value is 16000000 (16MHz); must match
# initialization in source

KEYBOARD_LAYOUT := qwerty-kinesis-mod
# default layout for this keyboard

KEYBOARD_LAYOUTS := \
	colemak-symbol-mod \
	dvorak-kinesis-mod \
	qwerty-kinesis-mod
# a list of all available layouts for this keyboard

# -----------------------------------------------------------------------------

CURDIRS := $(CURDIR) $(CURDIRS)
# -------
CURDIR := $(ROOTDIR)/lib/twi
include $(CURDIR)/options.mk
# -------
CURDIR := $(ROOTDIR)/lib/layout/eeprom-macro
include $(CURDIR)/options.mk
# -------
CURDIR := $(ROOTDIR)/lib/layout/key-functions
include $(CURDIR)/options.mk
# -------
CURDIR := $(ROOTDIR)/lib/layout/layer-stack
include $(CURDIR)/options.mk
# -------
CURDIR := $(firstword $(CURDIRS))
CURDIRS := $(wordlist 2,$(words $(CURDIRS)),$(CURDIRS))

# -----------------------------------------------------------------------------

SRC += $(wildcard $(CURDIR)/*.c)
SRC += $(wildcard $(CURDIR)/controller/*.c)
SRC += $(wildcard $(CURDIR)/layout/$(KEYBOARD_LAYOUT)*.c)

CFLAGS += -include $(wildcard $(CURDIR)/options.h)

$(CURDIR)/layout/qwerty-kinesis-mod.o: $(wildcard $(CURDIR)/layout/common/*)
$(CURDIR)/layout/dvorak-kinesis-mod.o: $(wildcard $(CURDIR)/layout/common/*)
$(CURDIR)/layout/colemak-symbol-mod.o: $(wildcard $(CURDIR)/layout/common/*)

