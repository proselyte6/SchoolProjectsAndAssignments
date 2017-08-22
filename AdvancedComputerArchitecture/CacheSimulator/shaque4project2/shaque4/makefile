all: cache-sim

cache-sim: CacheSim.o Driver.o
	g++ -Wall CacheSim.o Driver.o -o cache-sim

CacheSim.o: CacheSim.h CacheSim.cpp
	g++ -Wall -c CacheSim.cpp

Driver.o: Driver.cpp
	g++ -Wall -c Driver.cpp

clean:
	rm -f *.o cache-sim
