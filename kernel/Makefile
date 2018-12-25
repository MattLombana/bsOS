TARGETS =				\
		  kernel.c		\
		  paging.c		\
		  rand.c		\
		  tty.c			\
		  boot.asm		\
		  paging.asm	\
		  rand.asm		\

_LIBS = 				\
	   libk.a			\

#####################################################################################################
#                                                                                                   #
#                              Everything below here can safely be ignored                          #
#                                                                                                   #
#####################################################################################################
ACC          = nasm
ACFLAGS      = -felf32
DEFAULT_ARCH = i386
ARCHDIR      = arch/$(DEFAULT_ARCH)

CC         = i686-elf-gcc
CFLAGS     = -std=gnu99 -ffreestanding -Wall -Wextra -c -I$(INCLUDEDIR)
SRCDIR     = src

DESTDIR = ../bin
OBJDIR  = $(DESTDIR)/obj

INCLUDEDIR = $(DESTDIR)/include

LIBDIR = $(DESTDIR)/lib
LIBS = $(addprefix $(LIBDIR)/, $(_LIBS))

LINKER = $(DESTDIR)/linker.ld
LFLAGS = -ffreestanding -nostdlib -lgcc

ISO    = $(DESTDIR)/bsOS.iso
ISODIR = $(DESTDIR)/isodir
BINARY = $(DESTDIR)/isodir/boot/bsOS.bin


_OBJS = $(patsubst %.c, $(OBJDIR)/%.o, $(TARGETS))
OBJS  = $(patsubst %.asm,$(OBJDIR)/%.asm.o,$(_OBJS))

.PHONY: all clean install-headers binary iso kernel help
.SUFFIXES: .c .o .asm .asm.o
default: all

help:
	@printf "Custom bsOS/kernel/ Makefile Targets:\n"
	@printf "make                 : Build the kernel, binary, and ISO\n"
	@printf "make install-headers : Install headers into bin/include/ \n"
	@printf "make kernel          : Build the kernel object files in bin/obj/ \n"
	@printf "make binary          : Build the binary and save it as bin/isodir/boot/bsOS.bin \n"
	@printf "make iso             : Build the ISO file and save it as bin/bsOS.iso \n"
	@printf "make clean           : Run Make clean to remove the libk.a and object files from compilation\n"
	@printf "make help            : Display this help message\n"

all: kernel binary iso

install-headers:
	mkdir -p $(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(INCLUDEDIR)

kernel: $(OBJS)

$(OBJDIR)/%.asm.o: $(ARCHDIR)/%.asm
	$(ACC) $(ACFLAGS) $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $< -o $@


binary: $(OBJS)
	$(CC) $(LFLAGS) -T $(LINKER) -o $(BINARY) $^ $(LIBS)

$(BINARY): binary

iso: $(BINARY)
	grub-mkrescue -o $(ISO) $(ISODIR)

clean:
	rm -f $(OBJS) $(BINARY) $(ISO)
