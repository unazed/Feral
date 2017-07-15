all:	bootstrap.o
	

bootstrap.o: boot/multiboot.asm
	$(ASM) $(ASMFLAGS) boot/multiboot.asm -f elf64 -o bootstrapx64.o
	objcopy -O elf32-i386 bootstrapx64.o bootstrapx86.o
	mv bootstrapx86.o $(BUILD_DIR)/bootstrap.o
