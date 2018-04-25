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

#define MAX_LINE 512

int my_bcmp(const void *b1, const void *b2, size_t len);

int main() {
	int len, i, j, error = 0;
	char str[MAX_LINE], *s = str;
	while (len) {
		printf("Length of bytes to compare = ");
		scanf("%d", &len);
		printf("The first index to compare from = ");
		scanf("%d", &i);
		printf("The second index to compare from = ");
		scanf("%d", &j);
		int newline = getchar();
		printf("The string you want to check = ");
		fgets(s, MAX_LINE, stdin);
		if (!*s || i < 0 || j < 0 || len < 0) {
			if (!*s)
				puts("You didn't insert a string\n");
			if (i < 0 || j < 0)
				printf("You didn't insert %s\n", i == -1 ? (j == -1 ? "2 indexes" : "the first index") : "the second index");
			if (len < 0)
				puts("You didn't insert a length\n");
			error = 1;
		}
		if ((i > j ? i : j) + len > MAX_LINE) {
			puts("You got a stack overflow\n");
			error = 1;
		}
		const void *a = s + (i < 0 ? 0 : i), *b = s + (j < 0 ? 0 : j);
		if (!error && (a == b || len == 0))
			puts("0");
		else if (!error)
			printf("%d\n\n", my_bcmp(a, b, len));
		*s = '\0';
		i = j = len = -1;

	}
	return 0;
}

int my_bcmp(const void *b1, const void *b2, size_t len) {
	char *a1 = b1, *a2 = b2;
	while (*(a1++) == *(a2++) && len-- > 1)
		;
	return *(--a1) - *(--a2);
}
