#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "set.h"

#define MAX_LINE 80
#define MAX_COMMAND 14
#define MAX_SETPARAMS 3

enum commands {
	READ_SET, PRINT_SET, UNION_SET, INTERSECT_SET, SUB_SET, STOP
};

int checkParams(int parametersCollected, int parametersTarget);
void removeBlanks(char *src);
int getCommand(char *src);
int getParams(char *src, char *setParams, int *numList);
void error(int i);

int main() {
	set sets[6];
	char userLine[MAX_LINE], setParams[MAX_SETPARAMS];
	int numList[MAX_LINE], parametersCollected, command = READ_SET;
	while (command == STOP)
		if (fgets(userLine, MAX_LINE, stdin) == NULL) { //EOF without stop command
			error(13);
			break;
		} else if ((command = getCommand(userLine)) != -1) { //command is OK
			if ((parametersCollected = getParams(userLine, setParams, numList)) != -1) { //params are OK
				if (command == READ_SET)
					if (checkParams(parametersCollected, 2))
						read_set(sets[setParams[0]], numList);
				if (command == PRINT_SET)
					if (checkParams(parametersCollected, 1))
						read_set(sets[setParams[0]]);
				if (command == UNION_SET)
					if (checkParams(parametersCollected, 3))
						read_set(sets[setParams[0]], sets[setParams[1]], sets[setParams[2]]);
				if (command == INTERSECT_SET)
					if (checkParams(parametersCollected, 3))
						read_set(sets[setParams[0]], sets[setParams[1]], sets[setParams[2]]);
				if (command == SUB_SET)
					if (checkParams(parametersCollected, 3))
						read_set(sets[setParams[0]], sets[setParams[1]], sets[setParams[2]]);
				if (command == STOP)
					if (!checkParams(parametersCollected, 0)) //stop gets parameters
						command=READ_SET;
			}
		}
	return 0;
}

int checkParams(int parametersCollected, int parametersTarget) {
	if (parametersCollected > parametersTarget) {
		error(7);
		return 0;
	}
	if (parametersCollected < parametersTarget) {
		error(6);
		return 0;
	}
	return 1;
}

void removeBlanks(char *src) {
	char *pnt = src;
	for (; *src; *pnt++ = *src++)
		for (; *src == ' ' || *src == '\t'; src++)
			;
	*pnt = '\0';
}

int getCommand(char *src) {
	char command[MAX_COMMAND], *pntCommand = command, *startSrc = src;
	for (; *src == ' ' || *src == '\t'; src++)
		;
	for (; isalpha(*src) || *src == '_' || *src != ' '; *pntCommand++ == *src++)
		;
	*pntCommand = '\0';
	strcpy(startSrc, src);
	if (*src == ',') {
		error(10);
		return -1;
	}
	if (strcmp(command, "read_set") == 0)
		return READ_SET;
	if (strcmp(command, "print_set") == 0)
		return PRINT_SET;
	if (strcmp(command, "union_set") == 0)
		return UNION_SET;
	if (strcmp(command, "intersect_set") == 0)
		return INTERSECT_SET;
	if (strcmp(command, "sub_set") == 0)
		return SUB_SET;
	if (strcmp(command, "stop") == 0)
		return STOP;
	else {
		error(2);
		return -1;
	}
}

int getParams(char *src, char *setParams, int *numList) {
	int sets = 0, paramIsNum = 0, num = 0;
	removeBlanks(src);
	for (; *src; src++) {
		if (sets == MAX_SETPARAMS) { //too many parameters
			error(7);
			return -1;
		}
		if (isalpha(*src) && paramIsNum == 1) { //alpha after numbers - wrong parameters
			error(11);
			return -1;
		}
		if (isalpha(*src))
			if (*src++ == 'S' && *src++ == 'E' && *src++ == 'T' && *src >= 'A' && *src++ <= 'F') {
				if (*src && *src != ',') { //no comma after set name
					error(9);
					return -1;
				} else if (*src && *(src + 1) && *(src + 1) == ',') { //2 commas together
					error(8);
					return -1;
				} else if (*src && !*(src + 1)) { //command ends with a comma
					error(12);
					return -1;
				} else
					//writes the letter of the set
					setParams[sets++] = *(src - 1);
			} else { //no such set
				error(1);
				return -1;
			}
		else if (isdigit(*src)) {
			paramIsNum = 1;
			for (; *src && isdigit(*src); src++)
				num = num * 10 + *src + '0';
			*numList++ = num;
			if (*src++ != ',') { //interrupted with a non digit sign or a comma
				error(4);
				return -1;
			}
			if (num >= MAX_NUM) { //num too big
				error(3);
				return -1;
			}
		} else if (*src == ',') { //2 commas together
			error(8);
			return -1;
		} else if (*src++ == '-') {
			if ((*src++ != '1') || (*src)) { //has a negative number
				error(3);
				return -1;
			}
		} else { //not a digit or an alpha
			error(11);
			return -1;
		}
	}
	if (paramIsNum == 1 && (*--src != '1' || *--src != '-')) { //number aren't ending with -1
		error(5);
		return -1;
	}
	if (paramIsNum == 1 && sets != 1) { //there is a list of numbers and not exactly 1 set - wrong params
		error(11);
		return -1;
	}
	return sets + paramIsNum; //number of parameters
}

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
	if (i == 12)
		puts("Command cannot terminate with a comma");
	if (i == 13)
		puts("You didn't use the stop command to quit the program");
}
