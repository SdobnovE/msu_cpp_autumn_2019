CC=g++

all: my_prog test



test: test.o row.o matrix.o
	$(CC) -o test row.o  test.o matrix.o

my_prog: main.o row.o matrix.o
	$(CC) -o my_prog row.o  main.o matrix.o

main.o: main.cpp
	$(CC) -c main.cpp
	
row.o: row.cpp
	$(CC) -c row.cpp

matrix.o: matrix.cpp
	$(CC) -c matrix.cpp

runTest:
	./test
	
clean:
	rm -rf *.o my_prog
