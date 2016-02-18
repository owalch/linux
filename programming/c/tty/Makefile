#
# Makefile
#

# source files
SRC     = $(shell find -name '*.c')
OBJ     = $(SRC:.c=.o)

# compiler and flags
CC	= gcc
CFLAGS	= -Wall -Werror -std=c99 -O2 -D_GNU_SOURCE
LDFLAGS =

# name of the program
PROG    = uart-listener

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
