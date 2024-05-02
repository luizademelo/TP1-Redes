#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "common.h"


#define BUFSZ 1024

typedef struct{ 
    double latitude; 
    double longitude; 
} Coordinate; 


int main(int argc, char **argv){
    if(argc < 3){

    }

    struct sockaddr_storage storage; 



    if(0 != addrparse(argv[1], argv[2], &storage)){

    }

    int client_socket = socket(storage.ss_family, SOCK_STREAM, 0); 
    if(client_socket == -1){
        logexit("socket"); 
    }

    struct sockaddr *addr = (struct sockaddr *) (&storage); 
    if(0 != connect(client_socket, addr, sizeof(storage))){

    }

    if(0 != connect(client_socket, addr, sizeof(addr))){
        logexit("connect"); 
    }

    char addrstr[BUFSZ]; 
    addrtostr(addr, addrstr, BUFSZ); 

    char buf[BUFSZ]; 
    memset(buf , 0, BUFSZ); 
    fgets(buf, BUFSZ-1, stdin); 

    int count = send(client_socket, buf, strlen(buf)+1, 0); 
    if(count != strlen(buf)+1){
        logexit("send");
    }

    memset(buf, 0, BUFSZ); 
    unsigned total = 0; 
    while(1){
        count = recv(client_socket, buf+total, BUFSZ-total, 0); 
        if(count == 0){
            // connection terminated
            break; 
        }
        total += count; 
    }

    close(client_socket); 

    exit(EXIT_SUCCESS); 
}