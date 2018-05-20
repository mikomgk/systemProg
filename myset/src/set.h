/*
 * set.h
 *
 *  Created on: May 19, 2018
 *      Author: user
 */

#define MAX_NUM 128
#define MAX_LINE 80

typedef struct {
	unsigned set :MAX_NUM;
} set;

void read_set(set dest, int *src);
void print_set(set src);
void union_set(set src1, set src2, set dest);
void intersect_set(set src1, set src2, set dest);
void sub_set(set src1, set src2, set dest);
//void stop();
