CC=g++

all: main.cpp favs.o
	$(CC) main.cpp favs.o -o nwsh

favs.o: modules/favs.hpp modules/favs.cpp
	$(CC) -c modules/favs.hpp modules/favs.cpp

install:
	sudo cp nwsh /usr/bin/nwsh
	cp etc/.nwshrc ~/.nwshrc

clean:
	rm -rf nwsh
	rm -rf *.o
	rm -rf */*.gch
