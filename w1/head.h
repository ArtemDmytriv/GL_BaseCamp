#ifndef _MAIN_HEAD
#define _MAIN_HEAD

#define MAXCON 10
#define BUFFLEN 64
#define PORT 5002
#define PAUSE 2000

#ifdef __linux__
// headers for Linux compability
#include "linxnetw.h"


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

#endif