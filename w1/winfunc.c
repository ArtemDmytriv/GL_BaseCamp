#include "winfunc.h"

// Server

int WSAinit(){
    WSADATA wsaData;
    printf("Initialising WinSock...\n");
    if (WSAStartup(WINSOCK_VERSION, &wsaData)){
        printf("WinSock init failed!\n ");
        exit(1);
    }
    else{
        printf("WinSock init succeed\n");
    }
}

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

// Client

SOCKET processClientSocket(const char * chaddr, short port){

    SOCKET sock = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP);
    SOCKADDR_IN addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(chaddr);

    if (connect (sock, (SOCKADDR *)&addr, sizeof(addr)) != SOCKET_ERROR){
        char buff[BUFFLEN];

        for (int i = 0; i < 10; ++i){
            // test func

            getMouseInfo(buff);

            send(sock, buff, strlen(buff), 0);
        
            //printf("Send : %s", buff);

        }
    }
    
    return sock;
}

int cleanupClient(SOCKET ClientSock){
    printf("Cleanup\n");
    closesocket(ClientSock);
    WSACleanup();
    
    return 0;
}

void getMouseInfo(char * buf){

    memset(buf, 0, BUFFLEN);

    POINT coor;
    int Rclicks = 0, Lclicks = 0;

    GetCursorPos(&coor);
    Sleep(500);

    //beginthreadex();

    sprintf(buf, "%d %d : %d %d", coor.x, coor.y, Lclicks, Rclicks);
}


// void WINAPI getMouseClickThread(int* kL, int * kR)
// {
//    //Check the mouse left button is pressed or not
//    while (1){
//     if ((GetKeyState(VK_LBUTTON) & 0x80) != 0)
//     {
//         *kL += 1;
//         printf("LButton pressed\n");
//     }
//     //Check the mouse right button is pressed or not
//     if ((GetKeyState(VK_RBUTTON) & 0x80) != 0)
//     {
//         *kR += 1;
//         printf("RButton pressed\n");
//     }
//    }
// }