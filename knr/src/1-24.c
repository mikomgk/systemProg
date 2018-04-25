/*
 * 1-24.c
 *
 *  Created on: Apr 23, 2018
 *      Author: user
 */

#include <stdio.h>
#include <ctype.h>

#define MAX_LINE 80
#define ERROR 0

enum status {
	OUT, IN_COMMENT, IN_CPP_COMMENT, IN_STRING
};

int main() {
	int c, temp, state = OUT, mode = 1, line = 1, col = 1, backslashes = 1;
	char stack[MAX_LINE], *s = stack - 1;
	while (mode != ERROR && (c = getchar()) != EOF) {
		switch (state) {
		case OUT:
			if (c == '{' || c == '[' || c == '(')
				*(++s) = c;
			else if (c == '/' && temp == '/')
				state = IN_COMMENT;
			else if (c == '*' && temp == '/')
				state = IN_CPP_COMMENT;
			else if (c == '\"' || c == '\'') {
				*(++s) = c;
				state = IN_STRING;
			} else if ((c == '}' && *s != '{') || (c == ']' && *s != '[') || (c == ')' && *s != '('))
				mode = ERROR;
			else if (c == '}' || c == ']' || c == ')')
				*(s--) = '\0';
			temp = c;
			break;
		case IN_COMMENT:
			if (c == '\n')
				state = OUT;
			break;
		case IN_CPP_COMMENT:
			if (c == '/' && temp == '*')
				state = OUT;
			temp = c;
			break;
		case IN_STRING:
			if ((c == '\"' && *s == '\"' && (backslashes % 2 == 0)) || (c == '\'' && *s == '\'' && (backslashes % 2 == 0))) {
				*(s--) = '\0';
				state = OUT;
				backslashes = 0;
			} else if (c == '\\' && temp == '\\')
				backslashes++;
			else if (c == '\\')
				backslashes = 1;
			else
				backslashes = 0;
			temp = c;
			break;
		}
		if (c == '\n') {
			line++;
			col = 1;
		} else if (c == '\t')
			col += 4;
		else
			col++;
	}
	if (mode == ERROR || *s != '\0') {
		char x = (*s == '{' ? '}' : (*s == '[' ? ']' : (*s == '(' ? ')' : *s)));
		printf("Error: expected %b in line:%d:%d\n", x, line, col);
	}
	return 0;
}
