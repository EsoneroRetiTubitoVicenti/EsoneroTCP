/*
 * verify.h
 *
 *  Created on: 21 nov 2021
 *      Author: mtubi
 */

#ifndef VERIFY_H_
#define VERIFY_H_


#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_NUM 4
#define ADD '+'
#define SUB '-'
#define DIVISION '/'
#define MULT 'x'
#define EQUAL '='



int stringVerify(char string[]);
void svuota_input();

#endif /* VERIFY_H_ */
