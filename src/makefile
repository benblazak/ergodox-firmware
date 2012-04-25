# -----------------------------------------------------------------------------
# makefile for the ergoDOX project
#
# - .h file dependencies are automatically generated
# - 
#
# - This makefile was originally (extensively) modified from the WinAVR
#   makefile template, mostly by removing stuff.  The copy I used was from
#   [pjrc : usb_keyboard] (http://pjrc.com/teensy/usb_keyboard.zip).
# -----------------------------------------------------------------------------
# Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
# Released under The MIT License (MIT) (see "license.md")
# Project located at <https://github.com/benblazak/ergodox-firmware>
# -----------------------------------------------------------------------------


TARGET   = firmware
FORMAT   = ihex
KEYBOARD = ergodox   # see "src/keyboard" for what's available
LAYOUT   = qwerty    # see "src/keyboard/*/layout" for what's available

# firmware stuff
SRC  = $(wildcard *.c)
# keyboard stuff
# --- remove whitespace
KEYBOARD := $(strip $(KEYBOARD))
LAYOUT   := $(strip $(LAYOUT))
# --- include stuff
SRC += $(wildcard keyboard/$(KEYBOARD)*.c)
SRC += $(wildcard keyboard/$(KEYBOARD)/*.c)
SRC += $(wildcard keyboard/$(KEYBOARD)/layout/$(LAYOUT)*.c)
# library stuff
# - add more "*/*/..."s as necessary to compile everything.
# - parts the stuff under "lib" may not be necessary, depending on other
#   options, but it's all included here.  hopefully any unnecessary stuff gets
#   compiled out.  else, the makefile will have to become more complicated.
SRC += $(wildcard lib/*.c)
SRC += $(wildcard lib/*/*.c)
SRC += $(wildcard lib/*/*/*.c)

OBJ = $(SRC:%.c=%.o)


CFLAGS  = -mmcu=atmega32u4  # processor type (teensy 2.0); must match real
			    #   life
CFLAGS += -DF_CPU=16000000  # processor frequency; must match initialization
			    #   in source
CFLAGS += -I.               # search for includes in the current directory
# . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
CFLAGS += -DKEYBOARD='"keyboard/$(strip $(KEYBOARD)).h"'
CFLAGS += -DKEYBOARD_LAYOUT='"layout/$(strip $(LAYOUT)).h"'
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
LDFLAGS  = -Wl,--relax        # for some linker optimizations
LDFLAGS += -Wl,--gc-sections  # discard unused functions and data
# . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
# . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
GENDEPFLAGS += -MMD -MP -MF $@.dep  # generate dependency files


CC      = avr-gcc
OBJCOPY = avr-objcopy
SIZE    = avr-size


# remove extraneous whitespace
TARGET      := $(strip $(TARGET))
FORMAT      := $(strip $(FORMAT))

# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------

.PHONY: all clean

all: $(TARGET).hex $(TARGET).eep
	@echo
	@echo '---------------------------------------------------------------'
	@echo '------- done --------------------------------------------------'
	@echo
	$(SIZE) --target=$(FORMAT) $(TARGET).hex
	@echo
	$(SIZE) --target=$(FORMAT) $(TARGET).eep
	@echo
	@echo '. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .'
	@echo
	$(SIZE) -C --mcu=atmega32u4 $(TARGET).elf
	@echo '. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .'
	@echo
	@echo 'you can load "$(TARGET).hex" and "$(TARGET).eep" onto the'
	@echo 'Teensy using the Teensy loader'
	@echo
	@echo '---------------------------------------------------------------'
	@echo

clean:
	@echo
	@echo --- cleaning ---
	cd .. ; git clean -dX  # remove ignored files and directories

# -----------------------------------------------------------------------------

.SECONDARY:

%.hex: %.elf
	@echo
	@echo --- making $@ ---
	# from the WinAVR makefile template (modified)
	$(OBJCOPY) -O $(FORMAT) \
		-R .eeprom -R .fuse -R .lock -R .signature \
		$< $@

%.eep: %.elf
	@echo
	@echo --- making $@ ---
	# from the WinAVR makefile template (modified)
	-$(OBJCOPY) -O $(FORMAT) \
		-j .eeprom \
		--set-section-flags=.eeprom="alloc,load" \
		--change-section-lma .eeprom=0 \
		--no-change-warnings \
		$< $@ || exit 0

%.elf: $(OBJ)
	@echo
	@echo --- making $@ ---
	$(CC) $(strip $(CFLAGS)) $(strip $(LDFLAGS)) $^ --output $@

%.o: %.c
	@echo
	@echo --- making $@ ---
	$(CC) -c $(strip $(CFLAGS)) $(strip $(GENDEPFLAGS)) $< -o $@ 

# -----------------------------------------------------------------------------

-include $(OBJ:%=%.dep)

