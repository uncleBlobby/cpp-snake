COMPILER = g++

FLAGS = -Wall -Werror

DRIVER = main

FILE = Game

$(DRIVER) : $(FILE).o $(DRIVER).o
	$(COMPILER) $(FLAGS) -o $(DRIVER) $(FILE).o $(DRIVER).o

$(DRIVER).o : $(DRIVER).cpp $(FILE).cpp $(FILE).h
	$(COMPILER) $(FLAGS) -c $(DRIVER).cpp -o $(DRIVER).o

$(FILE).o : $(FILE).cpp $(FILE).h
	$(COMPILER) $(FLAGS) -c $(FILE).cpp -o $(FILE).o

clean:
	@ /bin/rm -f *.o
