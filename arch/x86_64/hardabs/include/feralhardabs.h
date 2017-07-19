/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 *
 * Contributors:	
 *	Brian Schnepp	[author]
 */


#include <feral/feralobjs.h>

typedef struct _DAY_MONTH_PAIR __attribute__((__packed__))
{
	UINT8 NumDaysEven : 1 	//If number of days is 30 or 28. Just to waste a bit to get Day to 4 bits.
	UINT8 Month 	  : 3;	//0 - 14 (Smallest you can represent months with)
	UINT8 Day   	  : 4;	//0 - 31
}DAY_MONTH_PAIR

typedef struct _KERNEL_SYSTEM_TIME
{
	UINT16 Year;		//Are you really using Waypoint in 65535 AD?
	UINT8  DayMonth;	//Above should be treated as a UINT8...	
}KERNEL_SYSTEM_TIME;


/* Get the current thread that the kernel uses. The kernel is ALWAYS on 1 physical processor. */
//TODO on this defenition, etc. etc. How will this work out?
VOID* KeGetCurrentThread();
// The kernel is async in order to squeeze more performance out.
// While this 'wastes' a processor to do more awesome, it prevents the usermode --> kernel mode
// context switch, which does the most to impact performance. (over 100 CPU cycles!!!!)
// We care more about performance than scalability. (And readability over performance, 
// hence why C instead of raw assembly. Also so we can do an Aarch64 port.)

//Especially since Team Red is making good 8-core processors, there's no shortage of cores to worry
//about. We also really don't care about power efficiency outside of hardabs for Aarch64.
//Essentially no one still uses a 2-core system for gaming anymore. Don't bother supporting it.

//We're focused on high-end hardware, where 800W - 1200W PSUs (or better like 1600W) and dual top-of-the-line graphics cards are the norm.


/* TODO: make NIXoid applications happy. */
UINT64 UsConvertKernelStructTimeToEpochTime(DAY_MONTH_PAIR pair);


//TODO: Provide the nice defines we want for the assembly stuff we have to have.
// (ie, setting up stack and all that...)

//Probably a 12MB stack.





//The logic goes if you don't start making a production system NOW, it'll never be done by the time 
//it's able to be relevant. I should have started this (as in THIS this) when I was 12 - 13. Then we'd 
//be done by 2040, not like 2045.
