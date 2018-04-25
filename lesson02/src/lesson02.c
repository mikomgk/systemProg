/*
 ============================================================================
 Name        : lesson02.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	return EXIT_SUCCESS;
}

int strlen(char *s) {
	char*p;
	for (p = s; *p; p++)
		;
	return p - s;
}

void strcpyy(char *d, char *s) {
	while ((*d++ = *s++))
		;
}

void strncpyy(char *d, char *s, int n) {
	while ((*d++ = *s++) && n != 0)
		n--;
}
/*
char *strchrr( cs, c) {
	for (; *cs; cs++)
		if (*cs == c)
			return cs;
	return NULL;
}*/
/*
void some(char *s) {
	for (; (s = strchr(s, 'r'));)
		printf("%s", s);
}
*/
int getlinee(char *s, int lim) {
	int c;
	char *p = s, *end = s + lim;
	while ((p < end) && ((c = getchar()) != EOF) && (c != '\n'))
		*p++ = c;
	*p = '\0';
	return p - s;
}

int strcmp(char *s, char *t) {
	for (; *s && (*s == *t); s++, t++)
		;
	return *s - *t;
}
