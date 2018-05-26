#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(){
	char a[80], *b,*c,*d,*e,*f=a,*g=a;
	fgets(a,70,stdin);
	puts(f);
	puts(g);

	b=strtok(a," ");
	c=strtok(NULL," ");
	d=strtok(NULL," ");
	e=strtok(NULL," ");
	f=strtok(NULL," ");
	g=strtok(NULL," ");
	printf("b-%s.\nc-%s.\nd-%s.\ne-%s.\nf-%s.\ng-%s.\n",b,c,d,e,f,g);
	b=a;
/*	while(*b!='\n')*/
		for(;!isdigit(*b);b++);
			printf("%c	%c	%d",*b,*(b+1),atoi(b));
	return 0;
}
