#include "head.h"

SOCKET makeServerSocket();

SOCKET bindServerSocket(SOCKET ListenSock);

SOCKET createConnectionServer(SOCKET ListenSock);

SOCKET proccesServer(SOCKET ClientSock);

int closeConnectionServer(SOCKET ClientSock);

int cleanupServer(SOCKET ClientSock);

void genMouseInfo();