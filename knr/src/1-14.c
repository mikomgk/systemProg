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
#define STEPS 15

void countFrequencies(int *wordLengths);
void printHistogram(int *wordLengths);
void drawLine(int);
char *type(int t);
enum type {
	WHITE, ALPHA, NUMBER, OTHER
};

int main() {
	int wordLengths[CHAR_TYPE] = { 0 };
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
	int *start = lengths, i,lineLength = 0;
	for (; lengths - start < CHAR_TYPE; lengths++)
		if (*lengths > lineLength)
			lineLength = *lengths;
	drawLine(lineLength/STEPS);
	for (lengths = start; lengths - start < CHAR_TYPE; lengths++) {
		printf("      |");
		for (i = 0; i < *lengths/STEPS; i++)
			printf("_");
		printf("\n%6s|", type(lengths - start));
		for (i = 0; i < *lengths/STEPS; i++)
			printf("_");
		if (*lengths != 0)
			printf("|%d", *lengths);
		printf("\n");
	}
	drawLine(lineLength/STEPS);
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

void drawLine(_lineLength) {
	int i = 0;
	for (; i < _lineLength + 7; i++)
		printf("-");
	printf("\n");
}
