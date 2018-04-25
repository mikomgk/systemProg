/*
 * 2-1.c

 *
 *  Created on: Apr 23, 2018
 *      Author: user
 */

#include <stdio.h>

#define INFINITY (1e999)

int main() {
	unsigned char a = 'a';
	signed char b = 'a';
	unsigned short c = 1;
	signed short d = 1;
	signed short e = -1;
	unsigned int f = 1;
	signed int g = 1;
	signed int h = -1;
	unsigned long i = 1;
	signed long j=1;
	signed long k=-1;
	float l = 1;
	float m = -1;
	double n = 1;
	double o = -1;
	long double p = 1;
	long double q = -1;
	for (; k<0x7F800000;
			printf("%d\t\t%lu\t\t%ld\t\t%ld\t\t%f\t\t%f\t\t%f\t\t%f\t\t%Lf\t\t%Lf\n",
					f++, i++, j++, k--,l++,m--,n++,o--,p++,q--))
		;
	return 0;
}
