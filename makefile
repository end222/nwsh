CC=g++

all: main.cpp favs.o themes.o colors.o parse.o exec.o builtin.o
	$(CC) $(CFLAGS) main.cpp favs.o themes.o colors.o parse.o exec.o builtin.o -o nwsh

favs.o: modules/favs.hpp modules/favs.cpp
	$(CC) $(CFLAGS) -c modules/favs.hpp modules/favs.cpp

themes.o: themes/themes.hpp themes/themes.cpp 
	$(CC) $(CFLAGS) -c themes/themes.hpp themes/themes.cpp 

colors.o: modules/colors.cpp modules/colors.hpp
	$(CC) $(CFLAGS) -c modules/colors.hpp modules/colors.cpp

parse.o: functions/parse.hpp functions/parse.cpp
	$(CC) $(CFLAGS) -c functions/parse.hpp functions/parse.cpp

exec.o: functions/exec.hpp functions/exec.cpp
	$(CC) $(CFLAGS) -c functions/exec.hpp functions/exec.cpp

builtin.o: modules/builtin.hpp modules/builtin.cpp
	$(CC) $(CFLAGS) -c modules/builtin.hpp modules/builtin.cpp

install:
	sudo cp nwsh /usr/bin/nwsh
	cp etc/nwshrc ~/.nwshrc

clean:
	rm -rf nwsh
	rm -rf *.o
	rm -rf */*.gch
