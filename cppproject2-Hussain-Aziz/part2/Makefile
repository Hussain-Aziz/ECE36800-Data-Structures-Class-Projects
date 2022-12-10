CC = g++
CCOPTS = -g -Wall -std=c++11
OBJECTS = book.o booklist2.o

storeUI: storeUI.cpp $(OBJECTS)
	$(CC) $(CCOPTS) storeUI.cpp $(OBJECTS) -o storeUI.exe

booklist2.o: booklist2.cpp booklist2.h
	$(CC) $(CCOPTS) -c booklist2.cpp

book.o: book.cpp book.h
	$(CC) $(CCOPTS) -c book.cpp

clean:
	rm -f *.o *.exe
