CMP=		gcc
CMPFLAGS=	
LDFLAGS=
EXENAME1=	ProcA9.e
FNAM1=		ProcA9
LIBNAME=	-pthread

$(EXENAME1):	$(FNAM1).o
		$(CMP)  $(FNAM1).o $(LDFLAGS) $(LIBNAME) -o $@

.c.o:
		$(CMP) -c $(CMPFLAGS) $< 

.cc.o:
		$(CMP) -c $(CMPFLAGS) $< 

clean:
		rm -f *.o $(EXENAME1)

all:
		@make clean
		@make

