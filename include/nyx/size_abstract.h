#ifndef _NYX_SIZE_ABSTRACT_H_
#define _NYX_SIZE_ABSTRACT_H_

#include <feral.h>

#ifdef _FERAL_H_
	#include <feral/feralobjs.h>
#else
	#if defined(__x86_64__)
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
#endif
#endif