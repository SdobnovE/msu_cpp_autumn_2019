CC=g++
Keys=-O3
all: my_prog test

my_prog: main.o
	$(CC) $(Keys) -o my_prog main.o

test: test.o
	$(CC) $(Keys) -o test test.o

test.o: test.cpp vector.h
	$(CC) $(Keys) -c test.cpp


main.o: main.cpp vector.h
	$(CC) $(Keys) -c main.cpp

clear:
	rm -fr *.o my_prog test