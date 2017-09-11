#ifndef _FERAL_KERNEL_FERAL_STD_H_
#define _FERAL_KERNEL_FERAL_STD_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Compiler is nice and will give these to us. */
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>



/* Unsigned data types. */
typedef uint64_t UINT64;
typedef uint32_t UINT32;
typedef uint16_t UINT16;
typedef uint8_t  UINT8;

/* Deal with chars... */
typedef char     CHAR8;
typedef UINT16   CHAR16;

/* Signed data type. */
typedef int64_t INT64;
typedef int32_t INT32;
typedef int16_t INT16;
typedef int8_t  INT8;


/* Pointer variants... */
typedef uint64_t* PUINT64;
typedef uint32_t* PUINT32;
typedef uint16_t* PUINT16;
typedef uint8_t*  PUINT8;

typedef char*     STRING;
typedef UINT16*   WIDESTRING;

typedef int64_t* PINT64;
typedef int32_t* PINT32;
typedef int16_t* PINT16;
typedef int8_t*  PINT8;

/* Deal with floating point numbers. */
typedef float    FLOAT;
typedef FLOAT    FLOAT32;
typedef double   DOUBLE;
typedef DOUBLE   FLOAT64;


/* Some more things which might be needed... */
typedef bool BOOL;
typedef unsigned char BYTE;
#define BOOLEAN bool
#define VOID void



/* Use of these is discouraged, but exists so it's easier to port drivers over. */
#define CONST      const
#define DWORD     UINT32
#define DWORDLONG UINT64
#define INT        INT32 
#define LONG       INT64
#define LONGLONG   INT64



/* 'natural_t' and 'integer_t''s use is discourged, but exists so it's easier to port drivers from Mach and it's derivatives. 							               */
/* (ie doing crazy things like ripping apart a 20 year old OS, glue it's userspace servers in kernel-land here, apply more super-glue, and jury rig it to work on modern hardware.)            */
/* As you can tell, I **really** don't want to write some components without having much of any idea of what I'm actually doing. So, why not borrow from an old OS? 		               */
/* Semi-strictly want to keep everything in the kernel MPL or CC0 (or otherwise public domain). No license madness with BSD headers and MIT headers everywhere. Especially no LGPL or GPL.     */
/* Rather rewrite whatever we wanted from *BSD from scratch but with the MPL or CC0 instead. 												       */
#ifdef(__x86_64__)
typedef UINT64 UINTN;
typedef INT64  INTN;

typedef UINT64 natural_t;
typedef INT64  integer_t;
#endif

#ifdef(__i386__)
typedef UINT32 UINTN;
typedef INT32  INTN;

typedef UINT32 natural_t;
typedef INT32  integer_t;
#endif

/* Use of these types is also discouraged, but it makes porting drivers easier for whoever's interested.         */
/* We'll never get driver ports if we don't make it as close to "hit compile and you're done" as possible.       */
/* Especially as a primarilly desktop-oriented operating system. Without driver support, never going anywhere.   */
#define signed8_t  INT8
#define signed16_t INT16
#define signed32_t INT32
#define signed64_t INT64

#define unsigned8_t  UINT8
#define unsigned16_t UINT16
#define unsigned32_t UINT32
#define unsigned64_t UINT64

#define float32_t FLOAT
#define float64_t DOUBLE 



#ifdef __cplusplus
}
#endif
#endif
