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
    
    FILE* fout;

    // make file for writing data
    time_t rawtime;
    struct tm * ptm;

    time ( &rawtime );
    ptm = localtime ( &rawtime );
    char file_name[64] = {0}; 
    sprintf(file_name, "data/DATA_%02d:%02d:%02d.txt", ptm->tm_hour, ptm->tm_min, ptm->tm_sec);

    fout = fopen(file_name, "w");
    if (fout == NULL){
        printf("\nCannot create file\n");
    }

    char output[256];
    int bufflen = BUFFLEN;
    int res = read(ClientSock, buffer, bufflen);
    
    while (res > 0){
        printf("--------------------------------\nBytes recieved : %d B\n", res);
       
        MouseData * recvData = (MouseData*) buffer;       
        sprintf(output, "X%d Y%d %s %s\n", recvData->x, recvData->y, 
                    (recvData->LKM ? "LKM":" "),
                    (recvData->RKM ? "RKM":" ")); 
        
        // output in console
        puts(output);
        // output in file
        fwrite(output, sizeof(char), strlen(output), fout);

        memset(buffer, 0, BUFFLEN);

        res = read(ClientSock, buffer, bufflen);
    }
    
    
    fclose(fout);
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

int cleanupServer(socktype ClientSock){
    return 0;
}

//Client
socktype processClientSocket(const char * chaddr, short port){

    socktype sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in addr;
    struct hostent *server;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if(inet_pton(AF_INET, chaddr, &addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        exit(1); 
    } 
    printf("Address was converted succesfuly\n");


    if (connect(sock, (const struct sockaddr *)&addr, sizeof(addr)) < 0){
        printf("Connection failed\n");
        exit(1);
    }
    printf("Connection complete\n");

    char buff[BUFFLEN];

    for (int i = 0; i < LOOPCOUNT; ++i){
        getMouseInfo(buff);

        MouseData * recvData = (MouseData*) buff;
        printf("X%d Y%d %s %s\n", recvData->x, recvData->y, 
                (recvData->LKM != 0 ? "LKM":" "),
                (recvData->RKM != 0 ? "RKM":" ")); 
        
        send(sock, buff, BUFFLEN, 0);
        
        memset(buff, 0, BUFFLEN);
    }

    return sock;
}

int cleanupClient(socktype ClientSock){
    printf("Cleanup\n");
    shutdown(ClientSock, SHUT_RDWR);
    return 0;
}

// I haven't done it yet (hard coded)
int getMouseInfo(char * buff){
    //printf(">In %s\n",__func__);
    int x = 0, y = 0;

    MouseData data = {0, 0, x, y};
    memcpy(buff, &data, sizeof(data));

    usleep(1000*PAUSE);

    
    //printf("<In %s\n",__func__);
    return sizeof(data); 
}