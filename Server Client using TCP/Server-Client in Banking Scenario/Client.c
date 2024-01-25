#include <stdio.h>
#include <conio.h>
#include <winsock2.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#pragma comment(lib, "ws2_32.lib")

void timer(int);

int main()
{
    WSADATA wsa;
    SOCKET sck;
    struct sockaddr_in ip_info;
    char server_reply[2000];
    int recv_size;
    char msg[100];

    printf("Installing");
    for (int cnt = 1; cnt <= 3; cnt++)
    {
        timer(1);
        printf(".");
    }

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        printf("WSA error\n");
    else if ((sck = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
        printf("Socket error\n");
    else
    {
        ip_info.sin_addr.s_addr = inet_addr("127.0.0.1");
        ip_info.sin_family = AF_INET;
        ip_info.sin_port = htons(8888);
    }

    if (connect(sck, (struct sockaddr *)&ip_info, sizeof(ip_info)) < 0)
        printf("\nNot connected\n");
    else
        printf("\nSession is up\n");

    int choice = 0;
    while (1)
    {
        printf("\n\nEnter 1 for balance enquiry\n");
        printf("Enter 2 for cash deposit\n");
        printf("Enter 3 for cash withdrawl\n");
        printf("Enter 4 to exit\n");
        printf("Enter your choice :\n");
        scanf("%d", &choice);
        if (choice == 1)
        {
            // sending to the server
            char buffer[1000];
            sprintf(buffer, "%d", choice);
            send(sck, buffer, sizeof(buffer), 0);

            // receiving from the server
            if ((recv_size = recv(sck, server_reply, sizeof(server_reply), 0)) == SOCKET_ERROR)
            {
                puts("recv failed");
                break;
            }
            else if (recv_size == 0)
            {
                puts("Connection closed by server");
                break;
            }
            else
            {
                server_reply[recv_size] = '\0';
                printf("Bank balance : ");
                puts(server_reply);
            }
        }
        else if (choice == 2)
        {
            char buffer[1000];
            sprintf(buffer, "%d", choice);
            // choice sent to the server
            send(sck, buffer, sizeof(buffer), 0);

            // enter amount : message sent back from the server
            if ((recv_size = recv(sck, server_reply, sizeof(server_reply), 0)) == SOCKET_ERROR)
            {
                puts("recv failed");
                break;
            }
            else
            {
                server_reply[recv_size] = '\0';
                puts(server_reply);
                // amount entered by the user
                int amount;
                scanf("%d", &amount);
                char buffer[1000];
                // amount sent to the server
                itoa(amount, buffer, 10);
                send(sck, buffer, sizeof(buffer), 0);

                // amount deposited and message reply from the server
                if ((recv_size = recv(sck, server_reply, sizeof(server_reply), 0)) == SOCKET_ERROR)
                {
                    puts("recv failed");
                    break;
                }
                else
                {
                    server_reply[recv_size] = '\0';
                    puts(server_reply);
                }
            }
        }
        else if (choice == 3)
        {
            char buffer[1000];
            sprintf(buffer, "%d", choice);
            // choice sent to the server
            send(sck, buffer, sizeof(buffer), 0);

            // enter amount to be withdraw : message sent back from the server
            if ((recv_size = recv(sck, server_reply, sizeof(server_reply), 0)) == SOCKET_ERROR)
            {
                puts("recv failed");
                break;
            }
            else
            {
                server_reply[recv_size] = '\0';
                puts(server_reply);
                // amount entered by the user
                int amount;
                scanf("%d", &amount);
                char buffer[1000];
                // amount sent to the server
                itoa(amount, buffer, 10);
                send(sck, buffer, sizeof(buffer), 0);

                // amount withdrawn and message reply from the server
                if ((recv_size = recv(sck, server_reply, sizeof(server_reply), 0)) == SOCKET_ERROR)
                {
                    puts("recv failed");
                    break;
                }
                else
                {
                    server_reply[recv_size] = '\0';
                    puts(server_reply);
                }
            }
        }
        else if (choice == 4)
        {
            // char buffer[1000];
            // sprintf(buffer, "%d", choice);
            // // choice sent to the server
            // send(sck, buffer, sizeof(buffer), 0);
            printf("Connection terminated\n");
            break;
        }
        else
        {
            printf("Invalid choice\n");
        }
    }

    closesocket(sck);
    WSACleanup();
    getch();
    return 0;
}

void timer(int sec)
{
    clock_t end;
    end = clock() + sec * CLOCKS_PER_SEC;
    while (clock() <= end)
        ;
}
