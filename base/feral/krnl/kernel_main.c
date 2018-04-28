/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Contributors:
 *	Brian Schnepp [author]
 */

//TODO: Get around to bothering to fix the auto-generated license header script and all.

#include <stdint.h>
#include <hardabs/bootstruct.h>

//TODO: Purge the kernel of anything trying to imitate Mach in kernel-space in favor or something that doesn't feel glued on.
//#include "mach_types.h"

#include "feral_types.h"


void Kernel_Main(FeralBoot_Header* header)
{
	//Hello, world!!
	// Call the KiSystemStartup function as soon as we initialize the boot VGA driver and stuff.
	for (;;){};	//Temporary!!
}

/* TODO: Redo all of this as an enum instead. Much easier... */
#define KISTARTUP_FORCE_DEBUG_MODE_BIT  (0x01000000                                 )

#define KISTARTUP_FORCE_USE_VGA_DRIVER  (0x00000001 | KISTARTUP_FORCE_DEBUG_MODE_BIT)	/* Force the system to ignore graphics drivers, relying on VGA graphics instead. glNEXT disabled. */
#define KISTARTUP_FORCE_LIMIT_NUM_CORES (0x00000002 | KISTARTUP_FORCE_DEBUG_MODE_BIT)	/* Limit the number of CPUs we actually activate. */
#define KISTARTUP_CRASH_WINDBAG_DEBUG   (0x00000002 | KISTARTUP_FORCE_DEBUG_MODE_BIT)	/* Use a kernel-mode debugger on startup... */

/* Settings that are generally OK for end-users (non-developers) in A:/System/Feral/boot.ini */
#define KISTARTUP_DISABLE_LOADING_BAR   (0x00100001                                 )	/* Replace the "Starting Waypoint" graphic with text of what's being loaded by the bootstrapper. */
#define KISTARTUP_DISABLE_DEBUG_MODE    (0x00100002                                 )   /* Force the kernel to ignore debugger modes from above, in case a driver enable it. */
#define KISTARTUP_FORCE_MAX_MEMORY      (0x00100004                                 )   /* Force the kernel to only use a limited amount of memory. */


typedef uint32_t FERALBOOTFLAGS;


/*
	In-kernel utility functions should NOT follow the function naming convention for stable functions.
	If the two strings are exactly identical, the returned value will be the string length of the shorter string.
 */
int krnldiffstr(char* string, char* string1)
{
	int index = 0;
	char c  = string[0];
	char c1 = string1[0];
	while (c == c1 || (c != '\0' || c1 != '\0'))
	{
		index = index++;
		c     = string[index];
		c1    = string[index];
	}
	return index;
}

int krnlstrlen(char* string)
{
	int len = 0;
	while (string[len] != '\0')
	{
		len = len++;
	}
	return len;
}


void KiSystemStartup(int argc, char* argv[])
{
	FERALBOOTFLAGS flags = 0;

	/* TODO: Get flags set up properly and well and all. */
}
