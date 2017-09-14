/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 *
 * Contributors:
 *	Brian Schnepp [author]
 */

#include <feral/feralstd.h>

/* TODO: Figure out how to get smaller... */
typedef struct _FeralRights
{
	/* Each byte tells us what permissions we have, in order: Read, Write, Execute, Modify. 					*/
	/* We'll figure out how to differentiate between values (1, 2, 3, etc...) later, and for uses for it.				*/
	/* Each user gets assigned this when they get 'special permissions' to be other than what their group or themselves get.	*/	
	UINT32	  Permissions;

	/* Is this a user or a group? */
	BOOL UserOrGroup;

	/* To whom do we give the special permissions to..? */
	union
	{	
		WIDESTRING   Username;
		WIDESTRING  Groupname;
	}Whom;

}FeralRights;


/* Create FeralRights for reference in something. */
FeralRights* CreateFeralRights(UINT8 Read, UINT8 Write, UINT8 Execute, UINT8 Modify, BOOL UserOrGroup, WIDESTRING Name);

