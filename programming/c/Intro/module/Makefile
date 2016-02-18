#
# Makefile
#

# source files
SRC	=	main.c func1.c func2.c func3.c
OBJ	=	$(SRC:.c=.o)

# compiler and flags
CC 	=	gcc
CFLAGS 	=	-g
LDFLAGS	=	

# name of the program
PROG	=	main


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
		make main
#-----------------------------------------------------------------------------
