#include "string.h"

void *memcpy(void *destptr, const void *srcptr, size_t size) {
    unsigned char *dest = (unsigned char *)destptr;
    unsigned char *src = (unsigned char *)srcptr;
    for (size_t i = 0; i < size; i++) {
        dest[i] = src[i];
    }
    return destptr;
}
