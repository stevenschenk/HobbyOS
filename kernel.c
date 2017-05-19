#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>
#include <scancodes.h>
#include <console.h>

/* Check if the compiler thinks we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
#error "This OS needs to be compiled with a ix86-elf compiler"
#endif

//TODO: Put this in a seperate file, since 
// 		more files might need these functions.

static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}

static inline void outb(uint16_t port, uint8_t val)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

unsigned char getchar(unsigned char c)
{
	return asciiNonShift[c];
}

/////////////////////////////////////////////////

// Test code for keyboard input
void getScancode()
{
		unsigned char scancode;

		scancode = inb(0x60);

		if(scancode & 0x80) {

		} else {
			terminal_write_char(getchar(scancode));
		}

	// do {
	// 	if(inb(0x60)!=c) {	
	// 		c=inb(0x60);
	// 		if(c>0)
	// 			return c;
	// 	}
	// }while(1);
}



void kernel_main(void) {

	terminal_initialize();
	
	// while(1) {
		getScancode();
	// }	
}
