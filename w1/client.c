#include "head.h"

int main(int argc, char ** argv){

    const char * chaddr = "127.0.0.1";

    WSADATA wsaData;
    printf("Initialising WinSock...\n");
    if (WSAStartup(WINSOCK_VERSION, &wsaData)){
        printf("WinSock init failed!\n ");
        exit(1);
    }
    else{
        printf("WinSock init succeed\n");
    }

    //
    SOCKET sock = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP);
    SOCKADDR_IN addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr(chaddr);

    if (connect (sock, (SOCKADDR *)&addr, sizeof(addr)) != SOCKET_ERROR){
        char buff[BUFFLEN];

        for (int i = 0; i < 1000; ++i){
            // test func

            getMouseInfo(buff);
            
            send(sock, buff, strlen(buff), 0);
        
            //printf("Send : %s", buff);
            Sleep(500);
        }
    }

    closesocket(sock);

    WSACleanup();

    return 0;
}