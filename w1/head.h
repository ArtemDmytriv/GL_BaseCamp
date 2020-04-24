#ifndef _MAIN_HEAD
#define _MAIN_HEAD

#define MAXCON 10             
#define BUFFLEN 64            /* Buffer size for client's reply */
#define PORT 5002               
#define LOOPCOUNT 20         /* How many replies will be from client */
#define PAUSE 500             /* delay time between replies from client */
#define LOCALHOST "127.0.0.1" /* Local address ip */

#ifdef __linux__
// headers for Linux compability
#include "linux/linxnetw.h"
#include "unistd.h"
#include <X11/Xlib.h>
#include <pthread.h>
#include "linux/linxfunc.h"

#elif _WIN32
// headers for Windows compability
#include "win/winnetw.h"
#include "process.h"
#include "share.h"
#include "win/winfunc.h"

#else
#error "Run on not supported OS"
#endif

// cross-platform headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef __linux__
typedef int socktype;  
#elif _WIN32
typedef SOCKET socktype;
#endif


#endif