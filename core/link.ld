/**
 * core linker script for x86 architecture
 * 
 * SPDX-License-Identifier: GPL-2.0-only
 * Copyright (C) 2018, angel
 */

ENTRY(start)

SECTIONS
{
  . = 1M;
  __kernel_start = .;

  .boot :
  {
    *(.multiboot)
  }

  .text :
  {
    __text_start = .;
    *(.text)
    __text_end = .;
  }

  .data :
  {
    __data_start = .;
    *(.data)
    __data_end = .;
  }

  .bss :
  {
    __bss_start = .;
    *(.bss)
    __bss_end = .;
  }

  .rodata :
  {
    __rodata_start = .;
    *(.rodata)
    __rodata_end = .;
  }

  __kernel_end = .;
}
