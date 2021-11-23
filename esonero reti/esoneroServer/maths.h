/*
 * math.h
 *
 *  Created on: 21 nov 2021
 *      Author: mtubi
 */

#ifndef MATHS_H_
#define MATHS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define ADD '+'
#define SUB '-'
#define DIVISION '/'
#define MULT 'x'
#define EQUAL '='

#define MAX_NUM 9

int stringExtraction(char string[], int i, char stringnNum[]);
void ftoa(float n, char *res, int afterpoint);
int intToStr(int x, char str[], int d);
void reverse(char *str, int len);
int add(int num1, int num2);
int sub(int num1, int num2);
float division(int num1, int num2);
int mult(int num1, int num2);
void stringCalculator(char string[]);


#endif /* MATHS_H_ */
