//
//  kernel entry point
//  
//  SPDX-License-Identifier: GPL-2.0-only
//  Copyright (C) 2018, angel
//

#include <core/types.h>
#include <core/multiboot2.h>
#include <core/debug.h>
#include <core/io.h>

extern uintptr_t __kernel_start, __kernel_end,
                 __text_start, __text_end,
                 __data_start, __data_end,
                 __bss_start, __bss_end,
                 __rodata_start, __rodata_end;

static inline void __attribute__((noreturn))
_halt(void)
{
  __asm__("hlt");
  for (;;);
}

void
main(uint32_t magic,
     uintptr_t mbi_start)
{
  debug_init_early();

  if (magic != MULTIBOOT2_BOOTLOADER_MAGIC)
  {
    kprintf("loader is not multiboot-compliant");
    _halt();
  }

  if (mbi_start & 7)
  {
    kprintf("unaligned multiboot structure");
    _halt();
  }

  kprintf("mbi size: 0x%x\n", *((uint32_t *) mbi_start));
  for (struct multiboot_tag *tag = (struct multiboot_tag *) (mbi_start + 8);
       tag->type != MULTIBOOT_TAG_TYPE_END;
       tag = (struct multiboot_tag *) ((multiboot_uint8_t *) tag + ((tag->size + 7) & ~7)))
  {
    kprintf("tag 0x%x, size 0x%x\n", tag->type, tag->size);
    switch (tag->type)
    {
      case MULTIBOOT_TAG_TYPE_BASIC_MEMINFO:
      {
        const struct multiboot_tag_basic_meminfo *meminfo = 
          (struct multiboot_tag_basic_meminfo *) tag;

        kprintf("basic_meminfo: mem_lower=0x%x, mem_upper=0x%x\n",
          meminfo->mem_lower, meminfo->mem_upper);
        kprintf("system memory start address: 0x%x\n",
          1024 * meminfo->mem_lower);
        kprintf("system memory end address: 0x%x\n",
          1024 * meminfo->mem_upper);
        kprintf("total usable system memory: %u bytes\n\n",
          1024 * (meminfo->mem_upper - meminfo->mem_lower));

        kprintf("kernel range: [0x%x..0x%x]\n", &__kernel_start, &__kernel_end);
        kprintf("  .text: [0x%x..0x%x]\n", &__text_start, &__text_end);
        kprintf("  .data: [0x%x..0x%x]\n", &__data_start, &__data_end);
        kprintf("  .bss: [0x%x..0x%x]\n", &__bss_start, &__bss_end);
        kprintf("  .rodata: [0x%x..0x%x]\n\n", &__rodata_start, &__rodata_end);

        kprintf("total kernel memory: %u bytes\n",
          &__kernel_end - &__kernel_start);
        kprintf("total user memory: %u bytes\n",
          1024 * (meminfo->mem_upper - meminfo->mem_lower) -
          (&__kernel_end - &__kernel_start));
      }
    }
  }
}
