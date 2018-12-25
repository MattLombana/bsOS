#include "string.h"

int memcmp(const void *aptr, const void *bptr, size_t size) {
    const unsigned char *a = (const unsigned char*)aptr;
    const unsigned char *b = (const unsigned char*)bptr;

    for (size_t i = 0; i < size; i++) {
        if (a[i] < b[i]) {
            return -1;
        } else if (b[i] < a[i]) {
            return 1;
        }
    }
    return 0;
}


void *memcpy(void *destptr, const void *srcptr, size_t size) {
    unsigned char *dest = (unsigned char *)destptr;
    unsigned char *src = (unsigned char *)srcptr;
    for (size_t i = 0; i < size; i++) {
        dest[i] = src[i];
    }
    return destptr;
}


void* memmove(void* destptr, const void* srcptr, size_t size) {
    unsigned char* dest = (unsigned char*)destptr;
    const unsigned char* src = (const unsigned char*)srcptr;
    if (dest < src) {
        // If the start of dest is before the start of source, the end of dest might overlap with
        //  the start of src. Therefore, we need to copy from the front to back
        for (size_t i = 0; i < size; i++) {
            dest[i] = src[i];
        }
    } else {
        // if the start of dest is after the start of source, then dest might overlap at the end, so
        //  we need to copy from the back to the front.
        for (size_t i = size; i != 0; i--) {
            dest[i-1] = src[i-1];
        }
    }
    return destptr;
}


void* memset(void* bufptr, int val, size_t size) {
    unsigned char* buf = (unsigned char*)bufptr;
    for (size_t i = 0; i < size; i++) {
        buf[i] = (unsigned char) val;
    }
    return bufptr;
}


size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len]) {
        len++;
    }
    return len;
}
