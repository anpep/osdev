//
//  x86 MMU setup
//  
//  SPDX-License-Identifier: GPL-2.0-only
//  Copyright (C) 2018, angel
//

#pragma once

#include <core/status.h>

/**
 * @brief Page directory entry flags
 */
enum
{
  /**
   * @brief Page is present
   * @details (P) Present; must be 1 to reference a page table
   */
  PDE_PRESENT = 1 << 0,

  /**
   * @brief Page is writable
   * @details (R/W) Read/write; if 0, writes may not be allowed to the 4-MByte
   *          region controlled by this entry
   */
  PDE_WRITABLE = 1 << 1,

  /**
   * @brief Page is owned by the kernel
   * @details (U/S) User/supervisor; if 0, user-mode accesses are not allowed to
   *          the 4-MByte region controlled by this entry
   */
  PDE_KERNEL = 1 << 2
};

/**
 * @brief 4MiB page directory entry
 */
struct __attribute__((packed)) mmu_pdir_entry
{
  /**
   * Page directory entry flags
   */
  int flags : 12;  //  0..11

  /**
   * Physical address of the 4KiB aligned page table referenced by this entry
   */
  int addr : 20;   // 12..31
};

/**
 * @brief 4KiB page table entry
 */
struct __attribute__((packed, aligned(4))) mmu_ptab_entry
{
  /**
   * Page table entry flags
   */
  int flags : 12;  //  0..11

  /**
   * Physical address of the 4KiB page referenced by this entry
   */
  int addr : 20;   // 12..13
};

/**
 * @brief Sets up kernel page tables
 * 
 * @return A code indicating whether page tables were successfully set up or not
 */
status_t mmu_setup(void);
