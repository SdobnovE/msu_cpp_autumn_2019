CC=g++
Keys=-O3 -std=c++14 -pthread
all: my_prog

my_prog: main.o sort.o
	$(CC) $(Keys) -o my_prog main.o sort.o


sort.o: sort.cpp
	$(CC) $(Keys) -c sort.cpp


main.o: main.cpp
	$(CC) $(Keys) -c main.cpp


clear:
	rm -fr *.o my_prog 