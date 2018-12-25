AC           = nasm
AFLAGS       = -felf32
DEFAULT_ARCH = i686
ARCHDIR      = arch/$(DEFAULT_ARCH)

CC         = i686-elf-gcc
CFLAGS     = -std=gnu99 -ffreestanding -Wall -Wextra -c -I$(INCLUDEDIR)
SRCDIR     = src

DESTDIR = ../bin
OBJDIR  = $(DESTDIR)/obj

INCLUDEDIR = $(DESTDIR)/include

_SRC_OBJS =				\
		   kernel.o		\
		   paging.o		\
		   rand.o		\
		   tty.o
SRC_OBJS  = $(patsubst %,$(OBJDIR)/%,$(_SRC_OBJS))

_ARCH_OBJS =					\
			boot.asm.o		\
			paging.asm.o	\
			rand.asm.o		\
ARCH_OBJS  = $(patsubst %,$(OBJDIR)/%,$(_ARCH_OBJS))


OBJS =					\
	   $(ARCH_OBJS) 	\
	   $(SRC_OBJS)


.PHONY: all clean
.SUFFIXES: .c .o .asm

all: install-headers $(OBJS)

install-headers:
	mkdir -p $(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(INCLUDEDIR)

$(OBJDIR)/%.asm.o: $(ARCHDIR)/%.asm
	$(AC) $(AFLAGS) $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJS)
