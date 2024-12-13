#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct
{
    int intValue;
    char charValue;
    float floatValue;
} Data;

void modData(Data *data)
{
    data->intValue *= 2;
    data->charValue = (data->charValue == 'z') ? 'a' : data->charValue + 1;
    data->floatValue += 1.0;
}

int main()
{
    int serverSock, clientsock1, clientsock2;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrSize = sizeof(clientAddr);
    Data data;

    serverSock = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSock == -1)
    {
        perror("opening socket...");
        exit(-1);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(serverSock, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr_in)) == -1)
    {
        perror("Binding failed");
        close(serverSock);
        exit(-1);
    }

    if (listen(serverSock, 2) < 0)
    {
        perror("Unable to listen");
        close(serverSock);
        exit(-1);
    }

    printf("Server running on port 8080...\n");

    clientsock1 = accept(serverSock, (struct sockaddr *)&clientAddr, &addrSize);
    if (clientsock1 == -1)
    {
        perror("Accept Client 1 Failed...");
        close(serverSock);
        exit(-1);
    }

    printf("Connected to client1!");

    close(serverSock);
    printf("Closing Server...\n");
}