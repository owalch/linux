CMP=		gcc
CMPFLAGS=       -Wall
LDFLAGS=
EXENAMES=	ProcA4.e
FNAME=		ProcA4
LIBNAME=

$(EXENAMES):	$(FNAME).o
		$(CMP)  $(FNAME).o $(LIBNAME) $(LDFLAGS) -o $@

.c.o:
		$(CMP) -c $(CMPFLAGS) $<

.cc.o:
		$(CMP) -c $(CMPFLAGS) $<

clean:
		rm -f *.o $(EXENAMES)

all:
		@make clean
		@make

