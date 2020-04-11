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

    printf("Accept connection\n");
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

    int res = read(ClientSock, buffer, bufflen);
    
    while (res > 0){
        printf("--------------------------------\nBytes recieved : %d B\n", res);
       
        MouseData * recvData = (MouseData*) buffer;       
        printf("X%d Y%d %s %s\n", recvData->x, recvData->y, 
                    (recvData->LKM ? "LKM":" "),
                    (recvData->RKM ? "RKM":" ")); 

        memset(buffer, 0, BUFFLEN);

        res = read(ClientSock, buffer, bufflen);
    }
    
    printf ("Connection clossed\n");

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

//Client
socktype processClientSocket(const char * chaddr, short port){

    socktype sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(chaddr);

    if (connect(sock, (const struct sockaddr *)&addr, sizeof(addr))){
        printf("Connecting succesful\n");

        char buff[BUFFLEN];

        for (int i = 0; i < LOOPCOUNT; ++i){
            getMouseInfo(buff);

            MouseData * recvData = (MouseData*) buff;
            printf("X%d Y%d %s %s\n", recvData->x, recvData->y, 
                    (recvData->LKM != 0 ? "LKM":" "),
                    (recvData->RKM != 0 ? "RKM":" ")); 
            
            write(sock, buff, BUFFLEN);
        
            memset(buff, 0, BUFFLEN);
        }
    }

    return sock;
}

int cleanupClient(socktype ClientSock){
    printf("Cleanup\n");
    shutdown(ClientSock, SHUT_RDWR);

    return 0;
}

int getMouseInfo(char * buff){

    sleep(PAUSE);

    MouseData data = {1, 0, 243, 213};
    memcpy(buff, &data, sizeof(data));

    return sizeof(data); 
}