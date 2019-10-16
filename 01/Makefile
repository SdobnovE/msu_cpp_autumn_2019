CC=g++

all: my_prog

test: my_prog
	bash test.sh

run: my_prog
	./my_prog "${Args}"

my_prog: first.o
	$(CC) -o my_prog first.o 

first.o: first.cpp
	$(CC) -c first.cpp

clean:
	rm -rf *.o my_prog
