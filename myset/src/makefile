CC_FLAGS = gcc -c -ansi -Wall -pedantic 

myset: set.o myset.o
	$(CC_FLAGS) myset.c -o myset

myset.o: myset.c
	$(CC_FLAGS)  myset.c
	
set.o: set.c	
	$(CC_FLAGS) set.c