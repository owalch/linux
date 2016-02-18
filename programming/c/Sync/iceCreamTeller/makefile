CMP	=	gcc
CMPFLAGS=	-g
# you need -lrt or -pthread (MAC users need -lpthred)
LIB	=	-pthread

EXENAME0=	startApp.e
EXENAME1=	iceCreamTeller.e
EXENAME2=	customer.e

doit:
	@make --no-print-directory clean
	@make --no-print-directory startApp
	@make --no-print-directory iceCreamTeller
	@make --no-print-directory customer

startApp:	startApp.o 
	$(CMP) $(LIB) $(CMPFLAGS) startApp.o -o $(EXENAME0)

iceCreamTeller:	iceCreamTeller.o 
	$(CMP) $(LIB) $(CMPFLAGS) iceCreamTeller.o -o $(EXENAME1)

customer:	customer.o 
	$(CMP) $(LIB) $(CMPFLAGS) customer.o -o $(EXENAME2)

.c.o:	
	$(CMP) -c $(CMPFLAGS) $<

.cc.o:		
	$(CMP) -c $(CMPFLAGS) $<

all:
	@make clean
	make doit

clean:	
	@rm -f *.e *.o

purge:
	@make clean
