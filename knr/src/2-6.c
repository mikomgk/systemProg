/*
 * 2-6.c
 *
 *  Created on: Apr 24, 2018
 *      Author: user
 */

#include <stdio.h>
#include <math.h>

unsigned setbits(unsigned x, int p, int n, unsigned y);
unsigned getbits(unsigned x, int p, int n);
unsigned invert(unsigned x, int p, int n);
unsigned rightroot(unsigned x, int n);
int bitcount(signed x);

int main() {
	printf("%d\n", bitcount(302046));
	return 0;
}

unsigned setbits(unsigned x, int p, int n, unsigned y) {
	return ~((~(x | ((y & ~(~0 << n)) << (p + 1 - n)))) | ((~((~0 << n) | y)) << (p + 1 - n)));
}

unsigned getbits(unsigned x, int p, int n) {
	return (x >> (p + 1 - n)) & ~(~0 << n);
}

unsigned invert(unsigned x, int p, int n) {
	return x ^ ((~(~0 << n)) << (p + 1 - n));
}

unsigned rightroot(unsigned x, int n) {
	return (x >> n) | (((~(~0 << n)) & x) << (((int) (ceil(log(x) / log(2))) + 8 - ((int) (ceil(log(x) / log(2))) % 8)) - n));
}

int bitcount(signed x) {
	int i = 1;
	for (; (x &= (x - 1)) != 0; i++)
		;
	return i;
}
