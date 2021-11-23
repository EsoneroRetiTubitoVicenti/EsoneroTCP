/*
 * serverFunctions.c
 *
 *  Created on: 21 nov 2021
 *      Author: mtubi
 */

#include "serverFunctions.h"

void clearwinsock() {
#if defined WIN32
WSACleanup();
#endif
}


int server() {
	char inputString[BUFFERSIZE] = {};
	int failed = 0;
	#if defined WIN32
// Initialize Winsock
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("Error at WSAStartup()\n");
		return 0;
	}
#endif
	int mySocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (mySocket < 0) {
		printf("Socket creation failed.\n");
		clearwinsock();
	}
	struct sockaddr_in sad;
	sad.sin_family = AF_INET;
	sad.sin_addr.s_addr = inet_addr("127.0.0.1");
	sad.sin_port = htons(27015);
	if (bind(mySocket, (struct sockaddr*) &sad, sizeof(sad)) < 0) {
		printf("bind() failed.\n");
		closesocket(mySocket);
		clearwinsock();
		return -1;
	}
	if (listen(mySocket, QLEN) < 0) {
		printf("listen() failed.\n");
		closesocket(mySocket);
		clearwinsock();
		return -1;
	}

	struct sockaddr_in cad; //structure for the client address
	int clientSocket; //socket descriptor for the client
	int clientLen; //the size of the client address

	while (1) {
		failed = 0;
		printf("Waiting for a client to connect...\n");
		clientLen = sizeof(cad); //set the size of the client address
		if ((clientSocket = accept(mySocket, (struct sockaddr*) &cad,
				&clientLen)) < 0) {
			printf("accept() failed.\n");
			closesocket(clientSocket);
			failed = 1;
		}
		if(failed == 0){
		printf("Connection established with %s:%d \n", inet_ntoa(cad.sin_addr),
				ntohs(cad.sin_port));
		do {
			memset(inputString, 0, strlen(inputString));
			if (getString(clientSocket,inputString) < 0) {
				closesocket(clientSocket);
				failed = 1;
			}

			else if (inputString[0] != '=') {
				stringCalculator(inputString);
				if (sendString(clientSocket, inputString) < 0) {
					closesocket(clientSocket);
					failed = 1;
				}
			}
			else{
				closesocket(clientSocket);
			}
		} while (inputString[0] != '=' && failed == 0);
		}
	}
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
	printf("Input string: %s \n", string);
	return 0;
}
