#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <kernel/paging.h>
#include <kernel/tty.h>
#include <kernel/rand.h>


/* Temporary delay function.
 *
 * Note: This is a very bad function, as it ties up the CPU while delaying. It is only in place
 * while we do not have multithreading or clock tick support
 */
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
