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

void kerror(const char *estr) {
  puts(estr);
  for (;;);
}

void kernel_main(void)
{
  printf("Yolo\n");
  int i = 4 / 0;
  printf("%d\n", i);
  printf("Yolo");
}
