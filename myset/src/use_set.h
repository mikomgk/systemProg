/*
 * use_set.h
 *
 *  Created on: May 24, 2018
 *      Author: user
 */

# ifndef use_set_h_
# define use_set_h_

#include <stdio.h>
#include <string.h>
#include "set.h"

#define MAX_LINE 80
#define MAX_COMMAND 14

int str_trimmer(char *src);
void str_parser(char *src, char *cmdName, char *setParamNamesArr[],char *numStr);
int getNumArr(char*src, int numArr[]);
int set_names_to_sets(char*setParamNamesArr[], set*setParamArr[], const char*setsNames[],
		set *setArr[]);
set* cmd_name_to_cmd(const char *cmdName, const char *cmdNames[], set*cmdArr[], int *numParam,
		int paramsCollected);
void error(int errorCode);

#endif /* use_set_h_ */
