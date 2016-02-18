CMP=		gcc
CMPFLAGSA=	-Wall
LDFLAGS=
EXENAMES=	eeeeeeee.e
FNAME=		ProcA7
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

