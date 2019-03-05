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

  .boot BLOCK(4K) : ALIGN(4K)
  {
    *(.boot)
  }

  .text BLOCK(4K) : ALIGN(4K)
  {
    __text_start = .;
    *(.text)
    __text_end = .;
  }

  .rodata BLOCK(4K) : ALIGN(4K)
  {
    __rodata_start = .;
    *(.rodata)
    __rodata_end = .;
  }

  .data BLOCK(4K) : ALIGN(4K)
  {
    __data_start = .;
    *(.data)
    __data_end = .;
  }

  .bss BLOCK(4K) : ALIGN(4K)
  {
    __bss_start = .;
    *(.bss)
    __bss_end = .;
  }

  __kernel_end = .;
}
