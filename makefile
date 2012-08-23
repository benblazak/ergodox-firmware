# -----------------------------------------------------------------------------
# makefile for the ergoDOX project
#
# This should produce a single file (probably in an archive format) for
# distribution, containing everything people will need to use the software.
#
# DEPENDENCIES:  This is unabashedly dependant on various Unix commands, and
# therefore probably won't work in a Windows environment.  I'm sorry...  I
# don't know a good portable way to write it.
#
# TODO:
# - include doc files (and maybe render them in html)
# - include the UI stuff (once it's done)
# -----------------------------------------------------------------------------
# Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
# Released under The MIT License (MIT) (see "license.md")
# Project located at <https://github.com/benblazak/ergodox-firmware>
# -----------------------------------------------------------------------------


# the base name of the file or package to distribute
NAME := ergodox-firmware
# git info
GIT_BRANCH := $(shell git branch -l | grep '*' | cut -c 3-)
GIT_COMMIT_DATE := $(shell git log -n 1 --pretty --date=iso | grep 'Date' | cut -c 9- )
GIT_COMMIT_ID := $(shell git log -n 1 | grep 'commit' | cut -c 8-)

# name to use for the final distribution file or package
TARGET := $(NAME)--$(GIT_BRANCH)--$(shell date -d "$(GIT_COMMIT_DATE)" +'%Y%m%dT%H%M%S')--$(shell echo $(GIT_COMMIT_ID) | cut -c 1-7)

# the build dir
BUILD := build

# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------

.PHONY: all clean dist

all: dist

clean:
	git clean -dX  # remove ignored files and directories
	-rm -r '$(BUILD)'

dist:
	# make sure we're checked in
	git commit -a
	# set up the build dir
	-rm -r '$(BUILD)/$(TARGET)'*
	-mkdir -p '$(BUILD)/$(TARGET)'
	# make all subprojects
	cd src; $(MAKE) all
	# copy stuff to build dir
	# --- from src
	( cd src; \
	  cp firmware.hex firmware.eep firmware.map \
	     '../$(BUILD)/$(TARGET)' )
	# run secondary build scripts
	( ./build-scripts/gen-ui-info.py \
		--git-commit-date '$(GIT_COMMIT_DATE)' \
		--git-commit-id '$(GIT_COMMIT_ID)' \
		--map-file-path '$(BUILD)/$(TARGET)/firmware.map' \
		--source-code-path 'src' \
	) > '$(BUILD)/$(TARGET)/firmware--ui-info.json'
	# make into a zip archive
	( cd '$(BUILD)/$(TARGET)'; \
	  zip '../$(TARGET).zip' \
	      -r * .* \
	      -x '..*' )

