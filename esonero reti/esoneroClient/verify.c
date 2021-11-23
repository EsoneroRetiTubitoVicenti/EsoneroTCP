/*
 * verify.c
 *
 *  Created on: 21 nov 2021
 *      Author: mtubi
 */


#include "verify.h"

int stringVerify(char string[]) {
	int correct = 0;
	int firstPart = 0;
	int error = 0;
	int i = 0;
	int j = 0;
	if (string[0] == EQUAL) {
		if (strlen(string) != 1) {
			error = 1;
			puts("ATTENTION!! If you want to close the program you just have to type equals(=) \n \n");
		}
	} else {
		if (string[0] != ADD && string[0] != SUB && string[0] != DIVISION
				&& string[0] != MULT) {
			error = 1;
			puts("ATTENTION!! The first character can only be '+','-','/','x' or '=' \n \n");
		}
		else if (string[1] != ' '){
			error = 1;
			puts("ATTENTION!! After the operator there must be a space \n \n");
		}
		else if (isdigit(string[2]) != 1 && (string[2] != '-') && (string[2] != '+')){
			error = 1;
			puts("ATTENTION!! After entering the operator only numbers are allowed \n \n");
		}
		else{
			if(isdigit(string[2]) == 1){
		for (i = 3; error == 0 && firstPart == 0 && i < strlen(string); i++) {
			if ((i - 3) >= MAX_NUM) {
				error = 1;
				puts("ATTENTION!! You entered the first number too big \n \n");
			} else if (isdigit(string[i]) != 1) {
				if (string[i] == ' ') {
					firstPart = 1;
				} else {
					error = 1;
					puts("ATTENTION!! A number consists of numbers and nothing else \n \n");
				}
			}
		}
		}
			else{
				if(isdigit(string[3]) == 1){
					for (i = 4; error == 0 && firstPart == 0 && i < strlen(string); i++) {
								if ((i - 3) >= MAX_NUM) {
									error = 1;
									puts("ATTENTION!! You entered the first number too big \n \n");
								} else if (isdigit(string[i]) != 1) {
									if (string[i] == ' ') {
										firstPart = 1;
									} else {
										error = 1;
										puts("ATTENTION!! A number consists of numbers and nothing else \n \n");
									}
								}
							}
				}
			}

		if (firstPart == 1 && error == 0) {
			if(isdigit(string[i]) == 1 || (string[i] == '-') || (string[i] == '+')){
			for (j = i; j < strlen(string) && error == 0; j++) {
				if ((j - i) >= MAX_NUM) {
					error = 1;
					puts("ATTENTION!! You entered the second number too big \n \n");
				} else if (isdigit(string[j]) != 1) {
					error = 1;
					puts("ATTENTION!! A number consists of numbers and nothing else \n \n");
				}
			}
			}
			else{
				error = 1;
			}
		} else {
			if(error == 0){
			error = 1;
			puts("WARNING!! The first number was not written correctly \n \n");
			}
		}

		}
	}

	if (error == 0) {
		correct = 1;
	}

	return correct;
}

void svuota_input() {
	while (getchar() != '\n')
		;
}
