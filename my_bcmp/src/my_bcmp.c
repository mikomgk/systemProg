/*
 ============================================================================
 Name        : my_bcmp.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <string.h>

#define MAX_LINE 512
#define MAX_PRINT_LINE 60

int error;

int my_bcmp(const void *b1, const void *b2, size_t len);
int checkIfInt(float num, char* numName);
int checkIfPositive(float num, char* numName);

int main() {
	int inputs = 1;
	float len, i, j;
	char str[MAX_LINE], *s = str;
	extern int error;
	while (inputs != EOF) {
		error = 0;
		puts("Enter length to check, 2 index to begin from and a string, separated with space (enter exit to exit)\n");
		if ((inputs = scanf("%f %f %f %s", &len, &i, &j, s)) == 4) {
			checkIfInt(len, "The length");
			checkIfPositive(len, "The length");
			checkIfInt(i, "The first index");
			checkIfPositive(i, "The first index");
			checkIfInt(j, "The second index");
			checkIfPositive(j, "The second index");
			if ((i > j ? i : j) + len > MAX_LINE) {
				puts("These indexes and length make a stack overflow");
				error = 1;
			}
			if (!error) {
				char *a = s + (int) i, *b = s + (int) j;
				printf(
						"Length of bytes to compare = %d\nThe first index to compare from = %d\nThe second index to compare from = %d\nThe string you want to check = %s\n\n",
						(int) len, (int) i, (int) j, s);
				if (i == j || len == 0)
					printf("0\n\n\n");
				else
					printf("%d\n\n\n", my_bcmp(a, b, (int) len));
			}
			else
				puts("\n");
		} else {
			puts("You entered incorrect data");
			inputs = EOF;
		}
	}
	return 0;
}

int my_bcmp(const void *b1, const void *b2, size_t len) {
	char *a1 = (char *) b1, *a2 = (char *) b2;
	while (*(a1++) == *(a2++) && len-- > 1)
		;
	return *(--a1) - *(--a2);
}

int checkIfInt(float num, char* numName) {
	extern int error;
	char str[MAX_PRINT_LINE] = "", *s = strcat(str, numName);
	if ((int) num != num) {
		error = 1;
		puts(strcat(s, " must be an integer number"));
	}
	return 0;
}

int checkIfPositive(float num, char* numName) {
	extern int error;
	char str[MAX_PRINT_LINE] = "", *s = strcat(str, numName);
	if (num < 0) {
		error = 1;
		puts(strcat(s, " must be zero or bigger"));
	}
	return 0;
}
