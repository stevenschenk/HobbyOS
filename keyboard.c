#include <keyboard.h>
#include <io.h>
#include <scancodes.h>
#include <console.h>

unsigned char getchar(unsigned char c)
{
	return asciiNonShift[c];
}

string readString() {
	string buffstring = NULL;
	uint8_t index = 0;

	while(1) {
		if(inb(0x64) & 0x1) {
			char code = inb(0x60);
			if(code & 0x80) continue;
			if(code == 0x1c) break;
			char c = getchar(code);
			buffstring[index++] = c;
			terminal_write_char(c);
		}
	}
	buffstring[index] = '\0';
	return buffstring;
}