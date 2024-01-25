#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <winsock2.h>
#include <time.h>
#pragma comment(lib, "ws2_32.lib")
int balance = 1000;
int main()
{
    WSADATA wsa;
    SOCKET s, new_socket;
    struct sockaddr_in server, client;
    int c, recv_size;
    char msg[100];
    char client_reply[2000];

    char ip_address[20];
    int port;

    printf("Enter IP Address: ");
    scanf("%s", ip_address);

    printf("Enter Port Number: ");
    scanf("%d", &port);

    printf("Installing");

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

    server.sin_addr.s_addr = inet_addr(ip_address);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

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

            if (strcmp(client_reply, "1") == 0)
            {
                char buffer[1000];
                sprintf(buffer, "%d", balance);
                send(new_socket, buffer, sizeof(buffer), 0);
            }

            if (strcmp(client_reply, "2") == 0)
            {
                char buffer[1000];
                strcpy(buffer, "Enter the amount to be deposited:");
                send(new_socket, buffer, sizeof(buffer), 0);

                // amount sent by the client
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
                    int amount = atoi(client_reply);
                    balance += amount;
                    strcpy(buffer, "Amount deposited Successfully");
                    send(new_socket, buffer, sizeof(buffer), 0);
                }
            }

            if (strcmp(client_reply, "3") == 0)
            {
                char buffer[1000];
                strcpy(buffer, "Enter the amount you want to withdraw:");
                send(new_socket, buffer, sizeof(buffer), 0);

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
                    int amount = atoi(client_reply);
                    if (amount <= balance)
                    {
                        balance -= amount;
                        strcpy(buffer, "Cash withdrawl Successfull");
                        send(new_socket, buffer, sizeof(buffer), 0);
                    }
                    else
                    {
                        strcpy(buffer, "Insufficient balance");
                        send(new_socket, buffer, sizeof(buffer), 0);
                    }
                }
            }
        }
    }

    closesocket(s);
    closesocket(new_socket);
    WSACleanup();

    return 0;
}
