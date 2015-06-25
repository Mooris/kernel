#ifndef __KERNEL_H__
#define __KERNEL_H__

#include <stdint.h>
#include <stdio.h>

inline void kerror(const char *estr) __attribute__ ((noreturn));
inline void kerror(const char *estr)
{
  puts(estr);
  for (;;);
}

inline void outb(uint16_t port, uint8_t value) {
  asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

#endif 
