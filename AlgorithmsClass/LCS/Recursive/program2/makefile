FLAGS = -Wall -std=c++11

program2: LCSRecursive.o
	g++ $(FLAGS) LCSRecursive.o -o program2

LCSRecursive.o: LCSRecursive.cpp
	g++ $(FLAGS) -c LCSRecursive.cpp -o LCSRecursive.o

clean:
	rm -f *.o program2