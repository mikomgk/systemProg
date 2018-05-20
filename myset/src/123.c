/*
 ============================================================================
 Name        : myset.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX_COMMAND 14
#define MAX_SETPARAMS 3
#define MAX_NUM 128
#define MAX_LINE 80
#define BITS_PER_BITE 8
#define MAX_NUM_ROW 16

typedef struct {
	char set[MAX_NUM / BITS_PER_BITE];
} set;

int checkParams(int parametersCollected, int parametersTarget);
void removeBlanks(char *s);
int getCommand(char *s, char *command);
int getParams(char *src, char *setParams, int *listParam);
void error(int i);
void read_set(set dest, int *src);
void print_set(set src);
void union_set(set src1, set src2, set dest);
void intersect_set(set src1, set src2, set dest);
void sub_set(set src1, set src2, set dest);

int main() {
	set sets[6];
	char userCommand[MAX_LINE], command[MAX_COMMAND], setParams[MAX_SETPARAMS];
	int listParam[MAX_LINE], parametersCollected, commandStatus;
	while (strcmp(command, "stop") != 0) {
		if (fgets(userCommand, MAX_LINE, stdin) == NULL) {
			puts(userCommand);
			puts("You didn't use the stop command to quit the program");
			strcpy(command, "stop");
			break;
		}
		puts(userCommand);
		if ((commandStatus = getCommand(userCommand, command)) == 0)
			error(2);
		else if (commandStatus != -1) {
			removeBlanks(userCommand);
			if ((parametersCollected = getParams(userCommand, setParams, listParam)) != -1) {
				if (strcmp(command, "read_set") == 0) {
					if (checkParams(parametersCollected, 2))
						read_set(sets[setParams[0] - 'A'], listParam);
				} else if (strcmp(command, "print_set") == 0) {
					if (checkParams(parametersCollected, 1))
						print_set(sets[setParams[0] - 'A']);
				} else if (strcmp(command, "union_set") == 0) {
					if (checkParams(parametersCollected, 3))
						union_set(sets[setParams[0] - 'A'], sets[setParams[1] - 'A'], sets[setParams[2] - 'A']);
				} else if (strcmp(command, "read_set") == 0) {
					if (checkParams(parametersCollected, 3))
						intersect_set(sets[setParams[0] - 'A'], sets[setParams[1] - 'A'], sets[setParams[2] - 'A']);
				} else if (strcmp(command, "sub_set") == 0) {
					if (checkParams(parametersCollected, 3))
						sub_set(sets[setParams[0] - 'A'], sets[setParams[1] - 'A'], sets[setParams[2] - 'A']);
				} else if (strcmp(command, "stop") == 0) {
					if (parametersCollected > 0) {
						error(7);
						strcpy(command, "");
					}
				} else
					error(2);
			}
		}
	}
	return 0;
}

/*
 * Validates if the number of parameters are correct
 *
 * @param *parametersCollected the number of parameters entered
 * @param *parametersTarget the number of parameters that suppose to be
 * @return 0 if it's incorrect 1 if it's correct
 */
int checkParams(int parametersCollected, int parametersTarget) {
	if (parametersCollected > parametersTarget) {
		error(7);
		return 0;
	} else if (parametersCollected < parametersTarget) {
		error(6);
		return 0;
	}
	return 1;
}

/*
 * Removes spaces and tabs from *src
 */
void removeBlanks(char *src) {
	char *pnt = src;
	for (; *src; *pnt++ = *src++)
		for (; *src == ' ' || *src == '\t'; src++)
			;
	*pnt = '\0';
}

/*
 * Copy the first word from *src to *command and deletes it from *src
 *
 * @return the number of chars copied to command or -1 if there was an error
 */
int getCommand(char *src, char *command) {
	int counter = 0;
	char *start = src;
	for (; *src == ' ' || *src == '\t'; src++)
		;
	for (; (isalpha(*src) || *src == '_') && counter < 13; *command++ = *src++, counter++)
		;
	if (*src == ',') {
		error(10);
		return -1;
	}
	*command = '\0';
	if (strcmp(command - counter, "read_set") != 0 && strcmp(command - counter, "print_set") != 0
			&& strcmp(command - counter, "union_set") != 0 && strcmp(command - counter, "intersect_set") != 0
			&& strcmp(command - counter, "sub_set") != 0 && strcmp(command - counter, "stop") != 0) {
		error(2);
		return -1;
	}
	strcpy(start, src);
	return counter;
}

/*
 * Get the parameters out of *src and puts a letter to *setParams or an int to *listParam
 *
 * @return the number of parameters collected from *src or -1 if there was an error
 */
int getParams(char *src, char *setParams, int *listParam) {
	char *firstParam = setParams;
	int num = 0, paramIsDigit = 0;
	;
	for (; *src; src++) {
		if (paramIsDigit == 0 && isalpha(*src))
			if (*src++ == 'S' && *src++ == 'E' && *src++ == 'T')
				if (setParams - firstParam < MAX_SETPARAMS)
					if (*src >= 'A' && *src <= 'F') {
						*setParams++ = *src++;
						if (*src && *src != ',') {
							error(9);
							return -1;
						}
					} else {
						error(1);
						return -1;
					}
				else {
					error(7);
					return -1;
				}
			else {
				error(1);
				return -1;
			}
		else if (isdigit(*src)) {
			paramIsDigit = 1;
			for (; isdigit(*src); src++)
				num = 10 * num + *src + '0';
			if (num < MAX_NUM)
				*listParam++ = num;
			else {
				error(3);
				return -1;
			}
			if (*src == '.') {
				error(4);
				return -1;
			}
			if (*src != ',') {
				error(9);
				return -1;
			}
		} else if (*(src + 1) == ',') {
			error(8);
			return -1;
		} else if (*src++ == '-')
			if (*src++ == '1' && !*src)
				*listParam = -1;
			else {
				error(3);
				return -1;
			}
		else {
			error(4);
			return -1;
		}
	}
	if (*--src != '1' || *--src != '-') {
		error(5);
		return -1;
	}
	if (paramIsDigit == 1 && setParams - firstParam != 1) {
		error(11);
		return -1;
	}
	return setParams - firstParam + (paramIsDigit == 1 ? 1 : 0);
}

/*
 * Prints an error message by the  given error code
 */
void error(int i) {
	if (i == 1)
		puts("Undefined set name");
	if (i == 2)
		puts("Undefined command name");
	if (i == 3)
		puts("Invalid set member - value out of range");
	if (i == 4)
		puts("Invalid set member - not an integer");
	if (i == 5)
		puts("List of set members is not terminated correctly");
	if (i == 6)
		puts("Missing parameter");
	if (i == 7)
		puts("Extraneous text after end of command");
	if (i == 8)
		puts("Multiple consecutive commas");
	if (i == 9)
		puts("Missing comma");
	if (i == 10)
		puts("Illegal comma");
	if (i == 11)
		puts("Wrong parameters entered");
}

void read_set(set dest, int *src) {
	int i;
	for (i = 0; i < MAX_NUM / BITS_PER_BITE; i++)
		dest.set[i] = 0;
	for (; *src != -1; src++)
		dest.set[*src / BITS_PER_BITE] = dest.set[*src / BITS_PER_BITE] | (int) pow(2, *src % BITS_PER_BITE);
}

void print_set(set src) {
	int count = 0, i, j;
	for (i = 0; i < MAX_NUM / BITS_PER_BITE; i++)
		for (j = 0; j < BITS_PER_BITE; j++)
			if ((src.set[i] & (int) pow(2, j)) == (int) pow(2, j)) {
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

void union_set(set src1, set src2, set dest) {
	int i;
	for (i = 0; i < MAX_NUM / BITS_PER_BITE; i++)
		dest.set[i] = src1.set[i] | src2.set[i];
}

void intersect_set(set src1, set src2, set dest) {
	int i;
	for (i = 0; i < MAX_NUM / BITS_PER_BITE; i++)
		dest.set[i] = src1.set[i] & src2.set[i];
}

void sub_set(set src1, set src2, set dest) {
	int i;
	for (i = 0; i < MAX_NUM / BITS_PER_BITE; i++)
		dest.set[i] = src1.set[i] & (~(src1.set[i] & src2.set[i]));
}
