#ifndef _MAIN_HEAD
#define _MAIN_HEAD

#ifdef __linux__
// headers for Linux compability
#include "linxnetw.h"


#elif _WIN32
// headers for Windows compability
#include "winnetw.h"
#include "winfunc.h"

#else
#error "Run on not supported OS"
#endif

// cross-platform headers
#include <stdio.h>
#include <stdlib.h>

#endif