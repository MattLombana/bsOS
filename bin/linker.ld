/* The bootloader will look at the intry point, and start execution at the designated symbol
 */
ENTRY(_start)

/* Specify where each section of the object files will be but in the final kernel image
 */
SECTIONS
{
    /* Begin putting sections at 1 MiB.
     * This is a conventional place for kernels to be loaded into by the bootloader
     */
    . = 1M;

    /* Put the multiboot header first, as its required to be early in the image.
     * If it is not put within the first 8 KiB, the bootloader will not find it.
     * Afterwards, put in the text section.
     */
    .text BLOCK(4K) : ALIGN(4K)
    {
        *(.multiboot)
        *(.text)
    }

    /* Read-Only Data
     */
    .rodata BLOCK(4K) : ALIGN(4K)
    {
        *(.rodata)
    }

    /* Read-Write Data.
     * This data is initialized.
     */
    .data BLOCK(4K) : ALIGN(4K)
    {
        *(.data)
    }

    /* Read-Write Data.
     * This data is uninitialized, and contains the stack and heap.
     */
    .bss BLOCK(4K) : ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
    }

    /* The compiler may produce othe sections. By default, it will put them in a segment with the
     * same name.
     * To add more segments, add stuff here as needed.
     */
}
