#include "head.h"


int main(int argc, char ** argv){
    
    // Init WinApi 
    WSAinit();

    socktype servSock = makeServerSocket();

    servSock = bindServerSocket(servSock);

    socktype clienSock = createConnectionServer(servSock);

    clienSock = proccesServer(clienSock);

    closeConnectionServer(clienSock);

    cleanupServer(clienSock);
    
    return 0;
}