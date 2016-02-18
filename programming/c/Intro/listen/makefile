# ---------------------------------------------------------------------------
# Makefile fuer Programmbeispiel mit searaten Dateien
# Fach:     BS, J. Zeman, Sept. 99
# Changes:  M. Thaler, CFLGS added, 1/2010
# File:     makefile 
# ---------------------------------------------------------------------------
#macros
CC    = gcc
CFLGS = -pg

doit:
		make --no-print-directory test1
		make --no-print-directory test2

test1:		test1.o mylist.o mythread.o 
		$(CC) $(CFLGS) test1.o mylist.o mythread.o -o $@

test2:		test2.o mylist.o mythread.o 
		$(CC) $(CFLGS) test2.o mylist.o mythread.o -o $@

test1.o:	test1.c mylist.h  mythread.h
		$(CC) $(CFLGS) -c test1.c -o $@

test2.o:	test2.c mylist.h  mythread.h
		$(CC) $(CFLGS) -c test2.c -o $@

mythread.o:	mythread.c mythread.h 
		$(CC) $(CFLGS) -c mythread.c -o $@

mylist.o:	mylist.c mylist.h 
		$(CC) $(CFLGS) -c mylist.c -o $@

main.o:		main.c
		$(CC) $(CFLGS) -c main.c -o $@

clean:		
		rm -f test1 test2
		rm -f *.o
		@echo "directory cleaned"

all:
		@rm -f *.o
		make --no-print-directory test1
		make --no-print-directory test2
#-----------------------------------------------------------------------------
