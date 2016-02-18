CMP=		g++
CMPFLAGS=       
EXENAM=		DriverTest
LIBNAME=

compile:	$(EXENAM)

$(EXENA):	$(EXENAM).o
		$(CMP)  $(EXENAM).o -o $@

.cc.o:
		$(CMP) -c $(CMPFLAGS) $<

clean:
		rm -f *.o 
		rm -f DriverTest

all:
		touch *.c*
		make
