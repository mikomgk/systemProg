/*
 ============================================================================
 Name        : lesson03.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

char* strChr(char *str, char ch);

int main() {
	puts(strChr("tuvwxyz12345", 'z'));
	return 0;
}

char* strChr(char *str, char ch) {
	for (; *str && *str != ch; str++)
		;
	return str;
}
