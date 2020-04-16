#include "../head.h"
/* Header include windows inmplemntation */

// declaration mouse struct
struct MouseData;

/* Server functions */

// Initialize Winsock2 (also use for Client init)
int WSAinit();
SOCKET makeServerSocket();

// Bind server socket with server address
SOCKET bindServerSocket(SOCKET ListenSock);
// Accept connection from client (Creating client socket for recieving data)
SOCKET createConnectionServer(SOCKET ListenSock);
// Main process loop for Server
SOCKET proccesServer(SOCKET ClientSock);

int closeConnectionServer(SOCKET ClientSock);
// Close Winsock2
int cleanupServer(SOCKET ClientSock);


/* Client functions */

// Main process loop for Client
SOCKET processClientSocket(const char * addr, short port);
// Close socket by client's side and deactivate Winsock2
void cleanupClient(SOCKET ClientSock);

/* Main function for mouse (buf contains MouseData structure packed in buffer "char[]")
return sizeof packed data in bytes*/
int getMouseInfo(char * buf);

// Functions that runs in threads
// Functions for evaluate position of cursor
unsigned __stdcall getMousePosThread(void * params);
// Functions for evaluate and pressed button
unsigned __stdcall getMouseClickThread(void * params);

// Spy mode
void StealthMode();