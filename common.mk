##
##  common macros for Makefiles
##  
##  SPDX-License-Identifier: GPL-2.0-only
##  Copyright (C) 2018, angel
##

# specifies the kernel configuration file
KCONFIG_FILE ?= .config

-include $(dir $(lastword ${MAKEFILE_LIST}))/${KCONFIG_FILE}

ifeq (${BUILD_VERBOSE},y)
export Q=
else
export Q=@
endif

##
##  LOG OUTPUT MACROS
##
define _fail
  (/bin/echo -e "\x1b[31mfail:" $1 "\x1b[0m"; exit 1)
endef
define _done
  (/bin/echo -e "\x1b[32mdone:" $1 "\x1b[0m")
endef
define _warn
  (/bin/echo -e "\x1b[33mwarn:" $1 "\x1b[0m")
endef
define _verb
  (/bin/echo -e "\x1b[90mverb:" $1 "\x1b[0m")
endef
define _step
  (/bin/echo -e "\x1b[$1m$2:" $3 "\x1b[0m")
endef

define fail
  @$(call _fail,$1)
endef
define done
  @$(call _done,$1)
endef
define warn
  @$(call _warn,$1)
endef
define verb
  @$(call _verb,$1)
endef
define step
  @$(call _step,$1,$2,$3)
endef

##
##  TOOLCHAIN
##
export CC = gcc
export AS = nasm
export LD = ld

export PYTHON3 = python3
