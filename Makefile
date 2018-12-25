.PHONY: all clean libc kernel binary iso install-headers help
default: all


help:
	@printf "Custom bsOS Makefile Targets:\n"
	@printf "make                 : Install build libk and the kernel, and create the resulting iso\n"
	@printf "make install-headers : Install headers into bin/include/ \n"
	@printf "make libc            : Install libc headers and build libk.a \n"
	@printf "make kernel          : Install kernel headers and build the kernel object files\n"
	@printf "make binary          : Build the kernel binary \n"
	@printf "make iso             : Build an iso image from the kernel \n"
	@printf "make clean           : Run Make clean for both the libc and kernel directory\n"
	@printf "make help            : Display this help message\n"

all: libc iso

install-headers:
	$(MAKE) -C kernel install-headers
	$(MAKE) -C libc install-headers

libc:
	$(MAKE) -C libc

kernel:
	$(MAKE) -C kernel

binary: kernel
	$(MAKE) -C kernel binary

iso: $(BINARY)
	$(MAKE) -C kernel iso

clean:
	$(MAKE) -C libc clean
	$(MAKE) -C kernel clean
