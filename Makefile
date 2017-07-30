export CC   = clang
export CXX  = clang++
export LD   = ld.lld
export ASM  = nasm
export MAKE = bmake

export ARCH = x86_64

export TRIPLE = $(ARCH)-unknown-none-gnu

export CSTD = -std=c11 -Wall -Werror -Wconversion	##Embed these here so we don't forget.

export ROOT = $(shell readlink -f .)

##Some thing we'll probably need to do is try to figure out how to force Aarch64 to be ONLY little-endian, without performance penalty checking all the time.

##Intentionally leave out the first '-I' so this looks natural.
export INCLUDE 				= $(ROOT)/include -I$(ROOT)/include/sdk
export INCLUDE_INTERNAL 		= $(ROOT)/krnl_internal
export INCLUDE_USERSPACE 		= $(ROOT)/include/userspace

##I'm really bad at makefiles. Fix this later.
OBJS = 		bootstrap.o	\
		##kernel.so	\
		##x86-64.o	\
		##libnyx.a	\
		##libthreads.a	\

#The kernel image		
GOAL           = floskrnl

# What Waypoint will boot with for now...
MULTIBOOT_GOAL = flbooter

# The ELF loader we boot from EFI firmware. This will be done when I get around to it.		
EFI_GOAL       = floskldr

export BUILD_DIR = $(shell readlink -f build/)

all:	make_build_dir
	##$(MAKE) libnyx/
	##$(MAKE) libthreads/
	cd arch/$(ARCH)/ && $(MAKE) 

clean:
	rm -rf build/

make_build_dir:
	mkdir -p build/
	
	
