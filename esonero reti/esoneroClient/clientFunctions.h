/*
 * clientFunctions.h
 *
 *  Created on: 22 nov 2021
 *      Author: mtubi
 */

#ifndef CLIENTFUNCTIONS_H_
#define CLIENTFUNCTIONS_H_



#define LOCALHOST "127.0.0.1"
#define PORT 27015

void getIP_port(char IP[], int *portNumber);
int client();
int sendString(int socket, char string[]);
int getString(int socket, char string[]);
void clearwinsock();


#endif /* CLIENTFUNCTIONS_H_ */
