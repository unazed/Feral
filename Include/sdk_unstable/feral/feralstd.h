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

/* NIXoid support */
#define u8  UINT8
#define u16 UINT16
#define u32 UINT32
#define u64 UINT64

#define s8  INT8
#define s16 INT16
#define s32 INT32
#define s64 INT64


#if defined(__x86_64__) || defined(__Aarch64__)
typedef UINT64 UINTN;
typedef INT64  INTN;
#endif

#if defined(__i386__) || defined(__arm__)
typedef UINT32 UINTN;
typedef INT32  INTN;
#endif

/* 
	For people porting from Mach (2.5, 3, 4, GNU Mach, XNU/Darwin(?), MkLinux, whatever) for some reason.

	Since this is less likely than awkward ports from ReactOS/forks/workalikes, #define __MACH_IMITATION_DEFINES__
	before including this header.
 */

#ifdef __MACH_IMITATION_DEFINES__
#define natural_t UINTN
#define integer_t INTN

/* We already assume you're building with C11, as such, C99 is implicitly included. Not ANSI and not as portable, but portability is for people who can't write new programs...!!!! */
#define vm_offset_t 		uintptr_t
#define vm_size_t 		uintptr_t

#define mach_vm_address_t 	uintptr_t
#define mach_vm_offset_t 	uintptr_t
#define mach_vm_size_t 		uintptr_t

#define vm_map_offset_t 	uintptr_t
#define vm_map_address_t 	uintptr_t
#define vm_map_size_t 		uintptr_t
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
