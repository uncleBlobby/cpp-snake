COMPILER = g++

DRIVER = main

FILE = Game

$(DRIVER) : $(FILE).o $(DRIVER).o
	$(COMPILER) -o $(DRIVER) $(FILE).o $(DRIVER).o

$(DRIVER).o : $(DRIVER).cpp $(FILE).cpp $(FILE).h
	$(COMPILER) -c $(DRIVER).cpp -o $(DRIVER).o

$(FILE).o : $(FILE).cpp $(FILE).h
	$(COMPILER) -c $(FILE).cpp -o $(FILE).o

clean:
	@ /bin/rm -f *.o
