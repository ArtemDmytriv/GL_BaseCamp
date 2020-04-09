#include "head.h"

int main(int argc, char ** argv){

    const char * chaddr = "127.0.0.1"; // use local adress

    WSAinit();

    SOCKET sock = processClientSocket(chaddr, PORT);

    cleanupClient(sock);

    return 0;
}