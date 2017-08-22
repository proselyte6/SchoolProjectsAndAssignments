all: prog3ipc

prog3ipc: prog3ipc.o
	gcc prog3ipc.o -o prog3ipc

prog3ipc.o: prog3ipc.c
	gcc -c prog3ipc.c

clean:
	$(RM) prog3ipc *.o