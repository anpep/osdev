##
##  system core build rules
##  
##  SPDX-License-Identifier: GPL-2.0-only
##  Copyright (C) 2018, angel
##

-include ../common.mk

COBJS = $(patsubst %.c,%.o,$(shell find . -type f -name "*.c"))
SOBJS = $(patsubst %.asm,%.o,$(shell find . -type f -name "*.asm"))

CFLAGS = -m32 -std=c99 -nostdlib -ffreestanding \
         -mno-mmx -mno-sse -mno-sse2 -masm=intel \
         -Wall -Wextra \
         -I./include
         $(CORE_EXTRA_CFLAGS)
AFLAGS = -f elf32
LFLAGS = -melf_i386

ifeq (${CONFIG_CORE_DEBUG},y)
CFLAGS += -O0 -g
endif

all: core.elf

core.elf: ${SOBJS} ${COBJS}
	$(call step,37,  ld,$@)
	${Q}${LD} ${LFLAGS} -n -T link.ld -o $@ $^

%.o: %.asm
	$(call step,38,  as,$<)
	${Q}${AS} -o $@ ${AFLAGS} $<

%.o: %.c
	$(call step,36,  cc,$<)
	${Q}${CC} ${CFLAGS} -c $< -o $@

clean:
	${Q}rm -f core.elf ${COBJS} ${SOBJS}
	$(call done,cleaned output files)

.PHONY: all clean
