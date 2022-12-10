CC = g++
CCOPTS = -g -Wall -std=c++11
OBJECTS = tabletest1.cpp table1.o

all: $(OBJECTS)
	$(CC) $(CCOPTS) $(OBJECTS) -o tabletest1.exe

table1.o: table1.cpp table1.h
	$(CC) $(CCOPTS) -c table1.cpp

clean:
	rm -f *.o *.exe
