#include "winfunc.h"
typedef struct MouseData{
    char RKM;
    char LKM;
    int x;
    int y;
} MouseData;


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
        printf("--------------------------------\nBytes recieved: %d B\n", res);
       
        MouseData * recvData = (MouseData*) buffer;       
        printf("X%d Y%d %s %s\n", recvData->x, recvData->y, 
                    (recvData->LKM ? "LKM":" "),
                    (recvData->RKM ? "RKM":" ")); 

        memset(buffer, 0, BUFFLEN);

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
            
            MouseData * recvData = (MouseData*) buff;       
            printf("X%d Y%d %s %s\n", recvData->x, recvData->y, 
                    (recvData->LKM != 0 ? "LKM":" "),
                    (recvData->RKM != 0 ? "RKM":" ")); 
            
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


static HANDLE event;

void getMouseInfo(char * buf){
    printf("LOG: Start getMouseInfo\n");

    memset(buf, 0, BUFFLEN);

    typedef struct cl{
        char right;
        char left;
    } cl;
    

    POINT coor;
    cl clicks = {0, 0};

    event = CreateEvent(NULL, TRUE, FALSE, NULL);
 
    HANDLE t1 = (HANDLE)_beginthreadex(NULL, 0, getMousePosThread, (void*)&coor, 0, NULL);
    HANDLE t2 = (HANDLE)_beginthreadex(NULL, 0, getMouseClickThread, (void*)&clicks, 0, NULL);

    Sleep(PAUSE);

    SetEvent(event);

    CloseHandle(event);
    CloseHandle(t1);
    CloseHandle(t2);

    MouseData data = {clicks.right, clicks.left, coor.x, coor.y };

    memcpy(buf, &data, sizeof(data));
    printf("LOG: End getMouseInfo\n");
}

unsigned __stdcall getMousePosThread(void * params){
    
    LPPOINT res = (LPPOINT)params;
    GetCursorPos(res);

    printf("POS: %d, %d\n", (*res).x, (*res).y);

    return 0;
}

unsigned __stdcall getMouseClickThread(void * params){

    char * wasPressedL = (char*)params;
    char * wasPressedR = (char*)params + 1;

    while(WaitForSingleObject(event, 0) != WAIT_OBJECT_0){
        
        if ((GetKeyState(VK_LBUTTON) & 0x80) != 0 && !(*wasPressedL))
        {
            (*wasPressedL) = 1;
            printf("LButton pressed\n");
        }
        //Check the mouse right button is pressed or not
        if ((GetKeyState(VK_RBUTTON) & 0x80) != 0 && !(*wasPressedR))
        {
            (*wasPressedR) = 1;
            printf("RButton pressed\n");
        }

    }
    
    return 0;
}