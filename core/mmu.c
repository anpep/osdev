//
//  x86 MMU setup
//  
//  SPDX-License-Identifier: GPL-2.0-only
//  Copyright (C) 2018, angel
//

#include <core/mmu.h>
#include <core/types.h>
#include <core/debug.h>

/**
 * Kernel page directory
 * @remarks This variable falls into .bss, so we assume it's initialized to 0
 */
extern struct mmu_pdir_entry early_pdir[1024];

status_t
mmu_setup(void)
{
  kprintf("page dir entry size: %u\ntotal size: %u\n",
          sizeof(struct mmu_pdir_entry),
          sizeof(early_pdir));
  
  int i = 0;
  for (struct mmu_pdir_entry *pdir_ent = early_pdir;
       i < 1024;
       pdir_ent++, i++)
  {
    if (!pdir_ent->addr)
    {
      continue;
    }

    kprintf("page directory entry %u:\n", i);
    kprintf("  addr: 0x%x\n", pdir_ent->addr);
    kprintf("  flags: 0x%x\n", pdir_ent->flags);

    int j = 0;
    for (struct mmu_ptab_entry *ptab_ent = (struct mmu_ptab_entry *)
      (0xC0000000 + pdir_ent->addr * 0x1000);
      j < 1024;
      ptab_ent++, j++)
    {
      if (!ptab_ent->addr)
      {
        continue;
      }

      kprintf("  page table entry %u:\n", j);
      kprintf("    addr: 0x%x\n", ptab_ent->addr);
      kprintf("    flags: 0x%x\n", ptab_ent->flags);;
    }    
  }
}

status_t
mmu_map_page(uintptr_t phys_addr,
             uintptr_t virt_addr,
             unsigned flags)
{
}
