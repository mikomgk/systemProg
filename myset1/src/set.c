/*
 * set.c
 *
 *  Created on: May 19, 2018
 *      Author: Miko Stern
 */

#include <stdio.h>
#include <math.h>

#include "set.h"

#define MAX_NUM_ROW 16

void read_set(set dest, int *src) {
	int i;
	for (i = 0; i < MAX_NUM / BITS_PER_BITE; i++)
		dest.set[i] = 0;
	for (; *src != -1; src++)
		dest.set[*src / BITS_PER_BITE] = dest.set[*src / BITS_PER_BITE] | (int) pow(2, *src % BITS_PER_BITE);
}

void print_set(set src) {
	int count = 0, i, j;
	for (i = 0; i < MAX_NUM / BITS_PER_BITE; i++)
		for (j = 0; j < BITS_PER_BITE; j++)
			if ((src.set[i] & (int) pow(2, j)) == (int) pow(2, j)) {
				count++;
				if (count % MAX_NUM_ROW != 1)
					printf(", ");
				printf("%d", BITS_PER_BITE * i + j);
				if (count % MAX_NUM_ROW == 0)
					printf("\n");
			}
	if (count == 0)
		puts("The set is empty");
}

void union_set(set src1, set src2, set dest) {
	int i;
	for (i = 0; i < MAX_NUM / BITS_PER_BITE; i++)
		dest.set[i] = src1.set[i] | src2.set[i];
}

void intersect_set(set src1, set src2, set dest) {
	int i;
	for (i = 0; i < MAX_NUM / BITS_PER_BITE; i++)
		dest.set[i] = src1.set[i] & src2.set[i];
}

void sub_set(set src1, set src2, set dest) {
	int i;
	for (i = 0; i < MAX_NUM / BITS_PER_BITE; i++)
		dest.set[i] = src1.set[i] & (~(src1.set[i] & src2.set[i]));
}
