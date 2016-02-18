#
# Makefile
#

# source files
SRC	= test.c mythread.c scheduler.c queues.c mylist.c
OBJ	= $(SRC:.c=.o)

# compiler and flags
CC	= gcc
CFLAGS	= -Wall -Werror -std=c99 -O2 -D_GNU_SOURCE
CFLAGS	= -Wall -Werror -g
LDFLAGS = 

# name of the program
PROG    = test.e

main: $(OBJ)
	$(CC) $(CFLAGS) -o $(PROG) $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(PROG)
	rm -f *.o
	@echo "directory cleaned"

all:
	@rm -f  *.o

#-----------------------------------------------------------------------------
