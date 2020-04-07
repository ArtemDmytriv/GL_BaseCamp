#include "head.h"

int main(int argc, char ** argv){
    
    // Init WinApi 
    WSAinit();

    SOCKET servSock = makeServerSocket();

    servSock = bindServerSocket(servSock);

    SOCKET clienSock = createConnectionServer(servSock);

    clienSock = proccesServer(clienSock);

    closeConnectionServer(clienSock);

    cleanupServer(clienSock);
    
    return 0;
}