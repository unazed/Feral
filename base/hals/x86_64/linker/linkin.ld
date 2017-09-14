/* We start execution at this place... */
ENTRY(start)

SECTIONS
{
	. = 1073741824;				/* Put sections at 1 megabyte in */
	.text BLOCK(4096) : ALIGN(4096)
	{
		*(.text)
	}

	/* Deal with read-only data here */
	.rodata BLOCK(4096) : ALIGN(4096)
	{
		*(.rodata)
	}

	/* Initialized data */
	.data BLOCK(4096) : ALIGN(4096)
	{
		*(.data)
	}

	/* Stack */
	.bss BLOCK(4096) : ALIGN(4096)
	{
		*(COMMON)
		*(.bss)
	}

	/* TODO: any other sections which might pop up */
}

