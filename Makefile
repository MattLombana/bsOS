SOURCE = kernel screen rand string paging
ASM    = boot paging rand
_OBJ    =					\
		boot.asm.o			\
		paging.asm.o		\
		rand.asm.o			\
		kernel.o			\
		screen.o			\
		rand.o				\
		string.o			\
		paging.o


#####################################################################################################
#                                                                                                   #
#                              Everything below here can safely be ignored                          #
#                                                                                                   #
#####################################################################################################
CC     = i686-elf-gcc
AC     = nasm
LINKER = linker.ld
AFLAGS = -felf32
CFLAGS = -std=gnu99 -ffreestanding -Wall -Wextra -c
LFLAGS = -ffreestanding -nostdlib -lgcc

TARGET = ./bin/isodir/boot/bsOS.bin
ISO    = ./bin/bsOS.iso
ISODIR = ./bin/isodir
ODIR   = ./bin/obj
OBJ    = $(patsubst %,$(ODIR)/%,$(_OBJ))

# The target that is built when you run `make` with no arguments:
default: all


# Create object files for the assembly
$(ODIR)/%.asm.o: %.asm
	$(AC) $(AFLAGS) $< -o $@

# Create object files for the C code
$(ODIR)/%.o: %.c
	$(CC) $(CFLAGS) $< -o $@


# Make all files described in TARGET
all: $(OBJ)
	$(CC) $(LFLAGS) -T $(LINKER) -o $(TARGET) $^
	grub-mkrescue -o $(ISO) $(ISODIR)


# running `make clean` will remove all files ignored by git
clean:
	rm -f $(OBJ) $(TARGET) $(ISO)


.SUFFIXES:
.PHONY: default all clean
