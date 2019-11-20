CC=g++
Keys=-g
all: my_prog test



my_prog: main.o
	$(CC) $(Keys) -o my_prog  main.o

test: test.o
	$(CC) $(Keys) -o test test.o

main.o: main.cpp format.h
	$(CC) $(Keys) -c main.cpp
	

	
test.o: test.cpp format.h
	$(CC) $(Keys) -c test.cpp


clean:
	rm -rf *.o my_prog *.gch
