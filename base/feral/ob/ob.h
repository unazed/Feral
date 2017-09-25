/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Contributors:
 *	Brian Schnepp	[author]
 */

#include <feral/feralstd.h>
#include <feral/feralstatus.h>
#include <feral/task.h>

/* Structure/enum definitions... */
typedef enum _OB_OPEN_REASON
{
	ObCreateHandle,
	ObOpenHandle,
	ObCloneHandle,
	ObInheritHandle
}OB_OPEN_REASON;

typedef enum _OB_CLOSE_REASON
{
	ObDeleteHandle,
	ObErrorHandle,
	ObInvalidHandle
}OB_CLOSE_REASON;

typedef enum
{
	DriverType,	/* The object defines a driver's type...  */
	FileType,	/* The object is a file.  */
	DeviceType,	/* The object is a reference to a device itself, like a GPU or keyboard or something. */
	GenericType,	/* This is an object, but we don't know what it is.  */
	KernelType,	/* Kernel-land resource object. */
	TaskType,	/* Object is a task: this is what reactos calls a "Process".  */
	NetworkType,	/* Object is a reference to a network... this can be the web, LAN, etc. */
	MachineType,	/* This defines a machine, with the location based on FERALNET protocol (to be defined.) 'local' machine is always 0.0.0.0.0.0 */
	AccessType,	/* Object defines a permissions structure. */
	ResourceType,	/* Object defines a resource, such as virtual memory, GPU VRAM, etc. */
	HandleType	/* Object defines a 'handle', which is a wrapper around a more complex group of objects for simplified interaction. */
}ObjectType;

/*
For clarification, here's the terms we use:
	- A task is a program which is running, which can contain:
		- Threads, which are streams of processing which can run on multiple processor cores.
		- Itself another task, which will be referred to as a "process".
			- (This is for having a locally close-knit group of programs which have an interface to connect with each other, while appearing to
			   the rest of the system as one single task. The root task defines scheduling by itself. Kernel doesn't help other than doing it.)
*/

/* Object header defines what it is, we cast accordingly. All sub-objects have an 'Object' in their declaration, and have the 'parent' point locally. */

struct _FERALOBJECT;	/* Forward declaration for the header. */

typedef struct _FeralObjectHeader
{
        ObjectType             Type;
        UINT64                 Size;
	struct _FERALOBJECT* Object;
}FeralObjectHeader;

typedef struct _FERALOBJECT
{
	FERALOBJECT*              (*CreateObject)(struct _FERALOBJECT* This, VOID* Fields);
	VOID                                   (*DestroyObject)(struct _FERALOBJECT* This);

	VOID                      (*ModifyObject)(struct _FERALOBJECT* This, VOID* Fields);
	FERALOBJECT* (*CloneObject)(struct _FERALOBJECT* This, struct _FERALOBJECT* Where);
}FERALOBJECT;


/*
	TODO: Consider is redoing this as a struct which has a bunch of function pointers is a better idea.
	Performance is hindered with excessive function calls (lots of push/pop to stack, registers, etc. which are just undone anyway.)
	If you MUST make a new function, try to keep it it's arguments in registers or something.
	Avoid messing with RAM/stack/whatever if we can at all help it (too sloooowww!!!)
 */

/* Kernel calls this function to initialize the whole object system. */
BOOL ObInitializeSystem(VOID);

/* These functions are VOLATILE. Expect definitions to change. Backwards compatibility is only ensured for releases after 1.x.x. */
FERALSTATUS ObInitializeTask(TASK TaskToStart, TASK Parent);	/* Parent may be null. In such a case, the parent becomes (sessmgr/csrss/scm/whatever)/init/whatever. */
FERALSTATUS ObTerminateTask(BOOL HaveLock, TASK TaskToKill);	/* Why are these two functions here... and not part of Memory Manager? That, I don't know either. */
