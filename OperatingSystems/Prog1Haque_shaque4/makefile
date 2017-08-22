all: prog1sorter prog1generator

prog1sorter: prog1sorter.o timer.o
	gcc prog1sorter.o timer.o -o prog1sorter

prog1generator: prog1generator.o
	gcc prog1generator.o -o prog1generator

prog1sorter.o: prog1sorter.c
	gcc -c prog1sorter.c

prog1generator.o: prog1generator.c
	gcc -c prog1generator.c

timer.o: timer.c timer.h
	gcc -c timer.c timer.h

clean:
	$(RM) prog1sorter prog1generator *.o *.gch