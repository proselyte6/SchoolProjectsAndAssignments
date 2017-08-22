# CS375 Final Project / Presentation
# Shafkat Haque & Rachael Wang

all: dijkstrasAdjList

dijkstrasAdjList: dijkstraAdjList.o
	gcc -w dijkstraAdjList.o -o dijkstrasAdjList

dijkstraAdjList.o: dijkstraAdjList.cpp
	gcc -w -c dijkstraAdjList.cpp

clean: 
	rm -f *.o dijkstrasAdjList *~