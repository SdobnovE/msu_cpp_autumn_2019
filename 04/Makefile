CC=g++
Keys=-g
all: my_prog test

test: bigint.o test.o
	$(CC) $(Keys) -o test bigint.o  test.o

my_prog: main.o bigint.o
	$(CC) $(Keys) -o my_prog bigint.o  main.o

main.o: main.cpp
	$(CC) $(Keys) -c main.cpp
	
bigint.o: bigint.cpp
	$(CC) $(Keys) -c bigint.cpp

test.o: test.cpp
	$(CC) $(Keys) -c test.cpp

runTest: test
	./test

clean:
	rm -rf *.o my_prog
