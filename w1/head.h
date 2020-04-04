// headers for Linux compability
#ifdef __linux__

#include "linxnetw.h"

// headers for Windows compability
#elif _WIN32

#include "winnetw.h"

#else
#error "Run on not supported OS"
#endif

// cross-platform headers
#include <stdio.h>

