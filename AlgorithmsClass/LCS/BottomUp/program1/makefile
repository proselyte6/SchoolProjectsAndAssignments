FLAGS = -Wall -std=c++11

program1: LCSBottomUp.o
	g++ $(FLAGS) LCSBottomUp.o -o program1

LCSBottomUp.o: LCSBottomUp.cpp
	g++ $(FLAGS) -c LCSBottomUp.cpp -o LCSBottomUp.o

clean:
	rm -f *.o program1