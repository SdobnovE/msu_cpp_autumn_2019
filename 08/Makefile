CC=g++
Keys=-O3 -pthread
all: my_prog 

my_prog: main.o
	$(CC) $(Keys) -o my_prog main.o 




main.o: main.cpp thread_pool.h
	$(CC) $(Keys) -c main.cpp 

clear:
	rm -fr *.o my_prog 