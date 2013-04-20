# -----------------------------------------------------------------------------
# Copyright (c) 2012, 2013 Ben Blazak <benblazak.dev@gmail.com>
# Released under The MIT License (see "doc/license.md")
# Project located at <https://github.com/benblazak/ergodox-firmware>
# -----------------------------------------------------------------------------

##                                                                  description
# Makefile for the firmware
#
# See '.../firmware/keyboard/.../options.mk' for options
#
# Notes:
# - '.h' file dependencies are automatically generated
#
# History:
# - This makefile was originally (extensively) modified from the WinAVR
#   makefile template, mostly by removing stuff.  The copy I used was from
#   [pjrc : usb_keyboard] (http://pjrc.com/teensy/usb_keyboard.zip).
#

# -----------------------------------------------------------------------------

KEYBOARD_NAME := ergodox
# the name of the keyboard to build a firmware for

TARGET := firmware
# default name for the '.hex', '.eep', and '.map' files we'll be generating

# -----------------------------------------------------------------------------

default-target: all
# (to retain default behavior when included makefiles specify dependencies)

CURDIR  := .
ROOTDIR := .
# note: by default, `CURDIR` is initialized to (an absolute path to) the
# current working directory

SRC         :=
CFLAGS      :=
LDFLAGS     :=
GENDEPFLAGS :=
# (initialize variables, so we can use `+=` below and in the included files)

CURDIRS := $(CURDIR) $(CURDIRS)
# -------
CURDIR := $(ROOTDIR)/keyboard/$(KEYBOARD_NAME)
include $(CURDIR)/options.mk
# (the place for everything a keyboard implementation might want to change)
# -------
CURDIR := $(ROOTDIR)/lib/timer
include $(CURDIR)/options.mk
# -------
CURDIR := $(firstword $(CURDIRS))
CURDIRS := $(wordlist 2,$(words $(CURDIRS)),$(CURDIRS))

# -----------------------------------------------------------------------------

SRC += $(wildcard $(CURDIR)/main.c)
# (other source files included through the makefile included above)

# -----------------------------------------------------------------------------

CFLAGS += -mmcu=$(MCU)      # processor type; must match real life
CFLAGS += -DF_CPU=$(F_CPU)  # processor frequency; must match initialization
			    #   in source
# . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
CFLAGS += -std=gnu99  # use C99 plus GCC extensions
CFLAGS += -Os         # optimize for size
# . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
CFLAGS += -Wall                # enable lots of common warnings
CFLAGS += -Wstrict-prototypes  # "warn if a function is declared or defined
			       #   without specifying the argument types"
# . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
CFLAGS += -fpack-struct  # "pack all structure members together without holes"
CFLAGS += -fshort-enums  # "allocate to an 'enum' type only as many bytes as it
			 #   needs for the declared range of possible values"
# . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
CFLAGS += -ffunction-sections  # \ "place each function or data into its own
CFLAGS += -fdata-sections      # /   section in the output file if the
			       #     target supports arbitrary sections."  for
			       #     linker optimizations, and discarding
			       #     unused code.
# . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
# . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
LDFLAGS += -Wl,-Map=$(TARGET).map,--cref  # generate a link map, with a cross
					  #   reference table
LDFLAGS += -Wl,--relax        # for some linker optimizations
LDFLAGS += -Wl,--gc-sections  # discard unused functions and data
# . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
# . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
GENDEPFLAGS += -MMD -MP -MF $@.dep  # generate dependency files

# -----------------------------------------------------------------------------

CC      := avr-gcc
OBJCOPY := avr-objcopy
SIZE    := avr-size

# -----------------------------------------------------------------------------

OBJ := $(SRC:%.c=%.o)


# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------

.PHONY: all clean

all: $(TARGET).hex $(TARGET).eep
	@echo
	@echo '---------------------------------------------------------------'
	@echo '------- done --------------------------------------------------'
	@echo
	$(SIZE) --target=$(BINARY_FORMAT) $(TARGET).hex
	@echo
	$(SIZE) --target=$(BINARY_FORMAT) $(TARGET).eep
	@echo
	@echo 'you can load "$(TARGET).hex" and "$(TARGET).eep" onto the'
	@echo 'Teensy using the Teensy loader'
	@echo
	@echo '---------------------------------------------------------------'
	@echo

clean:
	@echo
	@echo '--- cleaning ---'
	git clean -dX  # remove ignored files and directories

# -----------------------------------------------------------------------------

.SECONDARY:

%.hex: %.elf
	@echo
	@echo '--- making $@ ---'
	# from the WinAVR makefile template (modified)
	$(OBJCOPY) -O $(BINARY_FORMAT) \
		-R .eeprom -R .fuse -R .lock -R .signature \
		$< $@

%.eep: %.elf
	@echo
	@echo '--- making $@ ---'
	# from the WinAVR makefile template (modified)
	-$(OBJCOPY) -O $(BINARY_FORMAT) \
		-j .eeprom \
		--set-section-flags=.eeprom="alloc,load" \
		--change-section-lma .eeprom=0 \
		--no-change-warnings \
		$< $@ || exit 0

$(TARGET).elf: $(OBJ)
	@echo
	@echo '--- making $@ ---'
	$(CC) $(strip $(CFLAGS)) $(strip $(LDFLAGS)) $^ --output $@

%.o: %.c
	@echo
	@echo '--- making $@ ---'
	$(CC) -c $(strip $(CFLAGS)) $(strip $(GENDEPFLAGS)) $< -o $@

# -----------------------------------------------------------------------------

-include $(OBJ:%=%.dep)

