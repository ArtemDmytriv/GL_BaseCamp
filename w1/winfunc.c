#include "winfunc.h"

SOCKET makeSocket(unsigned short Port){


    SOCKET ListenSock = INVALID_SOCKET;
    SOCKADDR_IN SockAdrr;

    struct addrinfo *res = NULL, hints;

    ListenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ListenSock == INVALID_SOCKET){
        printf("Making socket failed! progam aborting...\n");
        WSACleanup();
        exit(1);
    }

    SockAdrr.sin_family =  AF_INET;
    SockAdrr.sin_port = Port;
    SockAdrr.sin_addr.s_addr = INADDR_ANY;

    if (!bind(ListenSock, (const struct sockaddr *) &SockAdrr, sizeof(SockAdrr)) ){
        printf("Binding socket failed! program aborting...\n");
        WSACleanup();
        exit(1);
    }

    listen(ListenSock, MAXCON);

    return ListenSock;
}