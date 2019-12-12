CC=g++
Keys=-g -std=c++17
all: test

test: test.o
	$(CC) $(Keys) -o test  test.o

	
test.o: test.cpp Serializer.h
	$(CC) $(Keys) -c test.cpp

runTest: test
	./test

clean:
	rm -rf *.o test
