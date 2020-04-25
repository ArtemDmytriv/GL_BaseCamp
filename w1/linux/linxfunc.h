#include "../head.h"

typedef int socktype;
/* Header include windows inmplemntation */

// declaration mouse struct
struct MouseData;

/* Server functions */

// not use
int WSAinit();

// make socket for server
socktype makeServerSocket();

// Bind server socket with server address
socktype bindServerSocket(socktype ListenSock);
// Accept connection from client (Creating client socket for recieving data)
socktype createConnectionServer(socktype ListenSock);
// Main process loop for Server
socktype proccesServer(socktype ClientSock);

int closeConnectionServer(socktype ClientSock);
// Close Winsock2
int cleanupServer(socktype ClientSock);


/* Client functions */

// Main process loop for Client
socktype processClientSocket(const char * addr, short port);
// Close socket by client's side and deactivate Winsock2
int cleanupClient(socktype ClientSock);


/* Main function for mouse (buf contains MouseData structure packed in buffer "char[]")
return sizeof packed data in bytes*/
int getMouseInfo(char * buf);

// Functions for evaluate button position
void* getMousePosThread(void * params);

// Functions for evaluate and pressed button
void* getMouseClickThread(void * params);

// Spy mode
void StealthMode();