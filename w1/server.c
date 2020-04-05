#include "head.h"

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

    SOCKET servSock = makeServerSocket();

    servSock = bindServerSocket(servSock, PORT);

    WSACleanup();
    printf("WinSock closed\n");
    
    return 0;
}