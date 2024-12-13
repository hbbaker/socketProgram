#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

typedef struct
{
    int intValue;
    char charValue;
    float floatValue;
} Data;

int main()
{
    int clientSock;
    struct sockaddr_in serverAddr;
    Data data;

    clientSock = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSock == -1)
    {
        perror("Client Socket creation failed...");
        exit(-1);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = inet_addr("10.0.0.126");

    if (connect(clientSock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
    {
        perror("Connection failed...");
        close(clientSock);
        exit(-1);
    }

    recv(clientSock, &data, sizeof(data), 0);
    printf("Recieved data from Server:\n Int: %d, Char: %c, Float: %.2f\n");

    close(clientSock);

    return 0;
}