#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFSZ 1024

void logexit(const char *msg){
    perror(msg); 
    exit(EXIT_FAILURE); 
}


void main(int argc, int **argv){
    if(argc < 3){

    }

    int client_socket = socket(AF_INET, SOCK_STREAM, 0); 
    if(client_socket == -1){
        logexit("socket"); 
    }

    if(0 != connect(client_socket, addr, sizeof(addr))){
        logexit("connect"); 
    }

    close(client_socket); 

    exit(EXIT_SUCCESS); 
}