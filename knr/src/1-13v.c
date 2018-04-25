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
#define LINE_LENGTH 55

void countLength(int *wordLengths);
void printHistogram(int *wordLengths);
void drawLine();

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
	int *start = lengths, sum = 0, lines = 0;
	drawLine();
	for (lengths += 11; lengths - start <= WORD_LENGTH - 1; lengths++)
		sum += *lengths;
	*(start + 11) = sum;
	for (lengths = start + 1; lengths - start < 12; lengths++)
		if (*lengths > lines)
			lines = *lengths;
	for (lines += 2; lines > 0; lines--) {
		for (lengths = start + 1; lengths - start < 12; lengths++)
			if (*lengths - lines == -2 && *lengths != 0)
				printf(" %2d  ", *lengths);
			else if (*lengths - lines == -1 && *lengths != 0)
				printf(" __  ");
			else if (*lengths - lines >= 0)
				printf("|  | ");
			else
				printf("     ");
		printf("\n");
	}
	drawLine();
	for (lengths = start + 1; lengths - start < 11; lengths++)
		printf(" %02d |", lengths - start);
	printf(" >10");
	printf("\n");
	drawLine();
}

void drawLine() {
	int i = 0;
	for (; i < LINE_LENGTH; i++)
		printf("-");
	printf("\n");
}
