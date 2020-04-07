#include "head.h"

// Server funcs
int WSAinit();

SOCKET makeServerSocket();

SOCKET bindServerSocket(SOCKET ListenSock);

SOCKET createConnectionServer(SOCKET ListenSock);

SOCKET proccesServer(SOCKET ClientSock);

int closeConnectionServer(SOCKET ClientSock);

int cleanupServer(SOCKET ClientSock);



// Client funcs

SOCKET processClientSocket(const char * addr, short port);

int cleanupClient(SOCKET ClientSock);

void getMouseInfo(char * buf);

// void WINAPI getMouseClickThread(int* kL, int * kR);

