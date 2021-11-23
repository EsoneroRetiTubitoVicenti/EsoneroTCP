/*
 * math.c
 *
 *  Created on: 21 nov 2021
 *      Author: mtubi
 */

#include <math.h>
#include "maths.h"

void stringCalculator(char string[]) {
	char stringNum1[MAX_NUM] = {};
	char stringNum2[MAX_NUM] = {};
	char stringError[6] = "ERROR";
	int num1 = 0;
	int num2 = 0;
	int i = 2;
	i = stringExtraction(string, i, stringNum1);
	num1 = atoi(stringNum1);
	i++;
	i = stringExtraction(string, i, stringNum2);
	num2 = atoi(stringNum2);
	switch (string[0]) {
	case (ADD):
		memset(string, 0, strlen(string));
		itoa(add(num1, num2), string, 10);
		break;
	case (SUB):
		//strcpy(string, "");
		memset(string, 0, strlen(string));
		itoa(sub(num1, num2), string, 10);
		break;
	case (MULT):
		//strcpy(string, "");
		memset(string, 0, strlen(string));
		itoa(mult(num1, num2), string, 10);
		break;
	case (DIVISION):
		if (num2 != 0) {
			//strcpy(string, "");
			memset(string, 0, strlen(string));
			ftoa(division(num1, num2), string, 2);
		} else {
			memset(string, 0, strlen(string));
			strcpy(string, stringError);
		}
		break;
	}
}

int stringExtraction(char string[], int i, char stringNum[]) {
	int j = 0;
	for (j = 0; string[i] != ' ' && i < strlen(string); i++) {
		stringNum[j] = string[i];
		j++;
	}
	stringNum[j] = '\0';
	return i;
}

int add(int num1, int num2) {
	return num1 + num2;

}

int sub(int num1, int num2) {
	return num1 - num2;
}

float division(int num1, int num2) {
	float risultato = 0;
	if (num2 == 0) {
		return -1;
	} else {

		risultato = (float) num1 / num2;
	}
	return risultato;
}

int mult(int num1, int num2) {
		return num1 * num2;
}

void ftoa(float n, char *res, int afterpoint) {
	// Extract integer part
	int ipart = (int) n;

	// Extract floating part
	float fpart = n - (float) ipart;

	// convert integer part to string
	int i = intToStr(ipart, res, 0);

	// check for display option after point
	if (afterpoint != 0) {
		res[i] = '.'; // add dot

		// Get the value of fraction part upto given no.
		// of points after dot. The third parameter
		// is needed to handle cases like 233.007
		fpart = fpart * pow(10, afterpoint);

		intToStr((int) fpart, res + i + 1, afterpoint);
	}
}

int intToStr(int x, char str[], int d) {
	int i = 0;
	while (x) {
		str[i++] = (x % 10) + '0';
		x = x / 10;
	}

	// If number of digits required is more, then
	// add 0s at the beginning
	while (i < d)
		str[i++] = '0';

	reverse(str, i);
	str[i] = '\0';
	return i;
}

void reverse(char *str, int len) {
	int i = 0, j = len - 1, temp;
	while (i < j) {
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}


