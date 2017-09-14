## TODO : License header.


#ifndef _FERAL_GUI_FRAME_H_
#define _FERAL_GUI_FRAME_H_

#include <feral/feralstd.h>


typedef UINT64 Pixel;	/* Every 4 bytes are a color value from 0 - (2 ^ 16) */
typedef Pixel* ColorBuffer;	/* Buffer for spaces and all... */

typedef struct Frame
{
	WIDESTRING Title;
	UINT64 Width;
	UINT64 Height;
	ColorBuffer buffer;
	/* TODO */
}

typedef struct Icon
{
	ColorBuffer icon;
	WIDESTRING ToolTip;
	BOOL UseToolTip;
	/* Blah blah blah... */
}


#endif
