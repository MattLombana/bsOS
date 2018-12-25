#include "rand.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define RAND_MAX 32767
unsigned long next = 1;
extern uint32_t _timestamp_edx();
extern uint32_t _timestamp_eax();

int rand() {
    next = next * 1103515245 + 12345;
    return (unsigned int)(next / 65536) % RAND_MAX + 1;
}

void srand(unsigned int seed) {
    next = seed;
}

void rand_initialize() {
    srand(_timestamp_eax());
}
