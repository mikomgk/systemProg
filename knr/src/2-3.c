/*
 * 2-3.c
 *
 *  Created on: Apr 24, 2018
 *      Author: user
 */

#include <stdio.h>
#include <ctype.h>

int htoi(char *s);

int main() {
	char s[] = "f1";
	for (; s != " "; scanf("%s", s))
		printf("%s = %d\n", s, htoi(s));
	return 0;
}

int htoi(char *s) {
	int n = 0;
	for (; (*s >= '0' && *s <= '9') || (*s >= 'a' && *s <= 'f') || (*s >= 'A' && *s <= 'F'); s++) {
		n = 16 * n + (*s <= '9' ? *s - '0' : (*s <= 'F' ? *s - 'A' + 10 : *s - 'a' + 10));
	}
	return n;
}
