/*
 * Generic Printing Library
 */

enum screen_color {
    COLOR_BLACK,
    COLOR_BLUE,
    COLOR_GREEN,
    COLOR_CYAN,
    COLOR_RED,
    COLOR_MAGENTA,
    COLOR_BROWN,
    COLOR_LIGHT_GREY,
    COLOR_DARK_GREY,
    COLOR_LIGHT_BLUE,
    COLOR_LIGHT_GREEN,
    COLOR_LIGHT_CYAN,
    COLOR_LIGHT_RED,
    COLOR_LIGHT_MAGENTA,
    COLOR_LIGHT_BROWN,
    COLOR_WHITE,
};


void terminal_initialize();
void terminal_write_int(unsigned long);
void terminal_write_string(const char*);
void terminal_write_string_color(const char*, enum screen_color, enum screen_color);
void terminal_clear();
void terminal_set_color(enum screen_color, enum screen_color);
