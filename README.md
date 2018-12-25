# bsOS: The Big Slow Operating System

This is an operating system designed at teaching me the basics of creating an operating system. It is
highly influenced by the [OSDev Wiki](https://wiki.osdev.org/Expanded_Main_Page).

## Building bsOS
I recommend building bsOS on a clean install of Ubuntu 18.04, as this is what I'm using to develop it.
1. First, you need to set up the cross compiler:
```bash
sudo apt-get install build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo libcloog-isl-dev libisl-dev qemu grub-common xorriso nasm grub-pc-bin
export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"
mkdir ~/src
cd ~/src
wget https://ftp.gnu.org/gnu/binutils/binutils-2.31.1.tar.xz
tar -xf binutils-2.31.1.tar.xz
rm binutils-2.31.1.tar.xz
mkdir build-binutils
cd build-binutils/
../binutils-2.31.1/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make
make install
cd ~/src
wget https://ftp.gnu.org/gnu/gcc/gcc-8.2.0/gcc-8.2.0.tar.xz
tar -xf gcc-8.2.0.tar.xz
rm gcc-8.2.0.tar.xz
mkdir build-gcc
cd build-gcc
../gcc-8.2.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc
```
2. Next, you need to add this to your ~/.bashrc:
```bash
export PATH=$HOME/opt/cross/bin:$PATH
```


3. Clone this repository:
```bash
git clone https://github.com/mattlombana/bsOS.git
```

4. Built it:
```bash
cd bsOS
make libc
make iso
```

5. Run bsOS:
```bash
cd bin/
qemu-system-i386 -cdrom bsOS.iso
```


