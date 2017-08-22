all: main

main: main.o Disk.o File.o IBP.o DIBP.o
	g++ -std=c++11 main.o -o main
	
main.o: main.cpp Disk.h File.h IBP.h DIBP.h
	g++ -std=c++11 -c -g -Wall main.cpp -o main.o
	
Disk.o: Disk.h Disk.cpp File.h
	g++ -std=c++11 -c -g -Wall Disk.cpp -o Disk.o
	

File.o: File.h File.cpp IBP.h DIBP.h
	g++ -std=c++11 -c -g -Wall File.cpp -o File.o
	
IBP.o: IBP.h IBP.cpp
	g++ -std=c++11 -c -g -Wall IBP.cpp -o IBP.o
	
DIBP.o: DIBP.h DIBP.cpp IBP.h
	g++ -std=c++11 -c -g -Wall DIBP.cpp -o DIBP.o