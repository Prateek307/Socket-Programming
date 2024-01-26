#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

int main()
{
    WSADATA wsa;
    SOCKET s, new_socket;
    struct sockaddr_in server, client;
    int c, recv_size;
    char msg[100];
    char client_reply[2000];

    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }

    printf("Initialised.\n");

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d", WSAGetLastError());
        return 1;
    }

    printf("Socket created.\n");
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    if (bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d", WSAGetLastError());
        return 1;
    }

    puts("Bind done");

    listen(s, 3);

    puts("Waiting for incoming connections...");

    c = sizeof(struct sockaddr_in);
    new_socket = accept(s, (struct sockaddr *)&client, &c);
    if (new_socket == INVALID_SOCKET)
    {
        printf("accept failed with error code : %d", WSAGetLastError());
        return 1;
    }

    puts("Connection accepted");

    while (1)
    {
        if ((recv_size = recv(new_socket, client_reply, sizeof(client_reply), 0)) == SOCKET_ERROR)
        {
            puts("recv failed");
            break;
        }
        else if (recv_size == 0)
        {
            puts("Connection closed by client");
            break;
        }
        else
        {
            client_reply[recv_size] = '\0';
            puts(client_reply);

            printf("Me: ");
            gets(msg);

            send(new_socket, msg, strlen(msg), 0);
        }
    }

    closesocket(s);
    closesocket(new_socket);
    WSACleanup();

    return 0;
}   