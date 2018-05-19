/*
 * set.c
 *
 *  Created on: May 19, 2018
 *      Author: Miko Stern
 */

#include <stdio.h>
#include <stdlib.h>

#include "set.h"

void read_set(set dest, set src) {

}

void print_set(set src) {

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

void stop() {
	exit(0);
}
