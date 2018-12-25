#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "paging.h"
#include "tty.h"
#include "rand.h"



void delay(int t) {
    volatile int i,j;
    for (i = 0; i < t; i++) {
        for (j = 0; j < 250000; j++) {
            __asm__("NOP");
        }
    }
}



void kernel_main() {
    setup_paging();
    terminal_initialize();
    rand_initialize();

    delay(200);
    terminal_write_string("This is a test");
    for (;;) {
        terminal_write_int(rand());
        terminal_write_string(" ");
        delay(100);
    }
}
