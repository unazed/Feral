/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 *
 * Contributors:	
 *	Brian Schnepp	[author]
 */


#include "multiboot.h"
#include "mbstdio.h"

#include <hardabs/bootstruct.h>
#include <feral/feralobjs.h>


/* Ripped from the old FeralBoot. */
#define E_IDENTC 16




struct ElfHeader
{
	UINT8 e_ident[E_IDENTC];

	UINT16 e_type;
	UINT16 e_machine;

	UINT32 e_version;

	UINTN e_entry;
	UINTN e_phoff;
	UINTN e_shoff;

	UINT32 e_flags;

	UINT16 e_ehsize;
	UINT16 e_phentsize;
	UINT16 e_phnum;
	UINT16 e_shentsize;
	UINT16 e_shnum;
	UINT16 e_shstrndx;
}ElfHeader;

struct ElfProgramHeader
{
	UINT32 p_type;
	UINT32 p_flags;
	
	UINTN  p_offset;
	UINTN  p_vaddr;
	UINTN  p_paddr;
	UINTN  p_filesz;
	UINTN  p_memsz;
	UINTN  p_align;
}ElfProgramHeader;

struct ElfSectionHeader
{
	UINT32 sh_name;
	UINT32 sh_type;
	
	UINTN  sh_flags;
	UINTN  sh_addr;
	UINTN  sh_offset;
	UINTN  sh_size;

	UINT32 sh_link;
	UINT32 sh_info;

	UINTN  sh_addralign;
	UINTN  sh_entsize;
}ElfSectionHeader;

enum ElfType
{
	ET_NONE = 0,
	ET_REL = 1,
	ET_EXEC = 2,
	ET_SHARED = 3,
	ET_CORE = 4	//This is used for program memory dumps
};
/////////////////////////////////////////////////////////////////////


#if 0
typedef struct _FeralBoot_Header
{
	UINTN  RamAmount;
	
	UINTN  ScreenWidth;
	UINTN  ScreenHeight;
	UINT8  isTextMode;

	VOID*  VideoMemAddr;
	CHAR8* KernelArguments;

	//TODO...
}FeralBoot_Header;
#endif

/* Kernel loader. */

void KElfLoader(MultibootInfo* header)
{
	//Load it up!
	//We have no malloc() or free(), so we have to do everything on the stack.

	// The kernel is expected to be just an ordinary ELF64 shared object named 'floskrnl'.
	// Something we'll do later is add encryption protection and all that.

	ElfHeader* header;
	FeralBoot_Header* header;
	

	//Inline ASM to switch to 64-bit, prep the kernel, load!
	return;
}




