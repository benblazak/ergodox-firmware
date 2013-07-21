# -----------------------------------------------------------------------------
# Copyright (c) 2013 Gyuri Horak <dyuri@horak.hu>
# Released under The MIT License (see "doc/licenses/MIT.md")
# Project located at <https://github.com/benblazak/ergodox-firmware>
# -----------------------------------------------------------------------------

##
# mouse options
#
# This file is meant to be included by the using '.../options.mk'
#

ifdef MOUSE_ENABLE
  SRC += $(wildcard $(CURDIR)/*.c)
endif

