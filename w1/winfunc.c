#include "winfunc.h"

SOCKET makeServerSocket(){

    SOCKET ListenSock = INVALID_SOCKET;
    

    ListenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ListenSock == INVALID_SOCKET){
        printf("Making socket failed! progam aborting...\n");
        WSACleanup();
        exit(1);
    }
    
    return ListenSock;
}

SOCKET bindServerSocket(SOCKET ListenSock, unsigned short Port){
    
    SOCKADDR_IN SockAdrr;

    SockAdrr.sin_family =  AF_INET;
    SockAdrr.sin_port = Port;
    SockAdrr.sin_addr.s_addr = INADDR_ANY;

    if (bind(ListenSock, (const struct sockaddr *) &SockAdrr, sizeof(SockAdrr)) == SOCKET_ERROR ){
        printf("Binding socket failed! program aborting...\n");
        WSACleanup();
        exit(1);
    }
    
    listen(ListenSock, MAXCON);

    return ListenSock;
}
