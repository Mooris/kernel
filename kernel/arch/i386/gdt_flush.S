	.section .text
	.global gdt_flush    # Allows the C code to link to this
	.extern gp           # Says that _gp is in another file

gdt_flush:
	lgdt gp(,1)
	movw $0x10,%ax    # 0x10 is the offset in the GDT to our data segment
	movw %ax,%ds
	movw %ax,%es
	movw %ax,%fs
	movw %ax,%gs
	movw %ax,%ss
	ljmp $0x08, $flush2   # 0x08 is the offset to our code segment: Far jump!

flush2:
	ret               # Returns back to the C code!
	
