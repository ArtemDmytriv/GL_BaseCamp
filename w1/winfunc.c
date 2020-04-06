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

SOCKET createСonnectionServer(SOCKET ListenSock){

    SOCKET ClientSock = NULL;
    ClientSock = accept(ListenSock, NULL, NULL);

    if (ClientSock == INVALID_SOCKET){
        printf("Accept failed\n");
        closesocket(ListenSock);
        WSACleanup();
        return 1;
    }

    closesocket(ListenSock);

    return ClientSock;
}

int closeConnectionServer(SOCKET ClientSock){
    
    if (shutdown(ClientSock, SD_SEND) == SOCKET_ERROR){
        printf("Shutdown failed\n");
        closesocket(ClientSock);
        WSACleanup();

        return 1;
    }  
    
    return 0;
}

int cleanupServer(SOCKET ClientSock){

    closesocket(ClientSock);
    WSACleanup();
    
    return 0;
}