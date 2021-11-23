/*
 * serverFunctions.h
 *
 *  Created on: 21 nov 2021
 *      Author: mtubi
 */

#ifndef SERVERFUNCTIONS_H_
#define SERVERFUNCTIONS_H_

#if defined WIN32
#include <winsock.h>
#else
#define closesocket close
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif
#include <stdio.h>
#include "maths.h"

#define QLEN 5
#define BUFFERSIZE 204

int server();
int sendString(int socket, char string[]);
int getString(int socket, char string[]);
void clearwinsock();
#endif /* SERVERFUNCTIONS_H_ */
