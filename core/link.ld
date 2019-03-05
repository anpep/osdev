/**
 * core linker script for x86 architecture
 * 
 * SPDX-License-Identifier: GPL-2.0-only
 * Copyright (C) 2018, angel
 */

ENTRY(start)

SECTIONS
{
  . = 0xc0100000;
  __kernel_start = .;

  .text ALIGN (4K) : AT (ADDR (.text) - 0xc0000000)
  {
    __text_start = .;
    *(.boot)
    *(.text)
    __text_end = .;
  }

  .rodata ALIGN (4K) : AT (ADDR (.rodata) - 0xc0000000)
  {
    __rodata_start = .;
    *(.rodata)
    __rodata_end = .;
  }

  .data ALIGN (4K) : AT (ADDR (.data) - 0xc0000000)
  {
    __data_start = .;
    *(.data)
    __data_end = .;
  }

  .bss ALIGN (4K) : AT (ADDR (.bss) - 0xc0000000)
  {
    __bss_start = .;
    *(.bss)
    __bss_end = .;
  }

  __kernel_end = .;
}
