CC = g++
CCOPTS = -g -Wall -std=c++11
OBJECTS = tabletest2.cpp table2.o

all: $(OBJECTS)
	$(CC) $(CCOPTS) $(OBJECTS) -o tabletest2.exe

table2.o: table2.cpp table2.h
	$(CC) $(CCOPTS) -c table2.cpp

clean:
	rm -f *.o *.exe
