#ifndef _MAIN_HEAD
#define _MAIN_HEAD

#define MAXCON 10
#define BUFFLEN 64
#define PORT 5002
#define LOOPCOUNT 20
#define PAUSE 500




#ifdef __linux__
// headers for Linux compability
#include "linxnetw.h"
#include "termios.h"
#include "unistd.h"
#include "X11/Xlib.h"
#include "linxfunc.h"

#elif _WIN32
// headers for Windows compability
#include "winnetw.h"
#include "process.h"
#include "winfunc.h"

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