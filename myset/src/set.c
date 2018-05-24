/*
 * set.c
 *
 *  Created on: May 24, 2018
 *      Author: user
 */

#include "set.h"

#define MAX_NUM_ROW 16

set emptySet = { 0 };

set read_set(int *src) {
	set dest = emptySet;
	for (; *src != -1; src++)
		dest.data[*src / BITS_PER_BITE] |= (1 << (*src % BITS_PER_BITE));
	return dest;
}

void print_set(set src) {
	int count = 0, i= 0, j= 0;
	for (; i < (MAX_NUM + BITS_PER_BITE - 1) / BITS_PER_BITE; i++)
		for (; j < BITS_PER_BITE; j++)
			if ((src.data[i] & (1 << j)) == (1 << j)) {
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

set union_set(set src1, set src2) {
	set dest = emptySet;
	int i=0;
	for (; i < (MAX_NUM + BITS_PER_BITE - 1) / BITS_PER_BITE; i++)
		dest.data[i] = src1.data[i] | src2.data[i];
	return dest;
}

set intersect_set(set src1, set src2) {
	set dest = emptySet;
	int i= 0;
	for (; i < (MAX_NUM + BITS_PER_BITE - 1) / BITS_PER_BITE; i++)
		dest.data[i] = src1.data[i] & src2.data[i];
	return dest;
}

set sub_set(set src1, set src2) {
	set dest = emptySet;
	int i=0;
	for (; i < (MAX_NUM + BITS_PER_BITE - 1) / BITS_PER_BITE; i++)
		dest.data[i] = src1.data[i] & (~(src1.data[i] & src2.data[i]));
	return dest;
}
