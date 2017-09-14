/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Contributors:
 *	Brian Schnepp	[author]
 */

/* TODO: Include FERAL kernel's headers so we can define the default memory manager in Waypoint. */

#ifndef __FERAL_MEMORY_MANAGER_MAIN__
#define __FERAL_MEMORY_MANAGER_MAIN__

#include <feral/feralstd.h>

VOID* MmAllocateKernelMemory(UINTN amount);
VOID  MmFreeKernelMemory(VOID* memorypages);


/* Create the system memory areas we need... */
VOID  MiInitSystemMemoryAreas(VOID);	/* Memory Internal  */


#endif
