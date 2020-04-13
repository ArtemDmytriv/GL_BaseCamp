#include "head.h"

const char * LOCALHOST = "127.0.0.1"; // local adress

int main(int argc, char ** argv){
    
    //StealthMode(); spy mode

    if (WSAinit()){
        exit(1);
    }
    
    //ShowWindow(GetConsoleWindow(), SW_MINIMIZE);

    socktype sock = processClientSocket(LOCALHOST, PORT);

    cleanupClient(sock);

    return 0;
}