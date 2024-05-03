#pragma once

#include <stdio.h> 
#include <stdlib.h>
#include <inttypes.h>
#include <arpa/inet.h>

#define BUFSZ 1024
#define DRIVER_NOT_FOUND "driver_not_found"
#define DRIVER_FOUND "driver_found"
#define REJECTED 0 
#define ACCEPTED 1 
#define EXIT 0 
#define REQUEST_RIDE "crequest"

typedef struct{ 
    double latitude; 
    double longitude; 
} Coordinate; 

void logexit(const char *msg);
int addrparse(const char *addrstr, const char *portstr, struct sockaddr_storage *storage); 
void addrtostr(const struct sockaddr *addr, char *str, size_t strsize); 
int server_sockaddr_init(const char *proto, const char *portstr, struct sockaddr_storage *storage);
double calculateDistance(Coordinate coord1, Coordinate coord2)
