CXX=g++

all: main.cpp favs.o themes.o colors.o parse.o exec.o builtin.o
	$(CXX) $(CFLAGS) -std=c++11 main.cpp favs.o themes.o colors.o parse.o exec.o builtin.o -o nwsh

favs.o: modules/favs.hpp modules/favs.cpp
	$(CXX) $(CFLAGS) -std=c++11 -c modules/favs.hpp modules/favs.cpp

themes.o: themes/themes.hpp themes/themes.cpp 
	$(CXX) $(CFLAGS) -std=c++11 -c themes/themes.hpp themes/themes.cpp 

colors.o: modules/colors.cpp modules/colors.hpp
	$(CXX) $(CFLAGS) -std=c++11 -c modules/colors.hpp modules/colors.cpp

parse.o: functions/parse.hpp functions/parse.cpp
	$(CXX) $(CFLAGS) -std=c++11 -c functions/parse.hpp functions/parse.cpp

exec.o: functions/exec.hpp functions/exec.cpp
	$(CXX) $(CFLAGS) -std=c++11 -c functions/exec.hpp functions/exec.cpp

builtin.o: modules/builtin.hpp modules/builtin.cpp
	$(CXX) $(CFLAGS) -std=c++11 -c modules/builtin.hpp modules/builtin.cpp

install:
	sudo cp nwsh /usr/bin/nwsh
	cp etc/nwshrc ~/.nwshrc
	mkdir -p ~/.config/nwsh
	touch ~/.config/nwsh/favorites.conf

clean:
	rm -rf nwsh
	rm -rf *.o
	rm -rf */*.gch
