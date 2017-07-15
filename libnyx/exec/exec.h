#ifndef _LIB_NYX_EXEC_H_
#define _LIB_NYX_EXEC_H_

#include <nyx/size_abstract.h>

/* Options to support everything under the sun so this can be merged into Feral and be useful later... */
typedef enum
{
	EXEC_ELF   = 0,
	EXEC_MACHO = 1,
	EXEC_COFF  = 2,
	EXEC_PE    = 3
}ExecFormat;

typedef enum
{
	ExecFormat format;
	/* TODO: locations in memory and all... */
}ExecInfo;

#endif
