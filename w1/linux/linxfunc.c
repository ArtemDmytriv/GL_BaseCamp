#include "linxfunc.h"

typedef struct MouseData{
    char LKM;
    char RKM;
    int x;
    int y;
} MouseData;

const char *pDevice = "/dev/input/mice";

// Server functions

inline int WSAinit(){
    return 0;
}

socktype makeServerSocket(){

    printf("Make server socket\n");
    socktype ListenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ListenSock < 0){
        printf("Making socket failed! program aborting");
        exit(1);
    }

    return ListenSock;
}

socktype bindServerSocket(socktype ListenSock){

    struct sockaddr_in SockAdrr;

    memset((char *) &SockAdrr, 0, sizeof(SockAdrr));

    SockAdrr.sin_family =  AF_INET;
    SockAdrr.sin_port = htons(PORT);
    SockAdrr.sin_addr.s_addr = INADDR_ANY;
    
    if (bind(ListenSock, (const struct sockaddr *) &SockAdrr, sizeof(SockAdrr)) < 0){
        printf("Binding socket failed! program aborting...\n");
        exit(1);
    }

    printf("Listening port %d...\n", PORT);
    listen(ListenSock, MAXCON);

    return ListenSock;
}

socktype createConnectionServer(socktype ListenSock){

    socktype ClientSock;
    struct sockaddr_in  clientAddr;
    int nSize = sizeof(clientAddr);
    ClientSock = accept(ListenSock, (struct sockaddr*) &clientAddr, &nSize);

    printf("Accept connection\n");
    if (ClientSock < 0){
        printf("Accept failed\n");
        return 1;
    }

    // try do nto close socket

    return ClientSock;
}

socktype proccesServer(socktype ClientSock){
    char buffer[BUFFLEN];
    
    FILE* fout;

    // make file for writing data
    time_t rawtime;
    struct tm * ptm;

    time ( &rawtime );
    ptm = localtime ( &rawtime );
    char file_name[64] = {0}; 
    sprintf(file_name, "data/DATA(%02d_%02d)%02d_%02d_%02d.txt", ptm->tm_mday, ptm->tm_mon, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);

    fout = fopen(file_name, "w");
    if (fout == NULL){
        printf("\nCannot create file\n");
    }

    char output[256];
    int bufflen = BUFFLEN;
    int res = read(ClientSock, buffer, bufflen);
    
    while (res > 0){
        printf("--------------------------------\nBytes recieved : %d B\n", res);
       
        MouseData * recvData = (MouseData*) buffer;       
        sprintf(output, "X%d Y%d %s %s\n", recvData->x, recvData->y, 
                    (recvData->LKM ? "LKM":" "),
                    (recvData->RKM ? "RKM":" ")); 
        
        // output in console
        puts(output);
        // output in file
        fwrite(output, sizeof(char), strlen(output), fout);

        fflush(fout);
        memset(buffer, 0, BUFFLEN);

        res = read(ClientSock, buffer, bufflen);
    }
    
    
    fclose(fout);
    printf ("Connection clossed\n");

    return ClientSock;
}

int closeConnectionServer(socktype ClientSock){
    
    printf("Close connection\n");
    if (shutdown(ClientSock, SHUT_RD) < 0){
        printf("Shutdown failed\n");
        return 1;
    }

    return 0;
}

int cleanupServer(socktype ClientSock){
    return 0;
}

//Client
socktype processClientSocket(const char * chaddr, short port){

    socktype sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in addr;
    struct hostent *server;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if(inet_pton(AF_INET, chaddr, &addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        exit(1); 
    } 
    printf("Address was converted succesfuly\n");


    if (connect(sock, (const struct sockaddr *)&addr, sizeof(addr)) < 0){
        printf("Connection failed\n");
        exit(1);
    }
    printf("Connection complete\n");

    char buff[BUFFLEN];

    for (int i = 0; i < LOOPCOUNT; ++i){
        getMouseInfo(buff);

        MouseData * recvData = (MouseData*) buff;
        printf("X%d Y%d %s %s\n", recvData->x, recvData->y, 
                (recvData->LKM != 0 ? "LKM":" "),
                (recvData->RKM != 0 ? "RKM":" ")); 
        
        send(sock, buff, BUFFLEN, 0);
        
        memset(buff, 0, BUFFLEN);
    }

    return sock;
}

int cleanupClient(socktype ClientSock){
    printf("Cleanup\n");
    shutdown(ClientSock, SHUT_RDWR);
    return 0;
}


static int _XlibErrorHandler(Display *display, XErrorEvent *event) {
    fprintf(stderr, "An error occured detecting the mouse position\n");
    return True;
}

int getMouseInfo(char * buff){

    pthread_t t1, t2;

    MouseData data = {0,0,0,0};

    pthread_create(&t2, NULL, getMouseClickThread, &data);
    pthread_create(&t1, NULL, getMousePosThread, &data);
    

    pthread_join(t1, NULL);
    pthread_cancel(t2);

    pthread_join(t2, NULL);

    memcpy(buff, &data, sizeof(data));

    return sizeof(data);
}

void* getMousePosThread(void * params){
    //printf(">In %s\n",__func__);
    
    int number_of_screens, i;
    Bool result;
    Window *root_windows;
    Window window_returned;
    int root_x, root_y;
    int win_x, win_y;
    unsigned int mask_return;

    Display *display = XOpenDisplay(NULL);

    XSetErrorHandler(_XlibErrorHandler);
    number_of_screens = XScreenCount(display);
  
    root_windows = malloc(sizeof(Window) * number_of_screens);
    for (i = 0; i < number_of_screens; i++) {
        root_windows[i] = XRootWindow(display, i);
    }
 
    
    for (i = 0; i < number_of_screens; i++) {
        result = XQueryPointer(display, root_windows[i], &window_returned,
                    &window_returned, &root_x, &root_y, &win_x, &win_y,
                    &mask_return);
        if (result == 1) {
            break;
        }
    }
 
    free(root_windows);

    MouseData * md = (MouseData*)params;
    md->x = root_x;
    md->y = root_y;

    usleep(1000*PAUSE);

    //printf("<In %s\n",__func__);
}

void* getMouseClickThread(void * params){
    
    MouseData * md = (MouseData*)params;
    int fd, bytes;
    unsigned char data[3];

    // Open Mouse
    fd = open(pDevice, O_RDWR);
    if(fd == -1)
    {
        printf("ERROR Opening %s\n", pDevice);
    }

    int left, right;
    
    while(1)
    {
        // Read Mouse     
        bytes = read(fd, data, sizeof(data));

        if(bytes > 0)
        {
            if (data[0] & 0x1){
                md->LKM = 1;
            }
            if (data[0] & 0x2){
                md->RKM = 1;
            }   
        }   
    }

}