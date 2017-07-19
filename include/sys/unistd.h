/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 *
 * Contributors:
 *	Brian Schnepp [author]
 */

//For POSIX compatibility, we blindly follow POSIX, throwing logic for things like block sizes out the Glass Pane.
//If you want 512-byte blocks and other GNUy stuff, set the environment variable "LOGICALLY_CORRECT" to 1.
//Most POSIX commands and whatnot are ported from FreeBSD. If it's under the GPL, we write a replacement for it. etc. etc.
//Since we borrow a lot from the BSDs for POSIX conformance, we also need to imitate the FreeBSD kernel a lot. TODO on that.

//We'd really like to be fully POSIX-conformant, even though we shove the "POSIXness" into A:/System/Posix/root/
//Which then has the familiar /usr, /bin, /sys, /dev, /proc, /home, etc.
//(We look in A:/System/Posix/root/usr/bin and others after going into A:/Applications/, A:/Program Files/, etc. Thus, we look like a NIX system.)

#ifndef _SYS_UNISTD_H_
#define _SYS_UNISTD_H_

#include <feral/feralobjs.h>

//We're going to aim to implement POSIX.1-2008.
#define _POSIX_VERSION 200809L

//Pathfinder (will) ha(ve/s) a X server personality. Thus, we can be X11R6 compliant. Essentially the inverse of how Wayland solves this problem.
//The framing system imitates Xorg, not Xorg implementing the new specification. Where patches to existing projects can be avoided, we do it.
//Pathfinder will have some sort of system that lets us have remote desktops and all probably. I don't know.
#define _XOPEN_VERSION 700

typedef UINT16 size_t;
typedef INT16 ssize_t;

#define  STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#ifndef NULL
#define NULL 0
#endif


#define F_OK 0
#define X_OK 1
#define W_OK 2
#define R_OK 4

//POSIX 'access()' call...
int access(const char* path, int amode);

//POSIX alarm() call...
unsigned int alarm(unsigned int);

//POSIX chdir() call...
int chdir(const char*); 



#endif
