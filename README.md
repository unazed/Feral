# Feral
Repository for the Feral kernel

The Free pErformance oRiented Awesome kerneL.

This repository stores just the code for the Feral kernel by itself. It may or may not be buildable by itself.
Maybe we'll have a working kernel by 2025?

Priority right now: Fix the horrible inconsistency caused by gluing together a bunch of unstable branches of Feral!

This is just a hobby project with very high standards (and thus will probably never be completed to adequate standards.)
The aim is to build the kernel to run as fast as possible, have little to no security protecting drivers from going haywire (so they can go faster), and get any games which are ported to Feral well to run as fast as possible. The priority is strong GPU support (at the very least, for Team Red exclusively, and only supporting anything from 2017 and onward.)

This repository is VERY unstable. Expect failing builds almost all the time. Stable branches will be merged into Waypoint's repository. (When we have a suitable '0.01 release', then we'll start tagging.)
___

Some major design choices:

  - IPC should be as fast as possible. Messages shouldn't even be looked at or buffered by the kernel. The kernel just allocates a page (or more) which process A can write into which process B can then read. We can also try to pass messages via registers, if available. Since we don't expect to support IA-32, we have plenty of registers to do this with.
  
  - All (ideally) or most (realistically) of the kernel's subsystems should be possible to replace, via drivers. Slap in a ReactOS compatibility layer or Mach personality or whatever. Feral should accept it all. (Even better if we can find Lites' source code and get it running on Feral as a kernel extension with some modifications...) Personalities are in kernel-space for mostly performance reasons.
  
  - Avoid having drivers be just copy/paste of existing drivers with new glue code. Put some sort of standardization in. Ideally importable pieces which can be reused and patched if a vulnerability pops up, such that a bug in that part would quickly be patched and prevent every driver individually getting patched for it: it's already fixed for them.
  
  - Kernel understands what threads are, how they work, etc. etc., but does not iteself manage threads. Instead, a userspace libthreads does, which is probably (one way or another) statically linked into applications. This is for performance, letting tasks that don't necessarilly need to be stopped (ie, only 1 thread is actually blocking) continue to run for it's fair share of time.
  
  - Really heavilly depend on the hardware features of Family 17h. Squeeze as much performance out of the kernel as possible. Faster kernel means userspace has more time to run doing useful things.

  - The most important thing above everything else is GPU drivers. Find clever ways to use Team Red hardware to outperform reference drivers (Mesa), and ideally ReactOS-like systems too.

  - We require an MMU. Not sure why a desktop wouldn't have a MMU in 2017.

Some of the things that would be AWESOME for Feral would be:

	- Directly copying a message to another process, if the actual message is larger than the size of a register via memory mapping.
	- Parsing a UINTN (register size) number as a string (probably 8 letters, possibly 4 on 32-bit platforms only) in IPC... avoid having to remap memory pages if we can.
	- Try to get messages to fit into a register. Thus, we no longer need to make a mess of buffers and clean up and all.
	- Performance over almost everything else. Security is a close second, and a "user experience" is third. We would rather have fast GUI that's cool than pretty GUI that's cooler.
	- We want to get out of a game's way to do awesome stuff. Get close to the unrestrained control of hardware that *DOS had. Essentially, avoid having to do a ton of system calls and waiting for it to come back and all.
	
	- Big thing: Async system calls. Try to cram in more performance by just blocking the task, executing some more non-competing tasks, go into kernel mode, do it all at once, and THEN return the result... if this actually is a performance improvement.

	- Microkernels are cool but too impractical. Gotta go fast.
	
	
	
	
Things I'm very well aware I have no idea how to do right now:
	
	- Everything that isn't **really** obvious.


___


Feral is designed with being run on x86-64 processors in mind, but we write in C because:

	- C abstracts away the hard complexities that aren't interesting to mess with.
	- C is portable. We intend to have an Aarch64 port sometime.
	- C is easy to interface with from a different language.
	- GNU syntax assembly is strange. Avoid if at all possible... and while Blue syntax works too... Insert reason here?

___

Major design choices we're going with:

	- Mach ports are awesome. Copy it.
	- Debating if home-grown TCP/IP stack sounds fun, especially when NIC drivers AREN'T fun to make.
	- We'll probably end up with our own Waypoint-exclusive graphics API called "Cynic" or "Freedom3D" or something like that.
	- Everything is optimized carefully for performance. Minimize the size of data structures, cram things into small sizes, and carefully time how long something takes to execute.

	- I had an experimental branch with some multiboot stub mess. Merging it in and booting with that...
