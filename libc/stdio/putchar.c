#include "stdio.h"
#include <kernel/tty.h>

int putchar(int i) {
    char c = (char)i;
    terminal_write(&c, sizeof(c));
    return i;
}

