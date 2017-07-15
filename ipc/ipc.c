#ifndef _WILDNYX_IPC_MSG_H_
#define _WILDNYX_IPC_MSG_H_

#include <nyx/size_abstract.h>	
//This file becomes just "#include <feral/feralobjs.h" when merged.

typedef struct _NyxTask
{
		/* Stuff we'll need. */
		UINTN references;
		UINTN threads;
		
		UINT64 task_flags;	//Running, not running, blocked, etc...
		BOOLEAN terminated;	//This task should be removed when the kernel sees it...
		
		/* Statistics... */
		UINT64 total_user_time;
		UINT64 total_system_time;
		
		struct _NyxTask* children;	//Child tasks...
		
		//TODO: Virtual memory map declarations and all.
		
		UINTN priority;				//Priority of this task. 0 - 255.
									//Max of whatever is "natural int" of tasks.
									
		//TODO: IPC ports and all.
		/* TODO: pretty much everything. */
		
}NyxTask;

typedef struct
{
		UINTN msg_hdr_bits;
		UINTN msg_hdr_size;
}NyxMsgHdr;

#endif