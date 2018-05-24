/*
 * use_set.h
 *
 *  Created on: May 24, 2018
 *      Author: user
 */

#include <stdio.h>
#include "set.h"

#define MAX_LINE 80
#define MAX_COMMAND 14

set emprtySet;

void strTrim(char *src);
void strParse(char *src, char *cmdName, char *setParamArr);
void setNamesToSets(const char *setParamNamesArr, char*setParamArr, const char *setsNames,
		set *setArr);
set* cmdNameToCmd(const char *cmdName, const char *cmdNames, set *cmdArr, int *numParam,
		int paramsCollected);
void error(int errorCode);
