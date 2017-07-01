#ifndef CONSOLE
#define CONSOLE

#include <stddef.h>
#include <stdint.h>

#define TERMINAL_WIDTH 80
#define TERMINAL_HEIGHT 25
#define TERMINAL_DEFAULT_COLOR 0x07

/* Terminal Color Codes */
enum vga_color {
	VGA_COLOR_BLACK         =   0x0,
	VGA_COLOR_BLUE          =   0x1,
	VGA_COLOR_GREEN         =   0x2,
	VGA_COLOR_CYAN          =   0x3,
	VGA_COLOR_RED           =   0x4,
	VGA_COLOR_MAGENTA       =   0x5,
	VGA_COLOR_BROWN         =   0x6,
	VGA_COLOR_LIGHT_GREY    =   0x7,
	VGA_COLOR_DARK_GREY     =   0x8,
	VGA_COLOR_LIGHT_BLUE    =   0x9,
	VGA_COLOR_LIGHT_GREEN   =   0xA,
	VGA_COLOR_LIGHT_CYAN    =   0xB,
	VGA_COLOR_LIGHT_RED     =   0xC,
	VGA_COLOR_LIGHT_MAGENTA =   0xD,
	VGA_COLOR_LIGHT_BROWN   =   0xE,
	VGA_COLOR_WHITE         =   0xF,
};

extern void terminal_initialize();
extern void terminal_set_color(enum vga_color fg, enum vga_color bg);
extern void terminal_write_char(char c);
extern void terminal_write_char_at(char c, uint8_t terminal_row, uint8_t terminal_column);
extern void terminal_write_string(char * text);
extern void terminal_clear();
//TODO: Update cursor position (http://wiki.osdev.org/Text_Mode_Cursor)

#endif