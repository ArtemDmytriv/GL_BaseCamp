#include "head.h"

SOCKET makeServerSocket();

SOCKET bindServerSocket(SOCKET ListenSock, unsigned short Port);

SOCKET createСonnectionServer();

int closeConnectionServer(SOCKET ClientSock);

int cleanupServer(SOCKET ClientSock);

void genMouseInfo();