#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_NUM 127
#define BITS_PER_BITE 8
#define MAX_NUM_ROW 16
#define MAX_LINE 80
#define MAX_COMMAND 14

typedef struct {
	char data[(MAX_NUM + BITS_PER_BITE - 1) / BITS_PER_BITE];
} set;

set print_set2(set src);
set stop();
set read_set(int *src);
void print_set(set src);
set union_set(set src1, set src2);
set intersect_set(set src1, set src2);
set sub_set(set src1, set src2);
int str_trimmer(char *src);
void str_parser(char *src, char *cmdName, char *setParamNamesArr[],char *numStr);
int getNumArr(char*src, int numArr[]);
int set_names_to_sets(char*setParamNamesArr[], set*setParamArr[], const char*setsNames[], set *setArr[]);
set* cmd_name_to_cmd(const char *cmdName, const char *cmdNames[], set*cmdArr[], int *numParam, int paramsCollected);
void error(int errorCode);

set emptySet = { { 0 } };
int isStop=0;

int main() {
	extern set emptySet;
	extern int isStop;
	set a = emptySet, b = a, c = a, d = a, e = a, f = a, *leftSet, *rightSet, *resultSet;
	set*setArr[] = { &a, &b, &c, &d, &e, &f, NULL };
	set*setParamArr[] = { leftSet, rightSet, resultSet };
	const char*setsNames[] = { "SETA", "SETB", "SETC", "SETD", "SETE", "SETF", NULL };
	set (*rs)() = read_set, (*ps)() = print_set2, (*us)() = union_set, (*is)() = intersect_set,
			(*ss)() = sub_set, (*s)() = stop, (*cmd)();
	set*cmdArr[] = { rs, ps, us, is, ss, s, NULL };
	const char*cmdNames[] = { "read_set", "print_set", "union_set", "intersect_set", "sub_set",
			"stop", NULL };
	const int numParam[] = { 1, 1, 3, 3, 3, 0 };
	char line[MAX_LINE], cmdName[MAX_COMMAND], leftSetName[MAX_COMMAND], rightSetName[MAX_COMMAND],
			resulrSetName[MAX_COMMAND], isNull[MAX_COMMAND],*numStr;
	char* setParamNamesArr[] = { leftSetName, rightSetName, resulrSetName, isNull, NULL };
	int i, numArr[MAX_LINE];

	while (!isStop && fgets(line, MAX_LINE, stdin)) {
		if(!str_trimmer(line))
			continue;
		str_parser(line, cmdName, setParamNamesArr,numStr);
		for (i = 0; *setParamNamesArr[i]; i++)/*count parameters collected*/
			;
		if(!set_names_to_sets(setParamNamesArr, setParamArr, setsNames, setArr))
			continue;
		if (cmd = cmd_name_to_cmd(cmdName, cmdNames, cmdArr, numParam, i))/*command is correct*/{
			if (!strcmp(cmdName, cmdNames[0])){/*command is read_set*/
				if(!getNumArr(line, numArr))
					continue;
				*resultSet = cmd(leftSet, numArr);
			}
			*resultSet = cmd(leftSet, rightSet);
		}
	}
	if(isStop==0)/*finish without stop command*/
		error(12);
	return 0;
}

set print_set2(set src) {
	print_set(src);
	return src;
}

set stop() {
	extern set emptySet;
	isStop=1;
	return emptySet;
}

set read_set(int *src) {
	set dest = emptySet;
	int i = 0;
	for (; src[i] != -1; i++)
		dest.data[*src / BITS_PER_BITE] |= (1 << src[i] % BITS_PER_BITE);
	return dest;
}

void print_set(set src) {
	int count = 0, i = 0, j = 0;
	for (; i < (MAX_NUM + BITS_PER_BITE - 1) / BITS_PER_BITE; i++)
		for (; j < BITS_PER_BITE; j++)
			if ((src.data[i] & (1 << j)) == (1 << j)) {
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

set union_set(set src1, set src2) {
	set dest = emptySet;
	int i = 0;
	for (; i < (MAX_NUM + BITS_PER_BITE - 1) / BITS_PER_BITE; i++)
		dest.data[i] = src1.data[i] | src2.data[i];
	return dest;
}

set intersect_set(set src1, set src2) {
	set dest = emptySet;
	int i = 0;
	for (; i < (MAX_NUM + BITS_PER_BITE - 1) / BITS_PER_BITE; i++)
		dest.data[i] = src1.data[i] & src2.data[i];
	return dest;
}

set sub_set(set src1, set src2) {
	set dest = emptySet;
	int i = 0;
	for (; i < (MAX_NUM + BITS_PER_BITE - 1) / BITS_PER_BITE; i++)
		dest.data[i] = src1.data[i] & (~(src1.data[i] & src2.data[i]));
	return dest;
}

int str_trimmer(char *src) {
	char *pnt = src;
	int wordCount = 0, commasCount = 0;
	for (; *src; *pnt++ == *src++) {
		if (isalpha(*src) && (!*(src - 1) || isspace(*(src - 1)) || *(src - 1) == ',')) {/*new word*/
			if (wordCount > 1 && commasCount == 0) { /*missing comma*/
				error(9);
				return 0;
			}
			wordCount++;
			commasCount = 0;
		}
		for (; isspace(*src) || *src == ','; src++) {
			if (*src == ',' && wordCount < 2) {/*comma before or after command*/
				error(10);
				return 0;
			}
			if (*src == ',' && wordCount > 1)
				commasCount++;
			if (commasCount == 2) { /*two commas together*/
				error(8);
				return 0;
			}
		}
		*pnt++ = ' ';
	}
	*pnt = '\0';
	if (commasCount > 0) { /*end with a comma*/
		error(11);
		return 0;
	}
	return 1;
}

/*
 * Parse words out of src
 */
void str_parser(char *src, char *cmdName, char *setParamNamesArr[], char *numStr) {
	int i = 0;
	cmdName = strtok(src, " \t");
	for (; setParamNamesArr[i]; i++)
		if (isdigit(*(setParamNamesArr[i] = strtok(NULL, " \t")))) {/*there is a number*/
			numStr = setParamNamesArr[i];
			setParamNamesArr[i] = NULL;
		}
}

/*
 *Extracts numbers out of src and contain them in numArr.
 *Validates the numbers extracted and prints an error if needed.
 *Return 1. 0 if there's an error
 */
int getNumArr(char*src, int numArr[]) {
	int x, i = 0, j;
	char *tmp;
	for (strtok(src, " "); *src; src = strtok(NULL, " ")) {
		x = atoi(src);
		if (x != atof(src)) {/*not an int*/
			error(4);
			return 0;
		}
		if (x < 0 || x > MAX_NUM) {/*out of range*/
			error(3);
			return 0;
		}
		for (j = 0; src[j]; j++)
			if (!isdigit(src[j])) {/*not an int*/
				error(4);
				return 0;
			}
		numArr[i++] = x;
		tmp = src;
	}
	if (strcmp(tmp, "-1")) {
		error(5);
		return 0;
	}
	numArr[i] = -1;
	return 1;
}

/*
 * Assign pointers to sets in setParamArr by the given string names from setParamNamesArr.
 * Check if it's a valid set and prints an error if needed.
 * Return 1. 0 if there's an error
 */
int set_names_to_sets(char*setParamNamesArr[], set*setParamArr[], const char*setsNames[],
		set *setArr[]) {
	int i, j;
	for (i = 0; *(setParamNamesArr[i]); i++) {
		for (j = 0; *(setsNames[j]) && strcmp((setParamNamesArr[i]), (setsNames[j])); j++)
			;
		if (!*(setsNames[j]) && *(setParamNamesArr[i]))/*there is a non matching param*/
			if (isdigit(*(setParamNamesArr[i])))
				setParamArr[i] = NULL;
			else {
				error(1);
				return 0;
			}
		else
			*setParamArr[i] = *setArr[j];
	}
	return 1;
}

/*
 * Returns a pointer to the command function by the given command name,
 * NULL if there's no such command or there's wrong number of parameters
 */
set* cmd_name_to_cmd(const char *cmdName, const char *cmdNames[], set*cmdArr[], int *numParam,
		int paramsCollected) {
	int i = 0;
	for (; *cmdNames[i] && strcmp(cmdName, cmdNames[i]); i++)
		;
	if (*cmdNames[i]) {
		if (!strcmp(cmdName, cmdNames[0])) {/*command is read_set*/

		}
		if (paramsCollected == numParam[i])
			return cmdArr[i];
		if (paramsCollected > numParam[i])/*too many parameters*/
			error(7);
		if (paramsCollected < numParam[i])/*missing parameters*/
			error(6);
	} else if (*cmdName)
		error(2);
	return NULL;
}

/*
 * Prints error message by the given error code
 */
void error(int errorCode) {
	printf("ERROR: ");
	switch (errorCode) {
	case 1:
		puts("Undefined set name");
		break;
	case 2:
		puts("Undefined command name");
		break;
	case 3:
		puts("Invalid set member - value out of range");
		break;
	case 4:
		puts("Invalid set member - not an integer");
		break;
	case 5:
		puts("List of set members is not terminated correctly");
		break;
	case 6:
		puts("Missing parameter");
		break;
	case 7:
		puts("Extraneous text after end of command");
		break;
	case 8:
		puts("Multiple consecutive commas");
		break;
	case 9:
		puts("Missing comma");
		break;
	case 10:
		puts("Illegal comma");
		break;
	case 11:
		puts("Command cannot terminate with a comma");
		break;
	case 12:
		puts("You didn't use the stop command to quit the program");
		break;
	}
}

