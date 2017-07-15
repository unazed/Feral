#ifndef _LIB_NYX_MACHO_H_
#define _LIB_NYX_MACHO_H_

#include <nyx/size_abstract.h>

#pragma pack(1)
//Wrong names for lots of fields. Meh.

typedef enum
{
	ELF_RELOCATABLE = 0,
	ELF_EXECUTABLE = 1,
	ELF_SHARED = 2,
	ELF_CORE = 3
}ElfExecTypes;

typedef struct _ElfHeader
{
	UINT32 magic;	//MachO magic number...
	UINT8  cpu_bitsz;
	UINT8  cpu_endian;
	UINT8  e_version;
	UINT8  e_identifier;
	UINT64 e_padding;
	UINT16 e_type;
	UINT16 e_machine;
	UINT32 e_version;
	UINTN  e_entry;
	UINTN  e_phoff;
	UINTN  e_shoff;
	UINT32 e_flags;
	UINT16 e_ehsize;
	UINT16 e_phentsize;
	UINT16 e_phnum;
	UINT16 e_shentsize;
	
}ElfHeader;
#pragma pack(0)

#endif
