TARGETS =					\
		  string/memcmp 	\
		  string/memcpy	\
		  string/memmove	\
		  string/memset 	\
		  string/strlen

LIBS = 				\
	   libk.a		\

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

AR = ar


DESTDIR = ../bin
OBJDIR  = $(DESTDIR)/obj
LIBDIR = $(DESTDIR)/lib
INCLUDEDIR = $(DESTDIR)/include

OBJS = $(addsuffix .o, $(TARGETS))
_LIBK_OBJS = $(OBJS:.o=.libk.o)
LIBK_OBJS = $(addprefix $(OBJDIR)/, $(_LIBK_OBJS))


.PHONY: all clean install-headers help
.SUFFIXES: .c .o .asm .asm.o .libk.o
default: all

help:
	@printf "Custom bsOS/libc/ Makefile Targets:\n"
	@printf "make                 : Install headers, build libk\n"
	@printf "make install-headers : Install headers into bin/include/ \n"
	@printf "make libk.a          : Create the static libk.a library in bin/lib/\n"
	@printf "make clean           : Run Make clean to remove the libk.a and object files from compilation\n"
	@printf "make help            : Display this help message\n"


all: install-headers $(LIBS)

install-headers:
	mkdir -p $(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(INCLUDEDIR)

libk.a: $(LIBK_OBJS)
	$(AR) rcs $(LIBDIR)/$@ $(addprefix $(OBJDIR)/, $(notdir $(LIBK_OBJS)))

$(OBJDIR)/%.libk.o: %.c
	$(CC) $(CFLAGS) $< -o $(OBJDIR)/$(notdir $@)

clean:
	rm -f $(addprefix $(OBJDIR)/, $(notdir $(LIBK_OBJS)))
	rm -f $(addprefix $(LIBDIR)/, $(LIBS))


