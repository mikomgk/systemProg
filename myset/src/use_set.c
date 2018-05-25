/*
 * use_set.c
 *
 *  Created on: May 24, 2018
 *      Author: user
 */

#include <ctype.h>
#include <string.h>

#include "use_set.h"

/*
 * Takes off unnecessary spaces from src
 * src will be in a format "cmd leftSet ,rightSet ,resultSet( ,garbage)"
 */
void strTrim(char *src) {
	int wordCount = 0;
	char *pnt = src;
	for (; *src; *pnt++ == *src++) {
		if (isalpha(*src) && (!*(src - 1) || isspace(*(src - 1))))
			wordCount++;
		if (*src == ',' && wordCount > 1)
			*pnt++ = ' ';
		for (; isspace(*src); src++)
			if (wordCount == 1)
				*pnt++ = ' ';
	}
	*pnt = '\0';
}

/*
 * Parse words out of src
 */
void strParse(char *src, char *cmdName, char *setParamNamesArr[]) {
	for (; *setParamNamesArr; setParamNamesArr++)/*initialize parameters containers*/
		**setParamNamesArr = '\0';
	sscanf(src, "%s%s ,%s ,%s%s", cmdName, setParamNamesArr[0], setParamNamesArr[1],
			setParamNamesArr[2], setParamNamesArr[3]);
}

/*
 *
 */
void getNumArr(char*src, int*numArr) {

}

/*
 * Returns a pointer to a set by the given set name, NULL if there's no such set
 */
void setNamesToSets(const char*setParamNamesArr[], set*setParamArr[], const char*setsNames[],
		set *setArr) {
	int i = 0, j = 0;
	for (; *(setParamNamesArr[i]); i++) {
		for (; *(setsNames[j]) && !strcmp(*(setParamNamesArr[i]), *(setsNames[j])); j++)
			;
		*setParamArr[i] = setArr[j];
	}
}

/*
 * Returns a pointer to the command function by the given command name,
 * NULL if there's no such command or there's wrong number of parameters
 */
set* cmdNameToCmd(const char *cmdName, const char *cmdNames, set* *cmdArr, int *numParam,
		int paramsCollected) {
	int i = 0;
	for (; cmdNames[i] && strcmp(cmdName, cmdNames[i]); i++)
		;
	if (paramsCollected == numParam[i])
		return cmdArr[i];
	if (paramsCollected > numParam[i])/*too many parameters*/
		error(7);
	if (paramsCollected < numParam[i])/*missing parameters*/
		error(6);
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
		puts("Wrong parameters entered");
		break;
	case 12:
		puts("Command cannot terminate with a comma");
		break;
	case 13:
		puts("You didn't use the stop command to quit the program");
		break;
	}
}
