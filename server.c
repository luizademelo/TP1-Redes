#include "common.h"
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


#define BUFSZ 1024

typedef struct{ 
    double latitude; 
    double longitude; 
} Coordinate; 


int main(int argc, char **argv){
    if(argc < 3){

    }


    struct sockaddr_storage storage; 

    if(0 != server_sockaddr_init(argv[1], argv[2], &storage)){

    }

    int server_socket = socket(storage.ss_family, SOCK_STREAM, 0); 
    if(server_socket == -1){
        logexit("socket");
    }




    struct sockaddr *addr = (struct sockaddr *) (&storage); 

    if(0 != bind(server_socket, addr, sizeof(storage))){
        logexit("bind");
    }

    if(0 != listen(server_socket, 10)){
        logexit("listen"); 
    }


    while(1){

        struct sockaddr_storage cstorage; 
        struct sockaddr *caddr = (struct sockaddr *)(&cstorage); 
        socklen_t caddrlen = sizeof(cstorage); 

        int csock = accept(server_socket, caddr, &caddrlen); 
        if(csock == -1){
            logexit("accept"); 
        }

        char caddrstr[BUFSZ]; 
        addrtostr(caddr, caddrstr, BUFSZ); 

        char buf[BUFSZ]; 
        size_t count = recv(csock, buf, BUFSZ, 0); 

        sprintf(buf, "remote endpoint: %s\n", caddrstr); 
        send(csock, buf, strlen(buf)+1, 0); 
        close(csock); 

    }

    close(server_socket); 
    exit(EXIT_SUCCESS); 
}