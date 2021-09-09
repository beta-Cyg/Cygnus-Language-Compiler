all: cygnus

cygnus: include/main.cpp grammar_tree
	g++ include/main.cpp -o bin/cygnus
grammar_tree: include/core/grammar_tree.h
	g++ include/core/grammar_tree.h -o lib/gt.o
	ar rcs lib/libgt.a lib/gt.o
	rm lib/gt.o

clean:
	rm -rf *.o *.a *.so *.exe
