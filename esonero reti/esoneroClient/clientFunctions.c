/*
 * clientFunctions.c
 *
 *  Created on: 22 nov 2021
 *      Author: mtubi
 */
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#if defined WIN32
#include <winsock.h>
#else
#define closesocket close
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif
#include "clientFunctions.h"
#include "verify.h"

#define BUFFERSIZE 204

void clearwinsock() {
#if defined WIN32
WSACleanup();
#endif
}
void getIP_port(char IP[], int* portNumber) {
	char answer;
	do {
		puts("Type 'y' to insert IP address and port or 'n' to connect in localhost \n");
		scanf("%c", &answer);
		svuota_input();
	} while (answer != 'y' && answer != 'n');
	if (answer == 'y') {
		puts("Type IP address: \n");
		scanf("%16s", IP);
		svuota_input();
		puts("Type port number: \n");
		scanf("%d", portNumber);
		svuota_input();
	} else {
		strcpy(IP, LOCALHOST);
		*portNumber = PORT;
	}
}

int client() {
	char IPaddres[16] = {};
	int portNumber = 0;
	int c_socket = 0;
	int connectioCreated = 0;
	char input[BUFFERSIZE] = {};
	char inputServer[BUFFERSIZE]={};
	int correctInput = 0;
	struct sockaddr_in sad;
#if defined WIN32
// Initialize Winsock
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("Error at WSAStartup()\n");
		return 0;
	}
#endif
	c_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (c_socket < 0) {
		puts("socket creation failed.\n");
		closesocket(c_socket);
		clearwinsock();
		return -1;
	}
	do {
		memset(&sad, 0, sizeof(sad));
		sad.sin_family = AF_INET;
		getIP_port(IPaddres, &portNumber);
		sad.sin_addr.s_addr = inet_addr(IPaddres); // IP del server
		sad.sin_port = htons(portNumber);
		connectioCreated = connect(c_socket, (struct sockaddr*) &sad,
				sizeof(sad));
		if (connectioCreated < 0) {
			puts("Failed to connect.\n");
		}
	} while (connectioCreated < 0);
	do {
		memset(inputServer, 0, strlen(inputServer));
		do {
			memset(input, 0, strlen(input));
			puts("Enter the operation to run on the server \n");
			//fgets(input, BUFFERSIZE, stdin);
			gets(input);
			//svuota_input();
			correctInput = stringVerify(input);
		} while (correctInput != 1);
		if (sendString(c_socket, input) < 0) {
			closesocket(c_socket);
			clearwinsock();
			return -1;
		} else {
			if (input[0] != '=') {
				if (getString(c_socket, inputServer) < 0) {
					closesocket(c_socket);
					clearwinsock();
					return -1;

				} else {
					printf("Result is: %s\n", inputServer);
				}
			}
		}
	} while (input[0] != '=');
	closesocket(c_socket);
	clearwinsock();
	printf("\n"); // Print a final linefeed
	system("pause");
	return 1;
}

int sendString(int socket, char string[]) {
	int stringLenght = strlen(string);
	if (send(socket, string, stringLenght, 0) != stringLenght) {
		puts("send() sent a different number of bytes than expected");
		return -1;
	}
	return 0;
}

int getString(int socket, char string[]) {

	if (recv(socket, string, BUFFERSIZE - 1, 0) <= 0) {
		puts("recv() failed or connection closed prematurely");
		return -1;
	}
	return 0;
}
