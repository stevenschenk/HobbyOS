#if !defined(__cplusplus)
#include <stdbool.h> 
#endif

#include <stddef.h>
#include <stdint.h>
#include <console.h>
#include <string.h>
#include <keyboard.h>

/* Check if the compiler thinks we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
#error "This OS needs to be compiled with a ix86-elf compiler"
#endif


void kernel_main(void) {

	terminal_initialize();
	terminal_write_string("Welcome to HobbyOS (version 1.0), how may I serve you?");
	
	while(1) {
		terminal_write_string("\nHobbyOS> ");

		string command = readString();

		if(strcmp(command, "clear")) {
			terminal_clear();
		} 
		else if(strcmp(command, "hello")) {
			terminal_write_string("\nHello there! I am ready for orders!");
		}
	}	
}
