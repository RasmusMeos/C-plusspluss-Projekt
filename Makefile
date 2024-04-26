CC=g++
CFLAGS=-I include -I lib -std=c++20xs


all: fitness

fitness: src/main.cpp src/kasutaja.cpp
	$(CC) $(CFLAGS) -o fitness src/main.cpp src/kasutaja.cpp

clean:
	rm -f fitness
