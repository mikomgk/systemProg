/*
 ============================================================================
 Name        : myset.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "use_set.h"

set print_set2(set src);
set stop();

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
