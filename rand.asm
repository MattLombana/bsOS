global _timestamp_edx
global _timestamp_eax

section .text
    _timestamp_edx:
        rdtsc
        mov eax, edx
        ret

    _timestamp_eax:
        rdtsc
        ret
