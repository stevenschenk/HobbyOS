#include <console.h>
#include <string.h>

/*
 *  Output on screen is done via Memory Mapped I/O.
 *  This means you can write directly to the address,
 *  which saves a lot of CPU cycles. Starting address
 *  of the Color Text Mode is at 0xB8000. A "Character"
 *  takes 2 bytes. 1 byte for the ASCII code and 1 byte
 *  for the attribute (color).
 *
 *  Example: "hi" with backgroud color black and 
 *           foreground color light gray
 *
 *      0xB8000 : 0x48 (ASCII 72 => 'h')
 *      0xB8001 : 0x07 (colorcode)
 *      0xB8002 : 0x49 (ASCII 73 => 'i')
 *      0xB8003 : 0x07 (colorcode)
 *
 *  The Color Text Mode buffer is 32 kB. However
 *  the terminal supports 25 rows with each 80 columns,
 *  so a maximum of 2000 characters is supported on a 
 *  single terminal page. Since the buffer is 32 kB, 
 *  it is possible to have at most 8 pages in memory.
 *
 *  2000 * 2 = 4kB per page 
 *
 */

size_t terminal_row;            /* Current row index */
size_t terminal_column;         /* Current column index */
uint8_t terminal_color;         /* Color of the terminal fg + bg */
uint8_t* terminal_buffer;       /* Pointer to the first address of the video memory */

// size_t strlen(const char* str) {
// 	size_t len = 0;
// 	while (str[len])
// 		len++;
// 	return len;
// }

void terminal_clear() {
    terminal_row = 0;
    terminal_column = 0;
    for(uint16_t x = 0; x < TERMINAL_WIDTH * TERMINAL_HEIGHT * 2; x++) {
        terminal_buffer[x] = ' ';
        terminal_buffer[++x] = TERMINAL_DEFAULT_COLOR; 
    }
}

void terminal_initialize() {
    terminal_color = TERMINAL_DEFAULT_COLOR;
    terminal_buffer = (uint8_t*) 0xB8000;
    terminal_clear();
}

void terminal_set_color(enum vga_color fg, enum vga_color bg) {
    terminal_color = fg | bg << 4;
}

void terminal_write_char(char c) {
    if(c == '\n'){
        terminal_row++;
        terminal_column = 0;
    } else {
        terminal_write_char_at(c, terminal_row, terminal_column++);
    }

    if(terminal_column > TERMINAL_WIDTH) {
        terminal_row++;
        terminal_column = 0;
    }
}

void terminal_write_char_at(char c, uint8_t terminal_row, uint8_t terminal_column) {
    uint16_t index = (terminal_row * TERMINAL_WIDTH * 2) + (terminal_column * 2);
    terminal_buffer[index] = c;
    terminal_buffer[++index] = terminal_color;
}

void terminal_write_string(char * text) {
    size_t len = strlen(text);
    for(uint16_t i = 0; i < len; i++)
        terminal_write_char(text[i]);
}