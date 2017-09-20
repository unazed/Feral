/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 *
 * Contributors:
 *	Brian Schnepp [author]
 */
#ifndef _FERAL_OBJECTS_KDRIVER_H_
#define _FERAL_OBJECTS_KDRIVER_H_

#include <feral/feralstd.h>

#ifdef __cplusplus
extern "C" 
{
#endif

typedef enum
{
	/* DP and VGA are all I'll create on my own. */
	VGA_INTERFACE         = 0x0,
	DISPLAYPORT_INTERFACE = 0x1,
	HDMILEGACY_INTERFACE  = 0x2,
	HDMI2_INTERFACE       = 0x3,
	DVI_INTERFACE         = 0x4,
	VR_INTERFACE          = 0x5	/* Flesh this out when I get around to understanding how VR works driver-wise. */
}DISPLAY_DRIVER_TYPE;

typedef UINT64 DRIVER_TYPE;
/* What kind of driver is this? */
#define DISPLAY_DRIVER ((DRIVER_TYPE)0000000000000001)
#define GRAPHICS_DRIVER ((DRIVER_TYPE)0000000000000002)
#define AUDIO_OUT_DRIVER ((DRIVER_TYPE)0000000000000003)
#define AUDIO_IN_DRIVER ((DRIVER_TYPE)0000000000000004)
#define GENERIC_USB_DRIVER ((DRIVER_TYPE)0000000000000005)

typedef enum
{
	DeviceInvalidHandle = 0x0000,
	DeviceObjectCreated = 0x0001
	/* TODO... */
}OBJECT_TYPE_STATE;

typedef struct _KERNELDRIVER
{
	DRIVER_TYPE DriverType;	/* This is first so we dereference the pointer and then know what to cast this as. */	

	/* Demand to the driver that it essentially 'reset' all it's logic. */
	void (*ResetDevice)();
	
	/* ALL of these functions are TODO! */
	FERALSTATUS (*DriverEntry)();		/* Entry point for a driver... */
	FERALSTATUS (*DriverExit)();		/* When the driver is requested to shut down. */
	FERALSTATUS (*DriverDispatcher)();	/* "kernel IPC" for the driver. */

	
}KERNELDRIVER;


typedef struct _DEVICE_OBJECT
{
	UINT64 Type;			/* What kind of device is this? */
	UINT64 Port;			/* What do we tell the CPU as the device we're accessing? */
	KERNELDRIVER* Driver;		/* The associated driver for this object... */
	OBJECT_TYPE_STATE State;	/* What state is the device in? */
	/* Try to stay similar ReactOS family's data structures as best we can... */
}DEVICE_OBJECT;




#ifdef __cplusplus
}
#endif

#endif
