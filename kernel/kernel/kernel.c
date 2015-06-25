#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>

void kernel_early(void)
{
  terminal_initialize();
  gdt_initialize();
  idt_initialize();
}

void kernel_main(void)
{
  puts("0");
  puts("1");
  puts("2");
  puts("3");
  puts("4");
  puts("5");
  puts("6");
  puts("7");
  puts("8");
  puts("9");
  puts("10");
  puts("11");
  puts("12");
  puts("13");
  puts("14");
  puts("15");
  puts("16");
  puts("17");
  puts("18");
  puts("19");
  puts("20");
  puts("21");
  puts("22");
  puts("23");
  puts("24");
  puts("25");
}
