# Feral
Repository for the Feral kernel [TODO]

The Free pErformance oRiented Awesome kerneL.

This repository stores just the code for the Feral kernel by itself. It may or may not be buildable by itself.
Maybe we'll have a working kernel by 2025?


___

Some major design choices:

  - IPC should be as fast as possible. Messages shouldn't even be looked at or buffered by the kernel. The kernel just allocates a page (or more) which process A can write into which process B can then read.
  
  - All (ideally) or most (realistically) of the kernel's subsystems should be possible to replace, via drivers.
  
  - Avoid having drivers be just copy/paste of existing drivers with new glue code. Put some sort of standardization 
  
  - Kernel understands what threads are, how they work, etc. etc., but does not iteself manage threads. Instead, a userspace libthreads does, which is probably (one way or another) statically linked into applications. This is for performance, letting tasks that don't necessarilly need to be stopped (ie, only 1 thread is actually blocking) continue to run for it's fair share of time.
  
  - Some other stuff (essentially just a rename of WILDNYX, since that was essentially "feral-next" anyway.)
  

Some of the things that would be AWESOME for Feral would be:

	- Directly copying a message to another process, if the actual message is larger than the size of a register.
	- Parsing a UINTN (register size) number as a string (probably 8 letters, possibly 4 on 32-bit platforms only) in IPC.
	- Try to get messages to fit into a register. Thus, we no longer need to make a mess of buffers and clean up and all.
	- Performance over almost everything else. Security is a close second, and a "user experience" is third. We would rather have fast GUI that's cool than pretty GUI that's cooler.
	- We want to get out of a game's way to do awesome stuff. Get close to the unrestrained control of hardware that \*DOS had. Essentially, avoid having to do a ton of system calls and waiting for it to come back and all.
	
	- Big thing: Async system calls. Programs directly talking to the Feral kernel (ie, not with libc or a thin waypoint.h) can get some more performance by having async calls to the kernel which execute just before task time is up.
	
	
	
	
Things I'm very well aware I have no idea how to do right now:
	
	- Everything that isn't **really** obvious.