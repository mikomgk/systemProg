/*
 * set.h
 *
 *  Created on: May 19, 2018
 *      Author: user
 */

typedef struct {
	unsigned set :128;
} set;

void read_set(set dest, set src);
void print_set(set src);
void union_set(set src1, set src2, set dest);
void intersect_set(set src1, set src2, set dest);
void sub_set(set src1, set src2, set dest);
void stop();
