/*
 ============================================================================
 Name        : my_str.c
 Author      : Miko Stern
 Version     : 19/3/18
 Description : Prints all the possible ending of a given string from a given character
 ============================================================================
 */

#include <stdio.h>
#include <string.h>

#define MAX_STR 80

int suffix(char *s, char ch);

int main() {
	char str[MAX_STR], ch;
	int length, comma;
	puts("Enter a character followed by a string, separated with a comma and press enter(enter a comma to quit)");
	str[0] = 'a';
	while ((ch = getchar()) && (comma = getchar()) == 44 && fgets(str, MAX_STR, stdin)) {
		length = strlen(str);
		if (*(str + length - 1) == '\n')
			strcpy(str + length - 1, str + length);
		printf("\nYour character is %c\nYour string is %s\n\n", ch, str);
		printf("\nYou have %d ending versions\n\n", suffix(str, ch));
		puts("Enter a character followed by a string, separated with a comma and press enter(enter a comma to quit)");
	}
	return 0;
}

int suffix(char *s, char ch) {
	int count = 0;
	char *p;
	for (; (p = strchr(s, ch)); s = p + 1) {
		puts(p);
		count++;
	}
	return count;
}
