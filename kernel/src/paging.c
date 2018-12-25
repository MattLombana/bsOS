#include <stdint.h>
#include <kernel/paging.h>

extern void _loadPageDirectory(uint32_t*);
extern void _enablePaging();

/* Create the blank page directory.
 * It is blank because no page tables have been created, where entries in the page directory can
 *  point.
 * Note, all paging structures need to be page-aligned, (multiple of 4096).
 *  Finding the first free page-aligned addres after the kernel will be fine, but a page frame
 *  allocator should be written ASAP. Another temporary solution is to declare global objects
 *  with __attribute__((align(4096))). This is a GCC extension, so it might not work with all
 *  compilers.
 */
uint32_t page_directory[1024] __attribute__((aligned(4096)));

/* Create the  blank page table.
 * It is blank because no pages have been created, where entries in the page table can point.
 */
uint32_t first_page_table[1024] __attribute__((aligned(4096)));


/* Initally setup all paging requirements, by filling the page directory and first page table.
 */
void setup_paging() {
    uint32_t i;
    for(i = 0; i < 1024; i++) {
        // Set the following flags to the pages:
        //  Supervisor: Only kernel-mode can access them
        //  Write Enabled: It can be read and written to
        //  Not Present: The page table is not present
        page_directory[i] = 0x00000002;
    }


    // holds the physical address where we want to start mapping these pages to.
    // In this case, we want to map theese pages to the beginning of memory.
    // We will fill all 1024 entries in the table, mapping 4 megabytes
    for (i = 0; i < 1024; i++) {
        // As the address is page aligned, it will always leafve 12 bits zeroed.
        // Those bits are used by the attributes: supervisor level, read/write, present
        first_page_table[i] = (i * 0x1000) | 3;
    }

    // Put the page table in the page directory with attributes: supervisor level, read/write, present
    page_directory[0] = (uint32_t)first_page_table | 3;

    // Load the page directory into processor registers
    _loadPageDirectory(page_directory);
    _enablePaging();
}
