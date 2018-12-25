MBALIGN equ 1                       ; Align loaded modules on page boundaries
MEMINFO equ 2                       ; Provide the memory map
FLAGS equ MBALIGN | MEMINFO         ; Set the multiboot flag field
MAGIC equ 0x1BADB002                ; Tell the bootloader where the header is
CHECKSUM equ -(MAGIC + FLAGS)       ; Checksum to guarantee we are multibootable


; Declare a multiboot section, to mark the program as a kernel.
; These values are documented in the multibook standard. The bootloader will search for this
;  signature in the first 8 KiB of the kernel file. This must be 4-byte aligned.
; The signature is in its own section so the header can be forced within the first 8 KiB
section .multiboot
    align 4         ; 4 byte align the multiboot section
    dd MAGIC        ; Define a double word for the Magic number
    dd FLAGS        ; Define a double word for the Flags
    dd CHECKSUM     ; Define a double word for the checksum


; The multiboot standard doesn't specify the value of the extended stack pointer (esp) register
;  and its up to the kernel to provide a stack. This reserves 16 KiB for the stack, by creating a
;  symbol for it at the bottom and top (stack_bottom and stack_top)
; The stack will grow downwards, and is in its own section so it can be marked nobits. This means
;  the kernel file is smaller because it doesn't contain an uninitialized stack. The stack must be
;  16 byte aligned according to System V ABI and convention. The compiler will assume that the
;  stack is 16-byte aligned, with undefined behavior if this is not the case.
section .bss
    align 16            ; 16-byte align the stack
    stack_bottom:       ; Create a symbol for the stack bottom
    resb 16384          ; Reserve 16 KiB for the stack
    stack_top:          ; Create a symbol for the stack top


; The linker script specifies _start as the entry point to a program, and the bootloader will
;  jump to this point after loading the kernel.
; There is no reason to return from this function, as the bootloader won't exist any more
section .text

    ; Declare _start as a function symbol with the given function size
    ; We can find the size by subtracting the starting address from the ending address of _start
    global _start:function (_start.end - _start)

    ; The bootloader will load us into 32-bit protected mode on x86 machines.
    ; Interrupts and Paging will be disabled.
    ; The processor state will be defined in the multiboot standard, the Kernel has full
    ;  control of the CPU, and will only be able to use hardware features and code that it
    ;  defines itself.
    _start:
        ; Set up the esp register to point to the top of the stack (since it grows down in memory)
        ; This is necessarily done in assembly, as C requres a stack to function
        mov esp, stack_top

        ; Initialize a necessary processor state before the high level kernel code is called. It's
        ;  best to minimize the early environment when crucial features are not yet available.
        ; Note: the processor is not fully initialized yet, features such as floating point
        ;  instructions and instruction set extensions are not initialized
        ; The GDT and Paging should be loaded and enabled (respectively) here.
        ; C++ features such as global constructors and exceptions will require runtime support
        ;  to work as well.
        ; Note: if you're building on Windows, C functions may have an underscore prefix in assembly
        ;  meaning in should be `extern _kernel_main`
        extern kernel_main

        ; Enter the high-level kernel.
        ; The ABI requires the stack is 16-byte aligned at the time of the call instruction,
        ;  before it pushes the return pointer (which is 4-byte aligned)
        ; We guarantee the stack is still 16-byte aligned with this logic:
        ;  The stack was originally 16-byte aligned in the .bss section
        ;  We pushed the stack top to the stack, and the stack top is a multiple of 16 bytes
        ;  We have pushed 0 bytes to the stack before, so (0 + c*16) is still divisible by 16
        ; Note: if you're building on Windows, C functions may have an underscore prefix in assembly
        ;  meaning in should be `call _kernel_main`
        call kernel_main

        ; If the system ever returns from kernel_main, it should go to an infinite loop
        ; To do so:
        ;  1. Disable interrupts with cli (clear interrupt enable in eflags)
        ;     They are already disabled by the bootloader, so this shouldn't be needed, but
        ;      if you enable inerrupts and return from kernel_main they will need to be disabled
        ;  2. Wait for the next interrupt to arrive with hlt (halt instruction)
        ;     Because instructions are disabled, this should lock the execution of the OS
        ;  3. Jump to the hlt instruction if the system ever wakes up.
        ;     This should only happen if a non-maskable interrupt occurs, or system management mode
        ;      executes
        cli             ; Disable interrupts
        .hang: hlt      ; Halt until an interrupt occurs
        jmp .hang       ; Go back to halting
    .end:       ; Label used to find the end of _start

