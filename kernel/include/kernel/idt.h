#ifndef __IDT_H__
#define __IDT_H__

void idt_initialize();
void idt_set_gate(unsigned char, unsigned long, unsigned short, unsigned char);

#endif
