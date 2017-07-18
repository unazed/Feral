#ifndef _NYX_SIZE_ABSTRACT_H_
#define _NYX_SIZE_ABSTRACT_H_

#include <feral.h>
#if defined(__x86_64__) || defined(__i386__)
typedef unsigned long  UINT64;
typedef unsigned int   UINT32;
typedef unsigned short UINT16;
typedef unsigned char  UINT8;
	
typedef signed long  INT64;
typedef signed int   INT32;
typedef signed short INT16;	
typedef signed char  INT8;
		
typedef UINT8 BOOLEAN;
#endif

#if defined(__arm__) || defined(__aarch64__)
typedef unsigned long  UINT64;
typedef unsigned int   UINT32;
typedef unsigned short UINT16;
typedef unsigned char  UINT8;
	
typedef signed long  INT64;
typedef signed int   INT32;
typedef signed short INT16;	
typedef signed char  INT8;
		
typedef UINT8 BOOLEAN;
//Are these correct? I have 2 little quad-core ARM machines lying around to test on.
//No clue if they're Aarch64 or not.
#endif

typedef void VOID;


#endif
