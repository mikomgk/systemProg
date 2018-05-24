/*
 * set.h
 *
 *  Created on: May 23, 2018
 *      Author: user
 */

#include <stdio.h>

#define MAX_NUM 127
#define BITS_PER_BITE 8

typedef struct {
	char data[(MAX_NUM + BITS_PER_BITE - 1) / BITS_PER_BITE];
} set;

set emprtySet;

set read_set(int *src);
void print_set(set src);
set union_set(set src1, set src2);
set intersect_set(set src1, set src2);
set sub_set(set src1, set src2);
