# This is the first time I've written Mabell assembly, so I'm expecting to have to spend forever constantly patching this mess.
# Rewrote this in GNU syntax because reasons..?

.code32				# By default, Multiboot 2 places us in 32-bit compatibility mode. We need to un-do the 32-bit mode and go back to 64-bit.
.globl start			# This is the entry point for the kernel.
.globl multiboot		# This is where the Multiboot information is at.
.extern main			# We expect 'main' for the main function of the kernel. Perhaps change to 'KiKernelMain'.

#define MBOOT_MAGIC 		0xE85250D6
#define MBOOT_ARCH_LEGACY	0x00000000
#define MBOOT_SIZE		(multiboot_end - multiboot)
#define MBOOT_CHECKSUM		(0 - MBOOT_MAGIC - MBOOT_ARCH_LEGACY - (multiboot_end - multiboot)) & 0xFFFFFFFF


.extern code			# Multiboot wants these fields.
.extern bss			#
.extern end			#

# '.long' is the same as 'dd'. '.quad' is the same as 'dq'. We do <<source, dest>> because unintuitive things are cool? GNU syntax is strange.

multiboot:
	.long MBOOT_MAGIC
	.long MBOOT_ARCH_LEGACY
	.long MBOOT_SIZE
	.long MBOOT_CHECKSUM

	.long multiboot
	.long code
	.long bss
	.long end
	.long start

multiboot_end:
	

start:
	cli			# Interrupts here are the bane of all existance!
	movl _earlystack, %esp	# Set up the bootstrapping stack we need.
	pushl %ebx		# Push the multiboot struct header we'll need...
	call main		# Call the main() function. Kernel should enable interrupts as it sees fit.
	
hang:
	jmp .			# We shouldn't ever return.

.section stack
	.fill 8192, 1, 0
	
