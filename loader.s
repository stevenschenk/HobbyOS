extern kernel_main

ALIGNMENT	equ 1<<0
MEMINFO 	equ 1<<1
FLAGS		equ ALIGNMENT | MEMINFO
MAGIC		equ 0x1BADB002
CHECKSUM	equ -(MAGIC + FLAGS)

section .text
global _start
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

KERNEL_STACK_SIZE equ 0x1000 ;4KiB

section .bss
align 4
kernel_stack:
	resb KERNEL_STACK_SIZE

section .text
_start:
	mov esp, kernel_stack + KERNEL_STACK_SIZE ;x86 stacks points at end
	call kernel_main
	
loop:	
	jmp loop
