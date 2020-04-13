#include "head.h"


int main(int argc, char ** argv){
    
    // Init WinApi 
    if (WSAinit()){
        exit(1); // Failure
    }

    socktype servSock = makeServerSocket();

    servSock = bindServerSocket(servSock);

    socktype clienSock = createConnectionServer(servSock);

    clienSock = proccesServer(clienSock);

    if (closeConnectionServer(clienSock)){
        exit(2);
    }

    cleanupServer(clienSock);
    
    return 0;
}