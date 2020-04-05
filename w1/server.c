#include "head.h"

#define PORT 5002

int main(int argc, char ** argv){
    
    // Init WinApi 
    WSADATA wsaData;
    
    printf("Initialising WinSock...\n");
    if (WSAStartup(WINSOCK_VERSION, &wsaData)){
        printf("WinSock init failed!\n ");
        exit(1);
    }
    else{
        printf("WinSock init succeed\n");
    }

    POINT * lp;
    GetCursorPos(lp);

    WSACleanup();
    printf("WinSock closed\n");
    
    return 0;
}