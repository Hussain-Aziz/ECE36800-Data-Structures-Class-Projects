CC = g++
CCOPTS = -g -Wall
OBJECTS = sorttest2.cpp sort.o

all: $(OBJECTS)
	$(CC) $(CCOPTS) $(OBJECTS) -o sorttest.exe

sort.o: sort.cpp sort.h
	$(CC) $(CCOPTS) -c sort.cpp

clean:
	rm -f *.o *.exe
