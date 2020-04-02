// headers for Linux compability
#ifdef __linux__

#include <sys/socket.h> 
#include <sys/types.h> 

// headers for Windows compability
#elif _WIN32
// Will be soon

#include <sys/types.h> 
#include <sys/socket.h>

#error "Not Supported Yet"  

#else
#error "Run on not supported OS"
#endif

// cross-platform headers
#include <stdio.h>

