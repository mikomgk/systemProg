#include <stdio.h>
#include <string.h>

int main(){
	char a[5],b[5],c[5];
	strcpy(a,"11");
	strcpy(b,"22");
	strcpy(c,"33");
	sscanf("aa bb","%s %s %s",a,b,c);
	printf("%s\n%s\n%s",a,b,c);
	return 0;
}
