CC=g++

all: my_prog



my_prog: main.o allocator.o
	$(CC) -o my_prog allocator.o  main.o

main.o: main.cpp
	$(CC) -c main.cpp
	
allocator.o: allocator.cpp
	$(CC) -c allocator.cpp

clean:
	rm -rf *.o my_prog
