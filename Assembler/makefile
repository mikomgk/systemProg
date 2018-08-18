PROGNAME = assenmly
FLAGS = -pedantic -Wall -ansi
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

$(PROGNAME) : $(OBJS)
	gcc -o $(PROGNAME) $(OBJS)

%.o : %.c
	gcc -g -c $(FLAGS) $<
