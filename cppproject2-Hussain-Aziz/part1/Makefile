CC = g++
CCOPTS = -g -Wall -std=c++11
OBJECTS = book.o booklist1.o

all: catalog

catalog: catalog.cpp $(OBJECTS)
	$(CC) $(CCOPTS) catalog.cpp $(OBJECTS) -o catalog.exe

booklist1.o: booklist1.cpp booklist1.h
	$(CC) $(CCOPTS) -c booklist1.cpp

book.o: book.cpp book.h
	$(CC) $(CCOPTS) -c book.cpp

clean:
	rm -f *.o *.exe
