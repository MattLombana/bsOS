#include "heap.h"
#include <stdbool.h> // TODO: Needed?
#include <stddef.h> // TODO: Needed?
#include <stdint.h> // TODO: Needed?

#define ALIGNMENT 4
#define ADD_BYTES(base_addr, num_bytes) (((char *)(base_addr)) + (num_bytes))

/* Simple heap implementation. All values are 4 byte aligned for simplicity.
 *
 *
 * Usage:
 *
 * heap_t bheap;
 * char *ptr;
 *
 * bheap_initialize(&bheap, <mem start, get from boot.asm, maybe 1MB>, heap size<1MB>)
 * ptr = bheap_alloc(size)
 * bheap_free(ptr)
 */

typedef struct block_header_p block_header_p;
struct block_header_p {
    block_header_p *previous;
    block_header_p *next;
    uint32_t free;
};

typedef struct _heap_header_t {
    uint32_t max_size;
    uint32_t curr_size;
    block_header_p *next_free;
} heap_header_t;

int bheap_init(void *heap_ptr, uintptr_t addr, uint32_t heap_size) {
    // Force the heap pointer to be 4-byte aligned
    int heap_alignment_offset = 0;
    if ((uint64_t)addr % ALIGNMENT != 0) {
        heap_alignment_offset = (ALIGNMENT - ((uint64_t)addr % ALIGNMENT));
    }

    heap_ptr = ADD_BYTES(heap_ptr, heap_alignment_offset);

    // Define the minimum size to be the smallest 8-byte aligned overhead size, and fail if a heap
    //  too small will be created. (ie. heap size is 12 bytes, and the heap header is 16 bytes)
    int min_size = sizeof(heap_header_t);
    if (min_size % ALIGNMENT != 0) {
        min_size += ALIGNMENT - (min_size % ALIGNMENT);
    }
    if (heap_size < min_size) {
        return -1;
    }

    // Actually begin the body of init
    heap_header_t *heap = (heap_header_t *)heap_ptr;
    // Set the max size to be the heap size, excluding any kind of realignment
    heap->max_size = heap_size - heap_alignment_offset;
    heap->curr_size = min_size;

    // Create the initial block
    block_header_p *init_block = (block_header_p *)((char *)heap_ptr + heap->curr_size);

    if ((uint64_t)init_block % ALIGNMENT != 0) {
        int init_block_offset = ALIGNMENT - (uint64_t)init_block % ALIGNMENT;
        init_block += init_block_offset; // TODO: Make sure this is only adding x bytes, not 4x bytes for every offset
    }
    heap->next_free = init_block;
    init_block->previous = NULL;
    init_block->next = NULL;
    init_block->free = 1;

    return 0;
}
