## TODO: Rewrite this all with a Makefile.inc at the top level directory where possible.

include Makerules.inc

export MAKEROOT = $(shell readlink -f .)

QEMU_DISK_SIZE = 4294967296
QEMU = qemu-system-x86_64

TEST_FILE = disk.img

## Adjective + Animal.
CODENAME := Angry Aligator
RELEASE_CANIDATE := -rc-1000	##Negative 1000 since we're not even closed to finished.


##Some thing we'll probably need to do is try to figure out how to force Aarch64 to be ONLY little-endian, without performance penalty checking all the time.

##Intentionally leave out the first '-I' so this looks natural.
export INCLUDE 				= $(ROOT)/Include -I$(ROOT)/Include/sdk
export INCLUDE_INTERNAL 		= $(ROOT)/Include/krnl_internal
export INCLUDE_USERSPACE 		= $(ROOT)/Include/userspace


.PHONY:	OBJS GOAL all clean build_dir cleanall

##I'm really bad at makefiles. Fix this later.
OBJS = 		bootstrap.o	\
		##kernel.so	\
		##x86-64.o	\
		##libnyx.a	\
		##libthreads.a	\

#The kernel image. We need to stay OK for 8.3 because flash media.		
GOAL           = FERALKER.NEL

# These two stubs here no longer have a purpose, we boot with Multiboot 2.
# What Waypoint will boot with for now...
#MULTIBOOT_GOAL = flbooter

# The ELF loader we boot from EFI firmware. This will be done when I get around to it.		
#EFI_GOAL       = floskldr

export BUILD_DIR = $(shell readlink -f build/)

all:	make_build_dir
	##$(MAKE) libnyx/
	##$(MAKE) libthreads/
	##TODO: Point instead to /base/feral/hals/x86-64/halboot...
	cd base/hals/$(ARCH)/halboot && $(MAKE) 

clean:
	rm -rf build/

build_dir:
	mkdir -p build/

disk.img:
	qemu-img create -f raw $(TEST_FILE) $(QEMU_DISK_SIZE)
	sudo losetup /dev/loop0 $(TEST_FILE)
	
	echo "You'll need to set up this disk for partitioning..."
	echo "Create a single partition, ensure it is primary, and that it is the only one."
	echo "This is a simple hack so we have QEMU emulate grub too."
	echo "Distributions of Feral shouldn't come with GRUB or anything, as I want to minimize GPLed software as much as possible."
	echo "(This is to make it easy to reuse Feral without some unfairly annoying terms attached)"
	
	sudo cfdisk /dev/loop0
	sudo losetup -o 1048576 /dev/loop1 /dev/loop0	
	sudo mke2fs /dev/loop1
	
	mkdir feral_ext2_root
	
	sudo mount /dev/loop1 feral_ext2_root
	sudo grub-install --target=i386-pc --boot-directory=feral_ext2_root/boot \
	     --modules="biosdisk part_msdos ext2" /dev/loop0
	
	## TODO: Copy the files we generate to the disk as is appropriate...

	sudo umount feral_ext2_root
	sudo losetup -d /dev/loop1
	sudo losetup -d /dev/loop0
	
	rmdir feral_ext2_root
	
test:	$(TEST_FILE)
	# Imitate a certain Team Red CPU...
	$(QEMU) $(TEST_FILE) -smp cpus=1,threads=2,cores=16,maxcpus=32 -m 8G --enable-kvm -cpu host

cleanall:	clean
	rm -rf $(TEST_FILE)


