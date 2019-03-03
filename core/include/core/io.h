//
//  x86 I/O functions
//  
//  SPDX-License-Identifier: GPL-2.0-only
//  Copyright (C) 2018, angel
//

#pragma once

#include <core/types.h>

/**
 * @brief      reads a byte from the specified port
 *
 * @param[in]  port  port address
 *
 * @return     the value read from the port
 */
inline uint8_t inb(uint16_t port) __attribute__((always_inline));
inline uint8_t
inb(uint16_t port)
{
  uint8_t val;
  __asm__("inb %%1, %%0"
          : "=a"(val)
          : "dN"(port));
  return val;
}

/**
 * @brief      writes a byte to the specified port
 *
 * @param[in]  val   value to be written
 * @param[in]  port  port address
 */
inline void outb(uint8_t val, uint16_t port) __attribute__((always_inline));
inline void
outb(uint8_t val, uint16_t port)
{
  __asm__ volatile("outb %1, %0"
                   :
                   : "a"(val), "dN"(port));
}

/**
 * @brief      reads a word from the specified port
 *
 * @param[in]  port  port address
 *
 * @return     the value read from the port
 */
inline uint16_t inw(uint16_t port) __attribute__((always_inline));
inline uint16_t
inw(uint16_t port)
{
  uint16_t val;
  __asm__("inw %%1, %%0"
          : "=a"(val)
          : "dN"(port));
  return val;
}

/**
 * @brief      writes a word to the specified port
 *
 * @param[in]  val   value to be written
 * @param[in]  port  port address
 */
inline void outw(uint16_t val, uint16_t port) __attribute__((always_inline));
inline void
outw(uint16_t val, uint16_t port)
{
  __asm__ volatile("outw %1, %0"
                   :
                   : "a"(val), "dN"(port));
}

/**
 * @brief      reads a double word from the specified port
 *
 * @param[in]  port  port address
 *
 * @return     the value read from the port
 */
inline uint32_t inl(uint16_t port) __attribute__((always_inline));
inline uint32_t
inl(uint16_t port)
{
  uint32_t val;
  __asm__("inl %%1, %%0"
          : "=a"(val)
          : "dN"(port));
  return val;
}

/**
 * @brief      writes a double word to the specified port
 *
 * @param[in]  val   value to be written
 * @param[in]  port  port address
 */
inline void outl(uint32_t val, uint16_t port) __attribute__((always_inline));
inline void
outl(uint32_t val, uint16_t port)
{
  __asm__ volatile("outl %1, %0"
                   :
                   : "a"(val), "dN"(port));
}
