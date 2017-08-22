FLAGS = -Wall -std=c++11

program3: LCSMemoization.o
	g++ $(FLAGS) LCSMemoization.o -o program3

LCSMemoization.o: LCSMemoization.cpp
	g++ $(FLAGS) -c LCSMemoization.cpp -o LCSMemoization.o

clean:
	rm -f *.o program3