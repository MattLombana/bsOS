#include "string.h"

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
