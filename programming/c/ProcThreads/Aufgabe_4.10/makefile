CMP=		gcc
CMPFLAGS=       -Wall
LDFLAGS=
EXENAME1=	ProcA10_1.e
FNAM1=		ProcA10_1
EXENAME2=	ProcA10_2.e
FNAM2=		ProcA10_2
LIBNAME=	

Compile:	$(EXENAME1) $(EXENAME2)

$(EXENAME1):	$(FNAM1).o 
		$(CMP)  $(CMPFLAGS) $(FNAM1).o $(LIBNAME) $(LDFLAGS) -o $@

$(EXENAME2):	$(FNAM2).o
		$(CMP)  $(CMPFLAGS) $(FNAM2).o $(LIBNAME) $(LDFLAGS) -o $@

.c.o:
		$(CMP) -c $(CMPFLAGS) $< 

.cc.o:
		$(CMP) -c $(CMPFLAGS) $< 

clean:
		rm -f *.o $(EXENAME1) $(EXENAME2)

all:
		@make clean &> /dev/null
		@make

