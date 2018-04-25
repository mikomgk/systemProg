/*
 ============================================================================
 Name        : k1-13.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <ctype.h>

#define CHAR_TYPE 4
#define HEIGHT 17
#define LINE_LENGTH 30

void countFrequencies(int *wordLengths);
void printHistogram(int *wordLengths);
void drawLine();
int ceils(int lengths, int scale);
char *type(int t);
enum type {
	WHITE, ALPHA, NUMBER, OTHER
};

int main() {
	int wordLengths[CHAR_TYPE]={0};
	countFrequencies(wordLengths);
	printHistogram(wordLengths);
	return 0;
}

void countFrequencies(int *lengths) {
	int c;
	while ((c = getchar()) != EOF) {
		if (c == '\n' || c == '\t' || c == ' ')
			(*(lengths + WHITE))++;
		else if (isalpha(c))
			(*(lengths + ALPHA))++;
		else if (isdigit(c))
			(*(lengths + NUMBER))++;
		else
			(*(lengths + OTHER))++;
	}
}

void printHistogram(int *lengths) {
	int *start = lengths, lines = 0,scale,height=HEIGHT;
	drawLine();
	for (; lengths - start < 4; lengths++)
		if (*lengths > lines)
			lines = *lengths;
	scale=lines/HEIGHT;
	for (height += 2; height > 0; height--) {
		for (lengths = start; lengths - start < 4; lengths++)
			if (ceils(*lengths,scale) - height == -2 && *lengths != 0)
				printf(" %4d  ", *lengths);
			else if (ceils(*lengths,scale) - height == -1 && *lengths != 0)
				printf("  __   ");
			else if (ceils(*lengths,scale) - height >= 0)
				printf(" |  |  ");
			else
				printf("       ");
		printf("\n");
	}
	drawLine();
	for (lengths = start; lengths - start < 4; lengths++)
		printf("%6s|", type(lengths - start));
	printf("\n");
	drawLine();
}

int ceils(int lengths, int scale) {
	double x=lengths/scale;
	if(x<1&&lengths!=0)
		x=1;
	return x;
}

char *type(int t) {
	switch (t) {
	case WHITE:
		return "WHITE";
	case ALPHA:
		return "ALPHA";
	case NUMBER:
		return "NUMBER";
	case OTHER:
		return "OTHER";
	}
}

void drawLine() {
	int i = 0;
	for (; i < LINE_LENGTH; i++)
		printf("-");
	printf("\n");
}
