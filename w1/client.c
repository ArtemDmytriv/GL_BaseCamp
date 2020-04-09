#include "head.h"

int main(int argc, char ** argv){
    //StealthMode(); spy mode

    const char * chaddr = "127.0.0.1"; // use local adress

    WSAinit();
    ShowWindow(GetConsoleWindow(), SW_MINIMIZE);

    SOCKET sock = processClientSocket(chaddr, PORT);

    cleanupClient(sock);

    return 0;
}