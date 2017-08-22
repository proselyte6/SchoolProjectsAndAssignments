FLAGS = -Wall -std=c++11

BestFirstSearch: BestFirstSearch.o
	g++ $(FLAGS) -w BestFirstSearch.o -o BestFirstSearch

BestFirstSearch.o: BestFirstSearch.cpp
	g++ $(FLAGS) -w -c BestFirstSearch.cpp -o BestFirstSearch.o

clean:
	rm -f *.o BestFirstSearch