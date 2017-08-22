all: prog2tree

prog2tree: prog2tree.o
	gcc prog2tree.o -o prog2tree

prog2tree_copy.o : prog2tree.c
	gcc -c prog2tree.c

clean:
	$(RM) prog2tree *.o