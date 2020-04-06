#include "head.h"

int main(int argc, char ** argv){

    const char * chaddr = "127.0.0.1";

    WSADATA wsaData;
    printf("Initialising WinSock...\n");
    if (WSAStartup(WINSOCK_VERSION, &wsaData)){
        printf("WinSock init failed!\n ");
        exit(1);
    }
    else{
        printf("WinSock init succeed\n");
    }


    WSACleanup();

    return 0;
}