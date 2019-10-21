CC=g++

all: my_prog speed



speed: speed.o allocator.o
	$(CC) -o speed allocator.o speed.o

my_prog: main.o allocator.o
	$(CC) -o my_prog allocator.o  main.o

main.o: main.cpp
	$(CC) -c main.cpp
	
allocator.o: allocator.cpp
	$(CC) -c allocator.cpp

speed.o: speed.cpp
	$(CC) -c speed.cpp

runSpeedTest: speed
	./speed 600000000

runTestScript: my_prog
	bash test.sh
	
clean:
	rm -rf *.o my_prog
