/*
 * 3-4.c
 *
 *  Created on: Apr 26, 2018
 *      Author: user
 */

#include <stdio.h>
#include <string.h>
#include <math.h>

void itoa(int n, char s[]);
void reverse(char s[]);
void itob(int n, char *s, int b);

int main() {
	char s[50],a[50],c[50];
	//itob(-2147483648, s,16);
	itob(555,a,8);
	itob(555,c,2);
	printf("%d\t%s\t%s",-2147483648,a,c);
	return 0;
}

void itoa(int n, char s[]) {
	int i, sign;
	if ((sign = n) > 0)
		n = -n;
	i = 0;
	do {
		s[i++] = '0' - n % 10;
	} while ((n /= 10) < 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

void reverse(char s[]) {
	int c, i, j;
	for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
		c = s[i], s[i] = s[j], s[j] = c;
}

void itob(int n, char *s, int b) {
	int digit;
	if (n < 0) {
		*(s++) = '-';
		n = -n;
	}
	digit = log(n) / log(b);
	do {
		*s = (int) (n / pow(b, digit)) + '0';
		n -= (*(s++) - '0') * (int) pow(b, digit--);
	} while (n > 0);
	*s='\0';
}
