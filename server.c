#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void usage(int argc, char **argv)
{
    printf("usage: %s <ipv4|ipv6> <server port>\n", argv[0]);
    printf("example: %s ipv4 51511\n", argv[0]);
    exit(EXIT_FAILURE);
}

void printServerWaiting()
{
    printf("----------------------------------------------\n");
    printf("| $ Aguardando solicitação.                  |\n");
    printf("| $                                          |\n");
    printf("----------------------------------------------\n");
}

void printAvailableRide()
{
    printf("----------------------------------------------\n");
    printf("| $ Corrida disponível:                      |\n");
    printf("| $ 0 - Recusar                              |\n");
    printf("| $ 1 - Aceitar                              |\n");
    printf("| $                                          |\n");
    printf("----------------------------------------------\n");
}

int getAcceptRideOption(char *buf, int csock)
{
    int option;
    scanf("%d", &option);

    if (option == REJECTED)
    {
        strcpy(buf, DRIVER_NOT_FOUND);
        send(csock, buf, strlen(buf) + 1, 0);
        close(csock);
    }
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        usage(argc, argv);
    }

    struct sockaddr_storage storage;

    if (0 != server_sockaddr_init(argv[1], argv[2], &storage))
    {
    }

    int server_socket = socket(storage.ss_family, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        logexit("socket");
    }

    struct sockaddr *addr = (struct sockaddr *)(&storage);

    if (0 != bind(server_socket, addr, sizeof(storage)))
    {
        logexit("bind");
    }

    if (0 != listen(server_socket, 10))
    {
        logexit("listen");
    }

    while (1)
    {

        printServerWaiting();

        char buf[BUFSZ];
        struct sockaddr_storage cstorage;
        struct sockaddr *caddr = (struct sockaddr *)(&cstorage);
        socklen_t caddrlen = sizeof(cstorage);

        int csock = accept(server_socket, caddr, &caddrlen);
        if (csock == -1)
        {
            logexit("accept");
        }

        char caddrstr[BUFSZ];
        addrtostr(caddr, caddrstr, BUFSZ);

        size_t count = recv(csock, buf, BUFSZ, 0);

        printAvailableRide();

        if (getAcceptRideOption(buf, csock) == REJECTED)
        {
            strcpy(buf, DRIVER_NOT_FOUND);
            send(csock, buf, strlen(buf) + 1, 0);
            close(csock);
            continue;
        }

        printf("accepted ride\n"); 

        close(csock);
    }

    close(server_socket);
    exit(EXIT_SUCCESS);
}