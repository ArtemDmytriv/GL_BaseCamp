#include "linxfunc.h"

typedef struct MouseData{
    char LKM;
    char RKM;
    int x;
    int y;
} MouseData;

// Server functions

inline int WSAinit(){
    return 0;
}

socktype makeServerSocket(){

    printf("Make server socket\n");
    socktype ListenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ListenSock < 0){
        printf("Making socket failed! program aborting");
        exit(1);
    }

    return ListenSock;
}

socktype bindServerSocket(socktype ListenSock){

    struct sockaddr_in SockAdrr;

    memset((char *) &SockAdrr, 0, sizeof(SockAdrr));

    SockAdrr.sin_family =  AF_INET;
    SockAdrr.sin_port = htons(PORT);
    SockAdrr.sin_addr.s_addr = INADDR_ANY;
    
    if (bind(ListenSock, (const struct sockaddr *) &SockAdrr, sizeof(SockAdrr)) < 0){
        printf("Binding socket failed! program aborting...\n");
        exit(1);
    }

    printf("Listening port %d...\n", PORT);
    listen(ListenSock, MAXCON);

    return ListenSock;
}

socktype createConnectionServer(socktype ListenSock){

    socktype ClientSock;
    struct sockaddr_in  clientAddr;
    int nSize = sizeof(clientAddr);
    ClientSock = accept(ListenSock, (struct sockaddr*) &clientAddr, &nSize);

    printf("Accept connection");
    if (ClientSock < 0){
        printf("Accept failed\n");
        return 1;
    }

    // try do nto close socket

    return ClientSock;
}

socktype proccesServer(socktype ClientSock){
    char buffer[BUFFLEN];
    int bufflen = BUFFLEN;

    int res = read(ClientSock, buffer, bufflen, 0);
    
    while (res > 0){
        printf("--------------------------------\nBytes recieved : %d B\n", res);
       
        MouseData * recvData = (MouseData*) buffer;       
        printf("X%d Y%d %s %s\n", recvData->x, recvData->y, 
                    (recvData->LKM ? "LKM":" "),
                    (recvData->RKM ? "RKM":" ")); 

        memset(buffer, 0, BUFFLEN);

        res = read(ClientSock, buffer, bufflen, 0);
    }
    
    printf ("Connection clossed");

    return ClientSock;
}

int closeConnectionServer(socktype ClientSock){
    
    printf("Close connection\n");
    if (shutdown(ClientSock, SHUT_RD) < 0){
        printf("Shutdown failed\n");
        return 1;
    }
    
    return 0;
}

inline int cleanupServer(socktype ClientSock){
    return 0;
}