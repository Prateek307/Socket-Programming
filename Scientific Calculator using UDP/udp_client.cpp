#include <stdio.h>
#include <winsock2.h>
#include <bits/stdc++.h>
#include <string>
#include <cstring>
#include <iostream>

#define PORT 19999

int main()
{
	WSADATA w;
	int nRet = 0;
	SOCKET nSocket;
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
	srv.sin_addr.s_addr = inet_addr("127.0.0.1"); // Use the actual IP address of the server
	srv.sin_port = htons(PORT);
	memset(&(srv.sin_zero), 0, 8);

	nRet = connect(nSocket, (struct sockaddr *)&srv, sizeof(srv));
	if (nRet == SOCKET_ERROR)
	{
		printf("\nCannot connect to server :\n%d", WSAGetLastError());
		closesocket(nSocket);
		WSACleanup();
		return -1;
	}

	while (1)
	{

		int choice;
		printf("\n\nScientific calculator\n");
		printf("Enter 1 for Addition\n");
		printf("Enter 2 for subtraction\n");
		printf("Enter 3 for Multiplication\n");
		printf("Enter 4 for Divison\n");
		printf("Enter 5 for Square root\n");
		printf("Enter 6 for Base and Power\n");
		printf("Enter 7 for Sine\n");
		printf("Enter 8 for Cosine\n");
		printf("Enter 9 for Tangent\n");
		printf("Enter 10 for Logarithm\n");
		printf("Enter 11 for Factorial\n");
		printf("Enter 12 for Inverse\n");
		printf("Enter 13 for Modulo\n");
		printf("Enter 14 for Exponentiation\n");
		printf("Enter 0 to disconnect\n");
		printf("Enter your choice :\n");
		scanf("%d", &choice);

		if (choice == 1) // for addition
		{
			strcpy(sbuff, "1");
			nRet = send(nSocket, sbuff, strlen(sbuff) + 1, 0);
			if (nRet == SOCKET_ERROR)
			{
				printf("\nCannot send message to server :\n%d", WSAGetLastError());
				break;
			}

			char val1[100], val2[100];
			printf("Enter first value :\n");
			scanf("%s", val1);
			strcpy(sbuff, val1);
			// first number sent to the server
			nRet = send(nSocket, sbuff, strlen(sbuff) + 1, 0);
			printf("Enter second value :\n");
			scanf("%s", val2);
			char sbuff2[100];
			strcpy(sbuff2, val2);
			// second number sent to the server
			nRet = send(nSocket, sbuff2, strlen(sbuff2) + 1, 0);

			printf("Addition request sent successfully\n");

			// receiving response from the server after addition
			char my_str[100];
			my_str[0] = '\0';
			nRet = recv(nSocket, my_str, sizeof(my_str), 0);
			my_str[nRet] = '\0';
			printf("data received from server = %s\n", my_str);
			printf("%s + %s = %s\n", val1, val2, my_str);
		}

		if (choice == 2) // for subtraction
		{
			sbuff[0] = '\0';
			strcpy(sbuff, "2");
			nRet = send(nSocket, sbuff, strlen(sbuff) + 1, 0);
			if (nRet == SOCKET_ERROR)
			{
				printf("\nCannot send message to server :\n%d", WSAGetLastError());
				break;
			}

			char val1[100], val2[100];
			printf("Enter first value :\n");
			scanf("%s", val1);
			strcpy(sbuff, val1);
			// first number sent to the server
			nRet = send(nSocket, sbuff, strlen(sbuff) + 1, 0);
			printf("Enter second value :\n");
			scanf("%s", val2);
			char sbuff2[100];
			strcpy(sbuff2, val2);
			// second number sent to the server
			nRet = send(nSocket, sbuff2, strlen(sbuff2) + 1, 0);

			printf("Subtraction request sent successfully\n");

			// receiving response from the server after addition
			// char my_str[100];
			char my_str2[100];
			my_str2[0] = '\0';
			nRet = recv(nSocket, my_str2, sizeof(my_str2), 0);
			my_str2[nRet] = '\0';
			// printf("value in sbuff %s\n",sbuff);
			printf("%s - %s = %s\n", val1, val2, my_str2);
		}

		if (choice == 3) // for multiplication
		{
			sbuff[0] = '\0';
			strcpy(sbuff, "3");
			nRet = send(nSocket, sbuff, strlen(sbuff) + 1, 0);
			if (nRet == SOCKET_ERROR)
			{
				printf("\nCannot send message to server :\n%d", WSAGetLastError());
				break;
			}

			char val1[100], val2[100];
			printf("Enter first value :\n");
			scanf("%s", val1);
			strcpy(sbuff, val1);
			// first number sent to the server
			nRet = send(nSocket, sbuff, strlen(sbuff) + 1, 0);
			printf("Enter second value :\n");
			scanf("%s", val2);
			char sbuff2[100];
			strcpy(sbuff2, val2);
			// second number sent to the server
			nRet = send(nSocket, sbuff2, strlen(sbuff2) + 1, 0);

			printf("Multiplication request sent successfully\n");

			// receiving response from the server after addition
			char my_str3[100];
			my_str3[0] = '\0';
			nRet = recv(nSocket, my_str3, sizeof(my_str3), 0);
			my_str3[nRet] = '\0';
			printf("%s * %s = %s\n", val1, val2, my_str3);
		}

		if (choice == 4) // for divison
		{
			sbuff[0] = '\0';
			strcpy(sbuff, "4");
			nRet = send(nSocket, sbuff, strlen(sbuff) + 1, 0);
			if (nRet == SOCKET_ERROR)
			{
				printf("\nCannot send message to server :\n%d", WSAGetLastError());
				break;
			}

			char val1[100], val2[100];
			printf("Enter first value :\n");
			scanf("%s", val1);
			strcpy(sbuff, val1);
			// first number sent to the server
			nRet = send(nSocket, sbuff, strlen(sbuff) + 1, 0);
			printf("Enter second value :\n");
			scanf("%s", val2);
			char sbuff2[100];
			strcpy(sbuff2, val2);
			// second number sent to the server
			nRet = send(nSocket, sbuff2, strlen(sbuff2) + 1, 0);

			printf("divison request sent successfully\n");

			// receiving response from the server after addition
			char my_str4[100];
			nRet = recv(nSocket, my_str4, sizeof(my_str4), 0);
			my_str4[nRet] = '\0';
			printf("%s / %s = %s\n", val1, val2, my_str4);
		}

		if (choice == 5) // for square root
		{
			sbuff[0] = '\0';
			strcpy(sbuff, "5");
			nRet = send(nSocket, sbuff, strlen(sbuff) + 1, 0);
			if (nRet == SOCKET_ERROR)
			{
				printf("\nCannot send message to server :\n%d", WSAGetLastError());
				break;
			}

			char val1[100], val2[100];
			printf("Enter value :\n");
			scanf("%s", val1);
			strcpy(sbuff, val1);
			// number sent to the server
			nRet = send(nSocket, sbuff, strlen(sbuff) + 1, 0);

			printf("Square root request sent successfully\n");

			// receiving response from the server after performing square root
			char my_str5[100];
			nRet = recv(nSocket, my_str5, sizeof(my_str5), 0);
			my_str5[nRet] = '\0';
			printf("%s ^ (1/2) = %s\n", val1, my_str5);
		}

		if (choice == 6) // for base and power
		{
			sbuff[0] = '\0';
			strcpy(sbuff, "6");
			nRet = send(nSocket, sbuff, strlen(sbuff) + 1, 0);
			if (nRet == SOCKET_ERROR)
			{
				printf("\nCannot send message to server :\n%d", WSAGetLastError());
				break;
			}

			char power[100], base[100];
			printf("Enter Base :\n");
			scanf("%s", base);
			strcpy(sbuff, base);
			// number sent to the server
			nRet = send(nSocket, sbuff, strlen(sbuff) + 1, 0);

			printf("Enter Power :\n");
			scanf("%s", power);
			char sbuff2[100];
			strcpy(sbuff2, power);
			// second number sent to the server
			nRet = send(nSocket, sbuff2, strlen(sbuff2) + 1, 0);

			printf("Base and Power request sent successfully\n");

			// receiving response from the server after performing square root
			char my_str6[100];
			nRet = recv(nSocket, my_str6, sizeof(my_str6), 0);
			my_str6[nRet] = '\0';
			printf("%s ^ %s = %s\n", base, power, my_str6);
		}

		if (choice == 7) // for sine angle
		{
			sbuff[0] = '\0';
			strcpy(sbuff, "7");
			nRet = send(nSocket, sbuff, strlen(sbuff) + 1, 0);
			if (nRet == SOCKET_ERROR)
			{
				printf("\nCannot send message to server :\n%d", WSAGetLastError());
				break;
			}

			char val1[100];
			printf("Enter value :\n");
			scanf("%s", val1);
			strcpy(sbuff, val1);
			// number sent to the server
			nRet = send(nSocket, sbuff, strlen(sbuff) + 1, 0);

			printf("Sine request sent successfully\n");

			// receiving response from the server after performing square root
			char my_str7[100];
			nRet = recv(nSocket, my_str7, sizeof(my_str7), 0);
			my_str7[nRet] = '\0';
			printf("Sine(%s) = %s\n", val1, my_str7);
		}

		if (choice == 8) // for cosine angle
		{
			sbuff[0] = '\0';
			strcpy(sbuff, "8");
			nRet = send(nSocket, sbuff, strlen(sbuff) + 1, 0);
			if (nRet == SOCKET_ERROR)
			{
				printf("\nCannot send message to server :\n%d", WSAGetLastError());
				break;
			}

			char val1[100];
			printf("Enter value :\n");
			scanf("%s", val1);
			strcpy(sbuff, val1);
			// number sent to the server
			nRet = send(nSocket, sbuff, strlen(sbuff) + 1, 0);

			printf("Cosine request sent successfully\n");

			// receiving response from the server after performing square root
			char my_str8[100];
			nRet = recv(nSocket, my_str8, sizeof(my_str8), 0);
			my_str8[nRet] = '\0';
			printf("Cosine(%s) = %s\n", val1, my_str8);
		}

		if (choice == 9) // for tan angle
		{
			sbuff[0] = '\0';
			strcpy(sbuff, "9");
			nRet = send(nSocket, sbuff, strlen(sbuff) + 1, 0);
			if (nRet == SOCKET_ERROR)
			{
				printf("\nCannot send message to server :\n%d", WSAGetLastError());
				break;
			}

			char val1[100];
			printf("Enter value :\n");
			scanf("%s", val1);
			strcpy(sbuff, val1);
			// number sent to the server
			nRet = send(nSocket, sbuff, strlen(sbuff) + 1, 0);

			printf("Tangent request sent successfully\n");

			// receiving response from the server after performing square root
			char my_str9[100];
			nRet = recv(nSocket, my_str9, sizeof(my_str9), 0);
			my_str9[nRet] = '\0';
			printf("Tangent(%s) = %s\n", val1, my_str9);
		}

		if (choice == 10) // for log10 angle
		{
			sbuff[0] = '\0';
			strcpy(sbuff, "10");
			nRet = send(nSocket, sbuff, strlen(sbuff) + 1, 0);
			if (nRet == SOCKET_ERROR)
			{
				printf("\nCannot send message to server :\n%d", WSAGetLastError());
				break;
			}

			char val1[100];
			printf("Enter value :\n");
			scanf("%s", val1);
			strcpy(sbuff, val1);
			// number sent to the server
			nRet = send(nSocket, sbuff, strlen(sbuff) + 1, 0);

			printf("Logarithm request sent successfully\n");

			// receiving response from the server after performing square root
			char my_str10[100];
			nRet = recv(nSocket, my_str10, sizeof(my_str10), 0);
			my_str10[nRet] = '\0';
			printf("Logarithm (base 10 (%s)) = %s\n", val1, my_str10);
		}

		if (choice == 11) // factorial of a number
		{
			sbuff[0] = '\0';
			strcpy(sbuff, "11");
			nRet = send(nSocket, sbuff, strlen(sbuff) + 1, 0);
			if (nRet == SOCKET_ERROR)
			{
				printf("\nCannot send message to server :\n%d", WSAGetLastError());
				break;
			}

			char val1[100];
			printf("Enter value :\n");
			scanf("%s", val1);
			strcpy(sbuff, val1);
			// number sent to the server
			nRet = send(nSocket, sbuff, strlen(sbuff) + 1, 0);

			printf("Factorial request sent successfully\n");

			// receiving response from the server after performing square root
			char my_str11[100];
			nRet = recv(nSocket, my_str11, sizeof(my_str11), 0);
			my_str11[nRet] = '\0';
			printf("Factorial of %s = %s\n", val1, my_str11);
		}

		if (choice == 12) // Inverse of a number
		{
			sbuff[0] = '\0';
			strcpy(sbuff, "12");
			nRet = send(nSocket, sbuff, strlen(sbuff) + 1, 0);
			if (nRet == SOCKET_ERROR)
			{
				printf("\nCannot send message to server :\n%d", WSAGetLastError());
				break;
			}

			char val1[100];
			printf("Enter value :\n");
			scanf("%s", val1);
			strcpy(sbuff, val1);
			// number sent to the server
			nRet = send(nSocket, sbuff, strlen(sbuff) + 1, 0);

			printf("Inverse request sent successfully\n");

			// receiving response from the server after performing square root
			char my_str12[100];
			nRet = recv(nSocket, my_str12, sizeof(my_str12), 0);
			my_str12[nRet] = '\0';
			printf("Inverse of %s = %s\n", val1, my_str12);
		}

		if (choice == 13) // for modulo
		{
			sbuff[0] = '\0';
			strcpy(sbuff, "13");
			nRet = send(nSocket, sbuff, strlen(sbuff) + 1, 0);
			if (nRet == SOCKET_ERROR)
			{
				printf("\nCannot send message to server :\n%d", WSAGetLastError());
				break;
			}

			char power[100], base[100];
			printf("Enter number 1 :\n");
			scanf("%s", base);
			strcpy(sbuff, base);
			// number sent to the server
			nRet = send(nSocket, sbuff, strlen(sbuff) + 1, 0);

			printf("Enter number 2 :\n");
			scanf("%s", power);
			char sbuff2[100];
			strcpy(sbuff2, power);
			// second number sent to the server
			nRet = send(nSocket, sbuff2, strlen(sbuff2) + 1, 0);

			printf("Modulo request sent successfully\n");

			// receiving response from the server after performing square root
			char my_str13[100];
			nRet = recv(nSocket, my_str13, sizeof(my_str13), 0);
			my_str13[nRet] = '\0';
			printf("%s modulo %s = %s\n", base, power, my_str13);
		}

		if (choice == 14) // for exponentiation
		{
			sbuff[0] = '\0';
			strcpy(sbuff, "14");
			nRet = send(nSocket, sbuff, strlen(sbuff) + 1, 0);
			if (nRet == SOCKET_ERROR)
			{
				printf("\nCannot send message to server :\n%d", WSAGetLastError());
				break;
			}

			char val1[100];
			printf("Enter value :\n");
			scanf("%s", val1);
			strcpy(sbuff, val1);
			// number sent to the server
			nRet = send(nSocket, sbuff, strlen(sbuff) + 1, 0);

			printf("Exponentiation request sent successfully\n");

			// receiving response from the server after performing square root
			char my_str14[100];
			nRet = recv(nSocket, my_str14, sizeof(my_str14), 0);
			my_str14[nRet] = '\0';
			printf("e ^ %s = %s\n", val1, my_str14);
		}

		if (choice == 0)
		{
			printf("Connection closed by client\n");
			break;
		}
	}

	closesocket(nSocket);
	WSACleanup();
	return 0;
}
