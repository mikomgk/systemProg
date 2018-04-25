/*
 ============================================================================
 Name        : k1-13.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <string.h>

#define MAX_LINE 80

char* reverse(char* to, char* from);
char* getlines(char *s, int lim);
int length(char *s);

int main() {
	char line[MAX_LINE];
	char reversedLine[MAX_LINE];
	char *s;
	while ((length(getlines(line, MAX_LINE))) > 0) {
		s=reverse(reversedLine, line);
		printf("%s",s);
	}
	return 0;
}

char* reverse(char* to, char* from) {
	to += MAX_LINE;
	*to-- = '\0';
	for (*to-- = '\n'; *from != '\n'; from++, to--)
		*to = *from;
	return to + 1;
}

char* getlines(char *s, int lim) {
	int c;
	char *start = s;
	for (; lim > 0 && (c = getchar()) != EOF && c != '\n'; lim--, s++)
		*s = c;
	if (c == '\n')
		*s++ = c;
	*s = '\0';
	return start;
}

int length(char *s) {
	char *start = s;
	for (; *s; s++)
		;
	return s - start;
}
