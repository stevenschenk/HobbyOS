extern kernel_main

ALIGNMENT	equ 1<<0			; Set alignment to flag to true
MEMINFO 	equ 1<<1			; Set Meminfo flag to true
FLAGS		equ ALIGNMENT | MEMINFO		; Compute flag
MAGIC		equ 0x1BADB002			; Magic number for the bootloader
CHECKSUM	equ -(MAGIC + FLAGS)		; CHECKSUM + MAGIC + FLAGS = 0

; Write the multiboot header in memory
section .text
global _start
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

KERNEL_STACK_SIZE equ 0x1000 ; Stack size of 4KiB

; Reserve bytes for the stack
section .bss
align 4
kernel_stack:
	resb KERNEL_STACK_SIZE

section .text
_start:
	mov esp, kernel_stack + KERNEL_STACK_SIZE 	; Set the stack pointer to the bottom 
							; of the stack, since x86 is bottom
							; to top.
	call kernel_main				
	
loop:							
	jmp loop
