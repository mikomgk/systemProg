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
#include <stdlib.h>

#include "set.h"

void blanksRemov(char *s);
void getCommand(char *s, char *command);
void getSetParam(char *s, char param);
void getListParam(char *src,int *setList);

int main() {
	set sets[6];
	char userCommand[MAX_LINE], command[14], paramA, paramB, paramC;
	int listParam[MAX_LINE];
	while (command != "stop") {
		if (fgets(userCommand, MAX_LINE, stdin) == NULL) {
			puts("You didn't use the stop command to quit the program");
			command = "stop";
			break;
		}
		getCommand(userCommand, command);
		blanksRemove(userCommand);
		switch(command){
		case "read_set":
			getSetParam(userCommand,paramA);
			getListParam(userCommand,listParam);
			if(strlen(userCommand)==0)
				read_set(sets[paramA-'A'],listParam);
			else
				error(7);
			break;
		case "print_set":
			getSetParam(userCommand,paramA);d
			break;
		case "union_set":

		break;
		case "intersect_set":

			break;
		case "sub_set":

			break;
		case "stop":

			break;
		default:
			error(2);
			break;
		}
	}
	return 0;
}

void blanksRemov(char *src) {

}

void getCommand(char *src, char *command) {

}

void getSetParam(char *src, char param) {

}

void getListParam(char *src,int *setList){

}

void error(int i){
	if(i==1)
		puts("Undefined set name");
	if(i==2)
		puts("Undefined command name");
	if(i==3)
		puts("Invalid set member - value out of range");
	if(i==4)
		puts("Invalid set member - not an integer");
	if(i==5)
		puts("List of set members is not terminated correctly");
	if(i==6)
		puts("Missing parameter");
	if(i==7)
		puts("Extraneous text after end of command");
	if(i==8)
		puts("Multiple consecutive commas");
	if(i==9)
		puts("Missing comma");
	if(i==10)
		puts("Illegal comma");
	if(i==11)
		puts(" ");
}










