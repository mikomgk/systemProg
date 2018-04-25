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
#include <ctype.h>

int main() {
	int c, blank = 0;
	while ((c = getchar()) != EOF) {
		if (c != '\t' && c != ' ' && c != '\n') {
			blank = 0;
			putchar(c);
		} else if (c == '\n') {
			if (blank == 0)
				putchar(c);
			blank = 1;
		}
	}
	return 0;
}
