#include "winfunc.h"

SOCKET makeServerSocket(){

    SOCKET ListenSock = INVALID_SOCKET;
    
    printf("Make socket\n");
    ListenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ListenSock == INVALID_SOCKET){
        printf("Making socket failed! progam aborting...\n");
        WSACleanup();
        exit(1);
    }
    
    return ListenSock;
}

SOCKET bindServerSocket(SOCKET ListenSock){
    
    SOCKADDR_IN SockAdrr;

    SockAdrr.sin_family =  AF_INET;
    SockAdrr.sin_port = htons(PORT);
    SockAdrr.sin_addr.s_addr = INADDR_ANY;

    printf("Bind sockets\n");
    if (bind(ListenSock, (const struct sockaddr *) &SockAdrr, sizeof(SockAdrr)) == SOCKET_ERROR ){
        printf("Binding socket failed! program aborting...\n");
        WSACleanup();
        exit(1);
    }
    
    printf("Listening port %d...\n", PORT);
    listen(ListenSock, MAXCON);

    return ListenSock;
}

SOCKET createConnectionServer(SOCKET ListenSock){

    SOCKET ClientSock = INVALID_SOCKET;
    ClientSock = accept(ListenSock, NULL, NULL);

    printf("Accept connection");
    if (ClientSock == INVALID_SOCKET){
        printf("Accept failed\n");
        closesocket(ListenSock);
        WSACleanup();
        return 1;
    }

    closesocket(ListenSock);

    return ClientSock;
}

SOCKET proccesServer(SOCKET ClientSock){

    char buffer[BUFFLEN];
    int bufflen = BUFFLEN;

    int res = recv(ClientSock, buffer, bufflen, 0);
    
    while (res > 0){
        printf("Bytes recieved %d B\n", res);
        printf("Recieved info: %s\n", buffer);
        //

        res = recv(ClientSock, buffer, bufflen, 0);
    }
    
    printf ("Connection clossed");

    return ClientSock;
}

int closeConnectionServer(SOCKET ClientSock){
    
    printf("Close connection\n");
    if (shutdown(ClientSock, SD_SEND) == SOCKET_ERROR){
        printf("Shutdown failed\n");
        closesocket(ClientSock);
        WSACleanup();

        return 1;
    }  

    return 0;
}

int cleanupServer(SOCKET ClientSock){

    printf("Cleanup\n");
    closesocket(ClientSock);
    WSACleanup();
    
    return 0;
}