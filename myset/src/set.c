/*
 * set.c
 *
 *  Created on: May 19, 2018
 *      Author: Miko Stern
 */

#include <stdio.h>
#include <math.h>

#include "set.h"

void read_set(set dest, int *src) {
	dest.set = 0;
	for (; *src != -1; src++)
		dest.set = dest.set | (int) pow(2, *src);
}

void print_set(set src) {
	int count = 0, x;
	double i;
	if (!src.set) {
		puts("The set is empty");
		return;
	}
	for (i = 0; i < MAX_NUM; i++)
		if (src.set & (x = (int) pow(2, 1))) {
			count++;
			if (count % 16 != 1)
				printf(", ");
			printf("%d", x);
			if (count % 16 == 0)
				printf("\n");
		}
}

void union_set(set src1, set src2, set dest) {
	dest.set = src1.set | src2.set;
}

void intersect_set(set src1, set src2, set dest) {
	dest.set = src1.set & src2.set;
}

void sub_set(set src1, set src2, set dest) {
	dest.set = src1.set & (~(src1.set & src2.set));
}
/*
void stop() {
	return;
}
*/
