CC=g++

all: main.cpp favs.o themes.o
	$(CC) main.cpp favs.o themes.o -o nwsh

favs.o: modules/favs.hpp modules/favs.cpp
	$(CC) -c modules/favs.hpp modules/favs.cpp

themes.o: themes/themes.hpp themes/themes.cpp
	$(CC) -c themes/themes.hpp themes/themes.cpp
install:
	sudo cp nwsh /usr/bin/nwsh
	cp etc/.nwshrc ~/.nwshrc

clean:
	rm -rf nwsh
	rm -rf *.o
	rm -rf */*.gch
