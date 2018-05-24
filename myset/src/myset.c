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

int main() {
	extern set emptySet;
	set a = emptySet, b = a, c = a, d = a, e = a, f = a, *leftSet, *rightSet, *resultSet;
	set*setArr = { &a, &b, &c, &d, &e, &f, NULL };
	const char* setsNames = { "SETA", "SETB", "SETC", "SETD", "SETE", "SETF", NULL };
	set (*rs)() = read_set, (*ps)() = print_set2, (*us)() = union_set, (*is)() = intersect_set,
			(*ss)() = sub_set, (*s)() = stop,cmd;
	set*cmdArr[] = { rs, ps, us, is, ss, s, NULL };
	const char* cmdNames = { "read_set", "print_set", "union_set", "intersect_set", "sub_set",
			"stop", NULL };
	const int numParam = { 1, 1, 3, 3, 3, 0, NULL };
	char line[MAX_LINE], cmdName[MAX_COMMAND], leftSetName[MAX_COMMAND], rightSetName[MAX_COMMAND],
			resulrSetName[MAX_COMMAND], isNull[MAX_COMMAND];
	char*setParamNamesArr = { leftSetName, rightSetName, resulrSetName, isNull };
	char*setParamArr = { leftSet, rightSet, resultSet };
	int isStop = 0, i;

	while (!isStop && fgets(line, MAX_LINE, stdin)) {
		strTrim(line);
		strParse(line, cmdName, setParamArr);
		for (i = 0; *setParamArr; i++)
			;
		setNamesToSets(setParamNamesArr, setParamArr, setsNames, setArr);
		cmd=cmdNameToCmd(cmdName, cmdNames, cmdArr, numParam, i);

	}
	return 0;
}

set print_set2(set src) {
	print_set(src);
	return src;
}

set stop() {
	extern set emptySet;
	/*EXIT HERE*/
	return emptySet;
}
