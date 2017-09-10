/*
	Defines for kernel-mode objects.
 */

#include "feralstd.h"

#ifndef _DDK_KOBJECT_H_
#define _DDK_KOBJECT_H_

#ifdef __cplusplus
extern "C" {
#endif

/* 
	We expect your driver to have some stuff inside the Feral kernel's Registry.
	The exceptions to this are file system drivers (for obvious reasons), and the boot-mode VGA driver. 

	We'll replace this with a struct defining a parent key, subkeys, and a name soon.
*/
typedef char* RegistryPath;

/* These are for the VGA driver. They're TODO and all that. */
#define StringTerminate 0
#define StringNewline \n
#define StringTab \t

typedef enum _FeralDriverInitFlags
{
	DriverInitNoPlugAndPlay = 0x1,
	DriverInitNoDispatchOverride = 0x2,
	/* TODO */
}FeralDriverInitFlags;


typedef struct _FeralDriver
{
	
}FeralDriver;


VOID KeLoadDriver(FeralDriver* driver);
VOID KeKillDriver(FeralDriver* driver);

//TODO: Method to send flags to KiSystemStartup? (the "kernel main() function")

#ifdef __cplusplus
}
#endif
#endif
