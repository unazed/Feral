# This is the first time I've written Mabell assembly, so I'm expecting to have to spend forever constantly patching this mess.
# Rewrote this in GNU syntax because reasons..?
# (Mainly because i'm almost 99% sure that Mabell syntax is used for a LOT of things I might need.)
# Wonderfully ambiguous, as I always am.

.code32				# By default, Multiboot 2 places us in 32-bit compatibility mode. We need to un-do the 32-bit mode and go back to 64-bit.
.globl start			# This is the entry point for the kernel.
.globl multiboot		# This is where the Multiboot information is at.
.extern Kernel_Main		# We expect 'main' for the main function of the kernel. Perhaps change to 'KiKernelMain' (This calls KiSystemStartup()...).
				# Alternatively, we can keep Kernel_Main, have that actually be the system initializer, THEN go to KiKernelMain.

.set MBOOT_MAGIC, 		0xE85250D6	# Multiboot 2 requires this magic number. Multiboot 1 doesn't do what we need it to do.
.set MBOOT_ARCH_LEGACY,		0x00000000	# This gives us 32-bit mode, we switch to 64.
.set MBOOT_SIZE,		(multiboot_end - multiboot)
.set MBOOT_CHECKSUM,		(0 - MBOOT_MAGIC - MBOOT_ARCH_LEGACY - (multiboot_end - multiboot)) & 0xFFFFFFFF

# '.long' is the same as 'dd'. '.quad' is the same as 'dq'. We do <<source, dest>> because unintuitive things are cool? GNU syntax is strange.

.align 8
jmp start	# Get us out of here!
multiboot:
	# Magic we need for Multiboot 2.
	.long MBOOT_MAGIC
	.long MBOOT_ARCH_LEGACY
	.long MBOOT_SIZE
	.long MBOOT_CHECKSUM

	# Address tags Multiboot wants... did I do this right???
addr_start:
	.word 2				# Show that we are indeed a address tag.
	.word 24			# I was told to turn on these flags without any idea what these do.
	.long (addr_end - addr_start)	# Size of this tag.
	.long multiboot			# Multiboot's information.
	.long text			# load_addr is where text starts.
	.long bss			# bss is after text, so it's address is the end...
	.long end			# The end of the bss segment.
	.long start
addr_end:

entry_start:
	.word 3				# Entry section.
	.word 0				# No flags.
	.long (entry_end - entry_start)	# Size of this tag.
	.long start			# Where the kernel starts execution.
entry_end:

.word 0
.word 0
.long 8					# Multiboot expects this to be present.
multiboot_end:

.global start
.type _start, @function
start:
	cli			# Interrupts here are the bane of all existance!
	movl sstack, %esp	# Set up the bootstrapping stack we need.
	pushl %ebx		# Push the multiboot struct header we'll need... Only one we strictly need (EAX tested later.)

	pushl $0		# Put 0x0 on the stack.
	popf			# Kill the EFLAGS register.

	# Here we start with setting up long mode.
	# It's pretty important that we do this right.

	# Now we do check for a valid x86_64 CPU. We however don't check if CPUID is available
	# to be able to do the check for x86_64.
	# Either way, "production grade" enough.
	# CPUs that old shouldn't really be even considered at all.
	# I mean, I guess for fun, you can try to get Feral on it... but why?
	# This kernel is mainly for learning (and eventually to be used for a serious, "gaming-oriented" OS)
	# An 8086 in 2017 just can't handle that. It's barely faster than a calculator (if not on-par).

	cmpl %eax, 0x36D76289
	jnz hang		# panic!!!

	# ok, let's do a sanity check and make sure you're not doing something stupid like running on an i686 or something.

	movl $0x80000000, %eax	# Set EAX to that value
	cpuid			# We assume CPUID is supported. Adding the logic needed  to actually test would bloat this file up too much.
	cmpl $0x80000001, %eax  # Compare the EAX register.
	jb hang			# Hang if it's below. There's no long mode here.
	movl $0x80000001, %eax	# Set the EAX register to this...
	cpuid			# Check CPU ID.
	andl (1 << 29), %edx	# Test if the long mode bit is set. 
	jz hang			# If they aren't...

	#Otherwise, we go on to boot in 64-bit mode. 
	jmp enter_long_mode	# TODO: Figure out what kind of crazy insane magic we need to get eax and ebx to work ok.

	popl %ecx		# Assume the EBX we pushed a long time ago goes back here, so it gets passed to Kernel_Main...
	call Kernel_Main	# Call the main() function. Kernel should enable interrupts as it sees fit.

	# We should NEVER get to this area. If we do, something terribly wrong has happened.
	cli
	hlt

hang:
	jmp hang		# We shouldn't ever return.

disable_paging:
	movl %cr0, %eax		# Move the contents of the control register to eax.
	andl $0x7FFFFFFF, %eax	# Clear the paging bit.
	movl %eax, %cr0		# Move EAX back into CR0.

	## TODO...
	ret

enter_long_mode:
	call disable_paging
	## TODO...
	## With paging, we have a maximum of 256TB of memory we can actually use.
	## This shouldn't be an issue for a very long time.
	## Each table has 512 entries, which control 512GB each.

	## TODO: Identity map a couple of pages for the kernel, load the kernel at -128TB or so.
	## Userspace gets 127TB of virtual memory to play with, should be enough.
	## We could also (not) split it in half and give the kernel only 2GB of virtual memory.
	## This would probably be nicer overall. Choices, choices...

	## MMU manipulation should be pretty fun!

	# Let's clear the page tables.
	movl $0x1000, %edi	# Set EDI to 4096.
	movl %edi, %cr3		# Put this into control register 3.
	xorl %eax, %eax		# Purge EAX's contents.
	movl $0x1000, %ecx	# Set ECX to 4096.
	rep stosl		# Pretty sure this is right?
	mov %cr3, %edi		# Move the value back into EDI.

	# We're now going to need to set up the tables as we see fit.
	# *003 enables READ and WRITE.

	# Let's identity map the first two megabytes, for now.
	movl $0x2003, (%edi)	# Set the DWORD at edi to 0x2003.
	addl $0x1000, %edi	# Add 4096 to EDI.

	movl $0x3003, (%edi)	# Set DWORD at EDI to 0x3003...
	add $0x1000, %edi	# Add 0x1000 to the destination index...

	movl $0x4003, (%edi)	# Set the DWORD at... you get the idea.
	addl $0x1000, (%edi)	# Add 0x1000 to the destination index.

	movl $0x00000003, %ebx	# Move 3 into EBX.
	movl   $00000512, %ecx	# Move 512 into ECX.

.SetEntry:
	movl %ebx, (%edi)	# Set the DWORD at EDI to EBX.
	add $0x1000, %ebx	# Add 4096 into EBX.
	add $8, %edi		# Add 8 to the desintation index.
	loop .SetEntry		# Repeat this again and again and again...


enable_pae:
	movl %cr4, %eax		# Move into EAX.
	orl $0x20, %eax		# Flip the bit on.
	mov %eax, %cr4		# Give it back.

finish_long_mode:
	movl $0xC0000080, %ecx	# Move into ECX the EFER MSR's location.
	rdmsr			# No clue if this instruction is correct in Mabell syntax. Let's try it anyway. (Does it need a suffix???)
	or $(1 << 8), %eax	# Set this bit on.
	wrmsr			# Write to the register.

	# Now we re-enable paging, since x86-64 requires paging.
	movl %cr0, %eax
	or $(1 << 31), %eax		# Just un-do what we did earlier to kill paging.
	mov %eax, %cr0

	# We not need to create a placeholder GDT, which we destroy and create a new one later.
	# This might sound unintuitive, but it's needed to get the kernel to be memory mapped into the higher half area.
	# We want a higher half kernel since it's easier to maintain ABI compatibility.
	# (Speaking of higher level stuff, we might do something crazy like make filepaths more (native) "New Technology"-like, ie, /Device/DosDrives/A/FERALKER.NEL)
	# This would (of course) be all internal, and allows us to hide /usr, /dev, /sys, /bin, etc, which only exist for *NIX compatibility, and aren't "true files".
	# Since we like to copy some things about Mach, we can even incorporate features of it's descendants, ie, an "/Applications" and "/System" folder.
	# Just to make it **really** easy to port to Waypoint. All of those are just handle-objects or symlinks to somewhere else (/System points to A:/System, for example.)
	# References to "/mach_kernel" should also symlink to A:/FERALKER.NEL, which would be /Device/HardDisk0Section2/FERALKER.NEL.
	# (where HardDisk0Section2 is the 'root' drive, and section 1 is an EFI system partition or whatever else, doesn't matter.)
	# (Of which, when implementing the kernel to support an EFI stub mode, we'll have the awkward naming of "FERALKER.EFI".)

	# One problem to deal with is how in the world to get the old stack, pop the EBX register off it, and get a pointer to the multiboot info we wanted.
	# We're taking up an awful lot of memory, while loading the kernel, we might have inadventently overwritten that area in memory anyway.
.code64
trampoline:
	# TODO...

.code32
.section .bss
stack:
	.align 16
	.fill 16384, 1, 0	# Should be plenty of room here with a 16KiB stack.
sstack:

.code64
stack64:
	.align 16
	.fill 16384, 1, 0	# Plenty of room for the stack here, even with twice the size of stuff.
sstack64:
end:
