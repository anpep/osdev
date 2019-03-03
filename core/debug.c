//
//  kernel debugging facilities
//  
//  SPDX-License-Identifier: GPL-2.0-only
//  Copyright (C) 2018, angel
//

#include <core/types.h>
#include <core/io.h>

static uint16_t g_io_port = 0;

/**
 * @brief      obtains the string representation of the given value
 *
 * @param      dest      destination buffer
 * @param[in]  spec      base specifier ('d', 'u', 'x')
 * @param[in]  val       value to be converted
 * @param[in]  dest_len  maximum length of the destination buffer
 */
static void
_vtosz(char *dest,
       char spec,
       unsigned int val,
       uintmax_t dest_len)
{
  if (dest_len < 2)
  {
    return;
  }

  char *head = dest;
  unsigned int abs = val;
  int div = 10;

  // if specified is signed put - in the head for negative values
  if (spec == 'd' && (signed) val < 0)
  {
    *dest++ = '-';
    dest_len--;
    head++;
    abs = -val;
  }
  else if (spec == 'x')
  {
    div = 16;
  }

  do
  {
    int rem = abs % div;
    *dest++ = rem < 10 ? '0' + rem : 'a' + rem - 10;
    if (!--dest_len)
    {
      goto reverse;
    }
  }
  while (abs /= div);

reverse:
  *dest = 0;
  dest--;
  while (head < dest)
  {
    char tmp = *head;
    *head = *dest;
    *dest = tmp;
    head++;
    dest--;
  }
}

void
debug_init_early(void)
{
  // HACK: using bochs debug port
  g_io_port = 0xe9;
}

void
kprintf(const char *fmt, ...)
{
  void **args = (void **) &fmt;
  args++;

  for (; *fmt; fmt++)
  {
    if (*fmt != '%')
    {
      outb(*fmt, g_io_port);
      continue;
    }

    switch (*++fmt)
    {
      case 'c':
        outb(*((const char *) *args++), g_io_port);
        break;

      case 's':
      {
        char *s = (char *) *args++;
        if (!s)
        {
          s = "(null)";
        }

        while (*s)
        {
          outb(*s++, g_io_port);
        }

        break;
      }

      case 'd':
      case 'u':
      case 'x':
      {
        char vbuf[12];
        char *ptr = vbuf;
        _vtosz(vbuf, *fmt, (int) *args++, sizeof(vbuf) - 1);
        while (*ptr)
        {
          outb(*ptr++, g_io_port);
        }
        break;
      }

      default:
        outb(*fmt, g_io_port);
        break;
    }
  }
}
