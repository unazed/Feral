/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 *
 * Contributors:
 *	Brian Schnepp [author]
 */
#include <feral/feralstd.h>
#include <feral/task.h>

/* */
typedef struct _FeralPort
{
	/* Some structure kind of like Mach's ports... */
	UINTN  Port;		/* ID of the port we have. This is what index in a global array with a process number we get. */
	STRING Identifier;	/* A string identifier: we can be part of a 'namespace' of ports of sorts. This is to allow us to have unlimited Tasks. */
	TASK*  TaskOne;		/* A port connects two Tasks. This is the first one. */
	TASK*  TaskTwo;		/* A port connects two Tasks. This is the second one. */
	UINT32 PermissionsOne;	/* What permissions does the first one get? */
	UINT32 PermissionsTwo;  /* What permissions does the second one get? */
	VOID*  PagesToShare;	/* What page(s) do these Tasks get to share? */
	UINTN  NumPagesToShare;	/* How many pages to we share? */
}FeralPort;

typedef FeralPort* FeralPortArray;

/* Creates a port between the two tasks. */
FeralPort* KeCreatePort(STRING group, TASK* TaskOne, TASK* TaskTwo, UINT32 PermissionsOne, UINT32 PermissionsTwo, VOID* Pages, UINTN NumberOfPages);

/* Deletes a port between the two tasks. The pages are unmapped from Task 2 and become property of Task 1. */
void KeDeletePort(FeralPort* port);


