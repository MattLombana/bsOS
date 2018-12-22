#include "screen.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "string.h"

#define DEFAULT_FG COLOR_WHITE
#define DEFAULT_BG COLOR_BLACK

static const size_t SCREEN_WIDTH = 80;
static const size_t SCREEN_HEIGHT = 25;
uint16_t* terminal_buffer;
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;

static inline uint8_t vga_entry_color(enum screen_color foreground, enum screen_color background) {
    return foreground | (background << 4);
}

static inline uint16_t vga_entry(unsigned char c, uint8_t color) {
    return (uint16_t) c | ((uint8_t) color << 8);
}

void terminal_put_char_at(char c, uint16_t color, size_t x, size_t y) {
    const size_t index = y * SCREEN_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}

void terminal_scroll_up() {
    int i;
    for (i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT - SCREEN_WIDTH; i++) {
        terminal_buffer[i] = terminal_buffer[i + SCREEN_WIDTH];
    }
    for (i = 0; i < SCREEN_WIDTH; i++) {
        terminal_buffer[(SCREEN_HEIGHT - 1) * SCREEN_WIDTH + i] = vga_entry(' ', terminal_color);
    }
}

void terminal_put_char(char c) {
    if (++terminal_column == SCREEN_WIDTH || c == '\n') {
        terminal_column = 0;
        if (terminal_row == SCREEN_HEIGHT - 1) {
            terminal_scroll_up();
        } else {
            terminal_row++;
        }
    }
    if (c == '\n') {
        return;
    }
    terminal_put_char_at(c, terminal_color, terminal_column, terminal_row);
}

void terminal_write(const char *data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        terminal_put_char(data[i]);
    }
}

void terminal_write_string(const char *data) {
    terminal_write(data, strlen(data));
}

void terminal_write_string_color(const char *data, enum screen_color fg, enum screen_color bg) {
    uint8_t old_color = terminal_color;
    terminal_color = vga_entry_color(fg, bg);
    terminal_write_string(data);
    terminal_color = old_color;
}

void terminal_write_int(unsigned long n) {
    if (n / 10) {
        terminal_write_int(n / 10);
    }
    terminal_put_char((n % 10) + '0');
}


void terminal_clear() {
    for (size_t y = 0; y < SCREEN_HEIGHT; y++) {
        for (size_t x = 0; x < SCREEN_WIDTH; x++) {
            terminal_put_char_at(' ', terminal_color, x, y);
        }
    }
}

void terminal_set_color(enum screen_color fg, enum screen_color bg) {
	terminal_color = vga_entry_color(fg, bg);
}

void terminal_initialize() {
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(DEFAULT_FG, DEFAULT_BG);
    terminal_buffer = (uint16_t *) 0xB8000;
    for (size_t y = 0; y < SCREEN_HEIGHT; y++) {
        for (size_t x = 0; x < SCREEN_WIDTH; x++) {
            terminal_put_char_at(' ', terminal_color, x, y);
        }
    }

    terminal_write_string("\n\n\n\n                            ");
    terminal_write_string_color("Welcome to bsOS\n", COLOR_WHITE, COLOR_LIGHT_BLUE);
    terminal_write_string("\n\n\n\n\n\n\n\n\n                               ");
    terminal_write_string_color("Rand():", COLOR_BLACK, COLOR_WHITE);
    terminal_put_char(' ');
}

