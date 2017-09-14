/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 *
 * Contributors:
 *	Brian Schnepp [author]
 */

#ifndef _FERAL_OBJECT_H_
#define _FERAL_OBJECT_H_

/* Objects are sort of like files. This is the 'reason' for opening one. */
typedef enum _OB_OPEN_REASON
{
	ObCreateHandle,
	ObOpenHandle,
	ObCloneHandle,
	ObInheritHandle
}OB_OPEN_REASON;

typedef enum _OB_CLOSE_REASON
{
	ObDeleteHandle,
	ObErrorHandle,
	ObInvalidHandle
}OB_CLOSE_REASON;


/* TODO: Functions to create and manage objects. */


#endif
