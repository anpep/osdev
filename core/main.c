//
//  kernel entry point
//  
//  SPDX-License-Identifier: GPL-2.0-only
//  Copyright (C) 2018, angel
//

#include <core/types.h>
#include <core/debug.h>
#include <core/io.h>
#include <core/mmu.h>

extern uintptr_t __kernel_start, __kernel_end,
                 __text_start, __text_end,
                 __data_start, __data_end,
                 __bss_start, __bss_end,
                 __rodata_start, __rodata_end;

void
main()
{
  debug_init_early();

  kprintf("kernel range: [0x%x..0x%x]\n", &__kernel_start, &__kernel_end);
  kprintf("  .text: [0x%x..0x%x]\n", &__text_start, &__text_end);
  kprintf("  .data: [0x%x..0x%x]\n", &__data_start, &__data_end);
  kprintf("  .bss: [0x%x..0x%x]\n", &__bss_start, &__bss_end);
  kprintf("  .rodata: [0x%x..0x%x]\n\n", &__rodata_start, &__rodata_end);

  kprintf("testing %u %u %u %u\n", 1, 2, 3, 4);
  mmu_setup();

  for (;;);
}
