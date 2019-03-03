//
//  kernel debugging facilities
//  
//  SPDX-License-Identifier: GPL-2.0-only
//  Copyright (C) 2018, angel
//

#pragma once

#include <core/types.h>
#include <core/io.h>

/**
 * @brief      initializes early debug facilities
 */
void debug_init_early(void);

/**
 * @brief      prints a formatted string to the kernel console
 *
 * @param[in]  fmt        format string
 * @param[in]  <unnamed>  format parameters
 */
void kprintf(const char *fmt, ...);
