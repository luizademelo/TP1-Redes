#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "common.h"

Coordinate coordCli = {-19.9391, -43.9398};


void usage(int argc, char **argv)
{
    printf("usage: %s <server IP> <server port>\n", argv[0]);
    printf("example: %s 127.0.0.1 51511\n", argv[0]);
    exit(EXIT_FAILURE);
}

void printClientInitialMenu()
{
    printf("----------------------------------------------\n");
    printf("| $ 0 - Sair\n");
    printf("| $ 1 - Solicitar corrida\n");
    printf("----------------------------------------------\n");
}

void printDriverNotFoundMenu()
{
    printf("----------------------------------------------\n");
    printf("| $ Nao foi encontrado um motorista\n");
    printf("| $ 0 - Sair\n");
    printf("| $ 1 - Solicitar corrida\n");
    printf("----------------------------------------------\n");
}

int getClientInitialMenuOption()
{
    int option;
    scanf("%d", &option);
    return option;
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
    }

    struct sockaddr_storage storage;

    if (0 != addrparse(argv[2], argv[3], &storage))
    {
    }

    int client_socket = socket(storage.ss_family, SOCK_STREAM, 0);
    if (client_socket == -1)
    {
        logexit("socket");
    }

    struct sockaddr *addr = (struct sockaddr *)(&storage);



    while (1)
    {
        printClientInitialMenu();
        int option = getClientInitialMenuOption();

        if (option == EXIT)
        {
            close(client_socket);
            exit(EXIT_SUCCESS);
        }

        if (0 != connect(client_socket, addr, sizeof(storage)))
        {
            logexit("connect");
        }

        char addrstr[BUFSZ];
        char buf[BUFSZ];

        addrtostr(addr, addrstr, BUFSZ);
        memset(buf, 0, BUFSZ);

        strcpy(buf, REQUEST_RIDE); 

        int count = send(client_socket, buf, strlen(buf) + 1, 0);
        if (count != strlen(buf) + 1)
        {
            logexit("send");
        }

        memset(buf, 0, BUFSZ);

        count = recv(client_socket, buf, BUFSZ, 0);
        if (count <= 0)
        {
            // connection terminated
            printf("conexao terminada\n");
            break;
        }

        if (strcmp(buf, DRIVER_NOT_FOUND) == 0)
        {
            printDriverNotFoundMenu();
            int option = getClientInitialMenuOption();
            if (option == EXIT)
            {
                close(client_socket);
                exit(EXIT_SUCCESS);
            }

            // if (0 != connect(client_socket, addr, sizeof(storage)))
            // {
            //     logexit("connect");
            // }

            // int count = send(client_socket, buf, strlen(buf) + 1, 0);
            // if (count != strlen(buf) + 1)
            // {
            //     logexit("send");
            // }
        }

        // Driver found

        send(client_socket, &coordCli, sizeof(coordCli), 0); 

        double dist; 
        while(0 < recv(client_socket, &dist, sizeof(dist), 0)){
            printf("motorista a %lfm\n", dist); 
        }


        printf("O motorista chegou.\n"); 
        break; 
    }

    close(client_socket);
    exit(EXIT_SUCCESS);
}