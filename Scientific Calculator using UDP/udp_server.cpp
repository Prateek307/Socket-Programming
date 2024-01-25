#include <stdio.h>
#include <winsock2.h>
#include <bits/stdc++.h>
#include <string>
#include <cstring>
#include <iostream>
#include<bits/stdc++.h>
#define PORT 19999
using namespace std;
int main()
{
    WSADATA w;
    int nRet = 0;
    SOCKET nSocket, nClientSocket;
    sockaddr_in srv;
    char sbuff[1024];

    nRet = WSAStartup(MAKEWORD(2, 2), &w);
    if (nRet < 0)
    {
        printf("\nCannot initialize socket lib\n");
        return -1;
    }

    nSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (nSocket == INVALID_SOCKET)
    {
        printf("\nCannot initialize listener socket : %d", WSAGetLastError());
        WSACleanup();
        return -1;
    }

    srv.sin_family = AF_INET;
    srv.sin_addr.s_addr = INADDR_ANY;
    srv.sin_port = htons(PORT);
    memset(&(srv.sin_zero), 0, 8);

    nRet = bind(nSocket, (struct sockaddr *)&srv, sizeof(srv));
    if (nRet == SOCKET_ERROR)
    {
        printf("\nCannot bind at port : %d", WSAGetLastError());
        closesocket(nSocket);
        WSACleanup();
        return -1;
    }

    nRet = listen(nSocket, 5);
    if (nRet == SOCKET_ERROR)
    {
        printf("\nCannot listen at port : %d", WSAGetLastError());
        closesocket(nSocket);
        WSACleanup();
        return -1;
    }

    int addrlen = sizeof(srv);
    nClientSocket = accept(nSocket, (struct sockaddr *)&srv, &addrlen);

    if (nClientSocket == INVALID_SOCKET)
    {
        printf("\nCannot accept client at port : %d", WSAGetLastError());
        closesocket(nSocket);
        WSACleanup();
        return -1;
    }

    while (1)
    {
        nRet = recv(nClientSocket, sbuff, sizeof(sbuff), 0);
        if (nRet == SOCKET_ERROR)
        {
            printf("\nCannot receive message from client :\n%d", WSAGetLastError());
            break;
        }
        else if (nRet == 0)
        {
            // Connection closed by the client
            printf("\nConnection closed by the client");
            break;
        }
        if (strcmp(sbuff, "1") == 0)
        {
            char my_str[100];
            nRet = recv(nClientSocket, my_str, sizeof(my_str), 0);
            printf("num1 received : %s\n", my_str);
            int val = stoi(my_str);
            int sum = val;
            nRet = recv(nClientSocket, my_str, sizeof(my_str), 0);
            printf("num2 received : %s\n", my_str);
            int val2 = stoi(my_str);
            sum += val2;
            // sum calculated successfully
            printf("addition is %d\n", sum);

            // now we will send the response back to the server
            string temp = to_string(sum);
            char str[1000];
            strcpy(str, temp.c_str());
            printf("data sending from server = %s\n", str);
            nRet = send(nClientSocket, str, strlen(str), 0);
        }
        if (strcmp(sbuff, "2") == 0)
        {
            char my_str[100];
            nRet = recv(nClientSocket, my_str, sizeof(my_str), 0);
            printf("num1 received : %s\n", my_str);
            int val = stoi(my_str);
            int sum = val;
            nRet = recv(nClientSocket, my_str, sizeof(my_str), 0);
            printf("num2 received : %s\n", my_str);
            int val2 = stoi(my_str);
            sum -= val2;
            // sum calculated successfully
            printf("difference is %d\n", sum);

            // now we will send the response back to the server
            string temp = to_string(sum);
            char str[100];
            strcpy(str, temp.c_str());
            printf("data sending %s\n", str);
            nRet = send(nClientSocket, str, strlen(str), 0);
        }
        if (strcmp(sbuff, "3") == 0)
        {
            char my_str[100];
            nRet = recv(nClientSocket, my_str, sizeof(my_str), 0);
            printf("num1 received: %s", my_str);
            float val = stoi(my_str);
            float sum = val;
            nRet = recv(nClientSocket, my_str, sizeof(my_str), 0);
            printf("num2 received : %s", my_str);
            float val2 = stoi(my_str);
            sum *= val2;
            // sum calculated successfully
            printf("product is %d\n", sum);

            // now we will send the response back to the server
            string temp = to_string(sum);
            char str[100];
            strcpy(str, temp.c_str());
            printf("data sending %s\n", str);
            nRet = send(nClientSocket, str, strlen(str), 0);
        }

        if (strcmp(sbuff, "4") == 0)
        {
            char my_str[100];
            nRet = recv(nClientSocket, my_str, sizeof(my_str), 0);
            printf("num1 received : %s", my_str);
            float val = stoi(my_str);
            float sum = val;
            nRet = recv(nClientSocket, my_str, sizeof(my_str), 0);
            printf("num2 received : %s", my_str);
            float val2 = stoi(my_str);
            sum /= val2;
            // sum calculated successfully
            printf("divison is %d\n", sum);

            // now we will send the response back to the server
            string temp = to_string(sum);
            char str[100];
            strcpy(str, temp.c_str());
            printf("data sending %s\n", str);
            nRet = send(nClientSocket, str, strlen(str), 0);
        }

        if (strcmp(sbuff, "5") == 0)
        {
            char my_str[100];
            nRet = recv(nClientSocket, my_str, sizeof(my_str), 0);
            printf("num1 received : %s\n", my_str);
            int val = stoi(my_str);
            int sum = val;

            //  calculated successfully
            double result = sqrt(sum);

            // now we will send the response back to the server
            string temp = to_string(result);
            char str[1000];
            strcpy(str, temp.c_str());
            printf("data sending from server = %s\n", str);
            nRet = send(nClientSocket, str, strlen(str), 0);
        }

        if (strcmp(sbuff, "6") == 0)
        {
            char my_str[100];
            nRet = recv(nClientSocket, my_str, sizeof(my_str), 0);
            printf("num1 received : %s", my_str);
            int val = stoi(my_str);
            int sum = val;
            nRet = recv(nClientSocket, my_str, sizeof(my_str), 0);
            printf("num2 received : %s", my_str);
            int val2 = stoi(my_str);

            // calculated successfully
            double res = pow(sum, val2);

            // now we will send the response back to the server
            string temp = to_string(res);
            char str[100];
            strcpy(str, temp.c_str());
            printf("data sending %s\n", str);
            nRet = send(nClientSocket, str, strlen(str), 0);
        }

        if (strcmp(sbuff, "7") == 0)
        {
            char my_str[100];
            nRet = recv(nClientSocket, my_str, sizeof(my_str), 0);
            printf("num1 received : %s\n", my_str);
            int val = stoi(my_str);
            int sum = val;

            //  calculated successfully
            double result = sin(sum);

            // now we will send the response back to the server
            string temp = to_string(result);
            char str[1000];
            strcpy(str, temp.c_str());
            printf("data sending from server = %s\n", str);
            nRet = send(nClientSocket, str, strlen(str), 0);
        }

        if (strcmp(sbuff, "8") == 0)
        {
            char my_str[100];
            nRet = recv(nClientSocket, my_str, sizeof(my_str), 0);
            printf("num1 received : %s\n", my_str);
            int val = stoi(my_str);
            int sum = val;

            //  calculated successfully
            double result = cos(sum);

            // now we will send the response back to the server
            string temp = to_string(result);
            char str[1000];
            strcpy(str, temp.c_str());
            printf("data sending from server = %s\n", str);
            nRet = send(nClientSocket, str, strlen(str), 0);
        }

        if (strcmp(sbuff, "9") == 0)
        {
            char my_str[100];
            nRet = recv(nClientSocket, my_str, sizeof(my_str), 0);
            printf("num1 received : %s\n", my_str);
            int val = stoi(my_str);
            int sum = val;

            //  calculated successfully
            double result = tan(sum);

            // now we will send the response back to the server
            string temp = to_string(result);
            char str[1000];
            strcpy(str, temp.c_str());
            printf("data sending from server = %s\n", str);
            nRet = send(nClientSocket, str, strlen(str), 0);
        }

        if (strcmp(sbuff, "10") == 0)
        {
            char my_str[100];
            nRet = recv(nClientSocket, my_str, sizeof(my_str), 0);
            printf("num1 received : %s\n", my_str);
            int val = stoi(my_str);
            int sum = val;

            //  calculated successfully
            double result = log10(sum);

            // now we will send the response back to the server
            string temp = to_string(result);
            char str[1000];
            strcpy(str, temp.c_str());
            printf("data sending from server = %s\n", str);
            nRet = send(nClientSocket, str, strlen(str), 0);
        }

        if (strcmp(sbuff, "11") == 0)
        {
            char my_str[100];
            nRet = recv(nClientSocket, my_str, sizeof(my_str), 0);
            printf("num1 received : %s\n", my_str);
            int val = stoi(my_str);
            int sum = val;

            //  calculated successfully
            int i, pro = 1;
            for (i = 1; i <= sum; ++i)
            {
                pro *= i;
            }

            // now we will send the response back to the server
            string temp = to_string(pro);
            char str[1000];
            strcpy(str, temp.c_str());
            printf("data sending from server = %s\n", str);
            nRet = send(nClientSocket, str, strlen(str), 0);
        }

        if (strcmp(sbuff, "12") == 0)
        {
            char my_str[100];
            nRet = recv(nClientSocket, my_str, sizeof(my_str), 0);
            printf("num1 received : %s\n", my_str);
            int val = stoi(my_str);
            int sum = val;

            //  calculated successfully
            double result_inverse = 1.0 / sum;

            // now we will send the response back to the server
            string temp = to_string(result_inverse);
            char str[1000];
            strcpy(str, temp.c_str());
            printf("data sending from server = %s\n", str);
            nRet = send(nClientSocket, str, strlen(str), 0);
        }

        if (strcmp(sbuff, "13") == 0)
        {
            char my_str[100];
            nRet = recv(nClientSocket, my_str, sizeof(my_str), 0);
            printf("num1 received : %s", my_str);
            int val = stoi(my_str);
            int sum = val;
            nRet = recv(nClientSocket, my_str, sizeof(my_str), 0);
            printf("num2 received : %s", my_str);
            int val2 = stoi(my_str);

            // sum calculated successfully
            double res = sum % val2;

            // now we will send the response back to the server
            string temp = to_string(res);
            char str[100];
            strcpy(str, temp.c_str());
            printf("data sending %s\n", str);
            nRet = send(nClientSocket, str, strlen(str), 0);
        }

        if (strcmp(sbuff, "14") == 0)
        {
            char my_str[100];
            nRet = recv(nClientSocket, my_str, sizeof(my_str), 0);
            printf("num1 received : %s\n", my_str);
            int val = stoi(my_str);
            int sum = val;

            //  calculated successfully
            double result = exp(sum);

            // now we will send the response back to the server
            string temp = to_string(result);
            char str[1000];
            strcpy(str, temp.c_str());
            printf("data sending from server = %s\n", str);
            nRet = send(nClientSocket, str, strlen(str), 0);
        }
    }

    closesocket(nClientSocket);
    closesocket(nSocket);
    WSACleanup();
    return 0;
}
