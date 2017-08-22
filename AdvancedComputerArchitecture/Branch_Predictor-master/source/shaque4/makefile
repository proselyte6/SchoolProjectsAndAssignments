all: predictors

predictors: Predictor.o Driver.o
	g++ -Wall Predictor.o Driver.o -o predictors

Predictor.o: Predictor.h Predictor.cpp
	g++ -Wall -c Predictor.cpp

Driver.o: Driver.cpp
	g++ -Wall -c Driver.cpp

clean:
	rm -f *.o predictors
