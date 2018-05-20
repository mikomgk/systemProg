/*
 * set.h
 *
 *  Created on: May 19, 2018
 *      Author: user
 */

#define MAX_NUM 128
#define MAX_LINE 80
#define BITS_PER_BITE 8

typedef struct {
	char set[MAX_NUM/BITS_PER_BITE];
} set;

void read_set(set dest, int *src);
void print_set(set src);
void union_set(set src1, set src2, set dest);
void intersect_set(set src1, set src2, set dest);
void sub_set(set src1, set src2, set dest);
