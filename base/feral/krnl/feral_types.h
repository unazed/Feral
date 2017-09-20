/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Contributors:
 *      Brian Schnepp [author]
 */

#include <feral/feralstd.h>

typedef struct _CpuInformation
{

	INT32 CpuType;
	INT32 CpuSubtype;
	UINT8 Bits;	/* Add 1 for every multiple of 16-bit. 64-bit CPU is 4. */
}CpuInformation;

#if defined(__x86_64__) || defined(__i386__)
typedef UINTN VmOffset;
typedef UINTN VmSize;
#else
/* Some CPUs may have RAM size that isn't the same. Figure this out later... */
typedef UINTN VmOffset;
typedef UINTN VmSize;
#endif

/* Is this correct..? */
typedef struct _CpuThread
{
	BOOL  IsRunning;
	UINTN InterruptClockFreq;
	UINTN CpuFreq;
}CpuThread;

typedef struct _MachineInfo
{
	CpuInformation CpuInfo;
	UINT64 NumberOfCpus;	/* Who needs more than physical 2^64 CPUs??? */
	UINT64 NumThreadsPerCpu /* In case someone goes crazy with SMT implementation. */

	VmSize MemorySize;	/* Misleading: we assume Virtual mem == theoretical mem limit. */
	VmSize PhysMemorySize;	/* See above... */

	CpuThread* threads;
}MachineInfo;
