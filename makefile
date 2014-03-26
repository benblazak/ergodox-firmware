# -----------------------------------------------------------------------------
# makefile for the ergoDOX project
#
# This should produce a single file (probably in an archive format) for
# distribution, containing everything people will need to use the software.
#
# DEPENDENCIES:  This is unabashedly dependant on (the GNU implementation of)
# various Unix commands, and therefore probably won't work in a Windows
# environment (besides maybe cygwin).  Sorry...  I don't know a good portable
# way to write it.
#
# TODO:
# - include doc files (and maybe render them in html)
# - include the UI stuff (once it's done)
# -----------------------------------------------------------------------------
# Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
# Released under The MIT License (MIT) (see "license.md")
# Project located at <https://github.com/benblazak/ergodox-firmware>
# -----------------------------------------------------------------------------


include src/makefile-options

# which layouts to compile (will override the variable in src/makefile-options)
# --- default
LAYOUT := qwerty-kinesis-mod
# --- all
LAYOUTS := qwerty-kinesis-mod dvorak-kinesis-mod colemak-symbol-mod workman-p-kinesis-mod

# system specific stuff
UNAME := $(shell uname)
ifeq ($(UNAME),Darwin)
	DATE_PROG := gdate
else
	DATE_PROG := date
endif

CURRENT_DATE := $(shell $(DATE_PROG) --rfc-3339 s)

# git info
GIT_BRANCH := $(shell git branch -l | grep '*' | cut -c 3-)
GIT_COMMIT_DATE := $(shell git log -n 1 --pretty --date=iso | grep 'Date' | cut -c 9- )
GIT_COMMIT_ID := $(shell git log -n 1 | grep 'commit' | cut -c 8-)

# name to use for the final distribution file or package
TARGET := ergodox-firmware--$(GIT_BRANCH)--$(shell $(DATE_PROG) -d "$(GIT_COMMIT_DATE)" +'%Y%m%dT%H%M%S')--$(shell echo $(GIT_COMMIT_ID) | cut -c 1-7)--$(LAYOUT)

# directories
BUILD := build
ROOT := $(BUILD)/$(TARGET)
SCRIPTS := build-scripts

# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------

.PHONY: all clean checkin build-dir firmware dist zip zip-all

all: dist

clean:
	git clean -dX  # remove ignored files and directories
	-rm -r '$(BUILD)'

checkin:
	-git commit -a

build-dir:
	-rm -r '$(BUILD)/$(TARGET)'*
	-mkdir -p '$(BUILD)/$(TARGET)'

firmware:
	cd src; $(MAKE) LAYOUT=$(LAYOUT) all

$(ROOT)/firmware.%: firmware
	cp 'src/firmware.$*' '$@'


$(ROOT)/firmware--ui-info.json: $(SCRIPTS)/gen-ui-info.py checkin
	( ./'$<' \
		--current-date '$(shell $(DATE_PROG) --rfc-3339 s)' \
		--git-commit-date '$(GIT_COMMIT_DATE)' \
		--git-commit-id '$(GIT_COMMIT_ID)' \
		--map-file-path '$(BUILD)/$(TARGET)/firmware.map' \
		--source-code-path 'src' \
		--matrix-file-path 'src/keyboard/$(KEYBOARD)/matrix.h' \
		--layout-file-path \
			'src/keyboard/$(KEYBOARD)/layout/$(LAYOUT).c' \
	) > '$@'

$(ROOT)/firmware--layout.html: \
	$(SCRIPTS)/gen-layout.py \
	$(ROOT)/firmware--ui-info.json
	\
	( ./'$<' \
		--ui-info-file '$(ROOT)/firmware--ui-info.json' \
	) > '$@'


dist: \
	checkin \
	build-dir \
	$(ROOT)/firmware.hex \
	$(ROOT)/firmware.eep \
	$(ROOT)/firmware.map \
	$(ROOT)/firmware--ui-info.json \
	$(ROOT)/firmware--layout.html

zip: dist
	( cd '$(BUILD)/$(TARGET)'; \
	  zip '../$(TARGET).zip' \
	      -r * .* \
	      -x '..*' )

zip-all:
	for layout in $(LAYOUTS); do \
		make LAYOUT=$$layout zip; \
	done

