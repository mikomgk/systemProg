/*
 ============================================================================
 Name        : my_str.c
 Author      : Miko Stern
 Version     : 19/3/18
 Description : Prints a shortened string for a given string
 ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_STR 80

void shortStr(char *s);
enum status {
	OUT, ALPHA, SEC_ALPHA, IN_STRING
};

int main() {
	char str[MAX_STR];
	int length;
	puts("Enter a string you want to make shortened(enter to quit)");
	while (fgets(str, MAX_STR, stdin)&&*str!='\n') {
		length = strlen(str);
		if (str[length - 1] == '\n')
			strcpy(str + length - 1, str + length);
		printf("\nYour long string is:\n%s\n\n", str);
		shortStr(str);
		printf("Your shortened string is:\n%s\n\n", str);
		puts("Enter a string you want to make shortened(enter to quit)");
	}
	return 0;
}

void shortStr(char *s) {
	int temp, state = OUT;
	char *endStr;
	for (; *s; s++) {
		switch (state) {
		case OUT:
			if (isalpha(*s)) {
				temp = *s;
				state = ALPHA;
			}
			break;

		case ALPHA:
			if (*s == temp + 1) {
				temp = *s;
				state = SEC_ALPHA;
			} else if (isalpha(*s))
				temp = *s;
			else
				state = OUT;
			break;

		case SEC_ALPHA:
			if (isalpha(*s) && *s == temp + 1) {
				*(s - 1) = '-';
				endStr = s;
				temp = *s;
				state = IN_STRING;
			} else if (isalpha(*s)) {
				temp = *s;
				state = ALPHA;
			} else
				state = OUT;
			break;

		case IN_STRING:
			if (*s != temp + 1 || !(isalpha(*s))) {
				char str[MAX_STR];
				strcpy(str, s - 1);
				strcpy(endStr, str);
				s = endStr + 1;
				if (isalpha(*s)) {
					temp = *s;
					state = ALPHA;
				} else
					state = OUT;
			} else
				temp = *s;
			break;
		}
	}
	if (state == IN_STRING)
		strcpy(endStr, s - 1);
}
