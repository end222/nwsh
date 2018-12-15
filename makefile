CC=g++

all: main.cpp favs.o themes.o colors.o parse.o exec.o
	$(CC) main.cpp favs.o themes.o colors.o parse.o exec.o -o nwsh

favs.o: modules/favs.hpp modules/favs.cpp
	$(CC) -c modules/favs.hpp modules/favs.cpp

themes.o: themes/themes.hpp themes/themes.cpp 
	$(CC) -c themes/themes.hpp themes/themes.cpp 

colors.o: modules/colors.cpp modules/colors.hpp
	$(CC) -c modules/colors.hpp modules/colors.cpp

parse.o: functions/parse.hpp functions/parse.cpp
	$(CC) -c functions/parse.hpp functions/parse.cpp

exec.o: functions/exec.hpp functions/exec.cpp
	$(CC) -c functions/exec.hpp functions/exec.cpp

install:
	sudo cp nwsh /usr/bin/nwsh
	cp etc/nwshrc ~/.nwshrc

clean:
	rm -rf nwsh
	rm -rf *.o
	rm -rf */*.gch
