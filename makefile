CC=g++

all: main.cpp
	$(CC) main.cpp -o nwsh

clean:
	rm -rf nwsh
