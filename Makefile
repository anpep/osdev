##
##  main kernel build rules
##  
##  SPDX-License-Identifier: GPL-2.0-only
##  Copyright (C) 2018, angel
##

.PHONY: kconfig core img clean

-include common.mk

##
##  DEFAULT TARGET
##
all: kconfig core

##
##  KERNEL CONFIGURATION CHECK TARGET
##
kconfig:
	@[ -f "${KCONFIG_FILE}" ] || ($(call _fail,kernel configuration not found. \
		Run \`make menuconfig\` or supply an existing ${KCONFIG_FILE} file)&&exit 1)

##
##  KERNEL TARGETS
##

####  OS core
core:
	${Q}make --silent -C core/

####  system boot image
img: core
	${Q}make --silent -C img/

##
##  GRAPHICAL CONFIGURATION TOOL
##
menuconfig:
	${Q}${PYTHON3} tool/kconfig/menuconfig.py

##
##  CLEAN TARGETS
##
clean:
	${Q}make --silent -C core/ clean
	${Q}make --silent -C img/ clean
