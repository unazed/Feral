export CC   = clang
export LD   = ld.lld
export ASM  = nasm
export MAKE = bmake

export ARCH = x86_64

export TRIPLE = $(ARCH)-unknown-none-gnu

##I'm really bad at makefiles. Fix this later.
OBJS = 		bootstrap.o	\
		##kernel.so	\
		##x86-64.o	\
		##libnyx.a	\
		##libthreads.a	\
		
GOAL = vmwildnyz

export BUILD_DIR = $(shell readlink -f build/)

all:
	##$(MAKE) libnyx/
	##$(MAKE) libthreads/
	mkdir -p build/
	cd arch/$(ARCH)/ && $(MAKE) 

clean:
	rm -rf build/

	
	
