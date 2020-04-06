#include "head.h"

SOCKET makeServerSocket();

SOCKET bindServerSocket(SOCKET ListenSock, unsigned short Port);

SOCKET createConnectionServer(SOCKET ListenSock);

int closeConnectionServer(SOCKET ClientSock);

SOCKET proccesServer(SOCKET ClientSock);

int cleanupServer(SOCKET ClientSock);

void genMouseInfo();