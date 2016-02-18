# tha 2/2011

CC = gcc
CF = -pg -Wall

build:	simpleShell.o readline.o
	$(CC) $(CF) simpleShell.o readline.o -o simpleShell.e

.c.o:
	$(CC) $(CF) -c $<

.cc.o:
	$(CC) $(CF) -c $<

clean:
	rm -f *.o *.e

all:
	@make -s clean
	make 
