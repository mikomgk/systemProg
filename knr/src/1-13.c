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

#define WORD_LENGTH 20

void countLength(int *wordLengths);
void printHistogram(int *wordLengths);
void drawLine(int);

int main() {
	int wordLengths[WORD_LENGTH]={0};
	countLength(wordLengths);
	printHistogram(wordLengths);
	return 0;
}

void countLength(int *lengths) {
	int c, length = 0;
	while ((c = getchar()) != EOF) {
		if (c != '\n' && c != '\t' && c != ' ')
			length++;
		else if (length > 0) {
			(*(lengths + length))++;
			length = 0;
		}
	}
}

void printHistogram(int *lengths) {
	int *start = lengths, i, sum = 0, lineLength=0;
	for (;lengths-start<WORD_LENGTH;lengths++)
		if(*lengths>lineLength)
			lineLength=*lengths;
	drawLine(lineLength);
	for (lengths=start+1; lengths - start < 11; lengths++) {
		printf("   |");
		for (i = 0; i < *lengths; i++)
			printf("_");
		printf("\n%03d|", lengths - start);
		for (i = 0; i < *lengths; i++)
			printf("_");
		if (*lengths != 0)
			printf("|%d", *lengths);
		printf("\n");
	}
	for (; lengths - start <= WORD_LENGTH - 1; lengths++)
		sum += *lengths;
	printf("   |");
	for (i = 0; i < sum; i++)
		printf("_");
	printf("\n>10|");
	for (i = 0; i < sum; i++)
		printf("_");
	if (sum != 0)
		printf("|%d", sum);
	printf("\n");
	drawLine(lineLength);
}

void drawLine(_lineLength) {
	int i = 0;
	for (; i < _lineLength+7; i++)
		printf("-");
	printf("\n");
}
