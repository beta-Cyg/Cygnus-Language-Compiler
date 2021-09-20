all: init cygnus

init:
	mkdir -p bin lib

cygnus: include/main.cpp grammar_tree
	g++ include/main.cpp -o bin/cygnus
grammar_tree: include/core/grammar_tree.h
	g++ -fPIC -shared -c include/core/grammar_tree.h -o lib/libgt.so
	g++ include/core/grammar_tree.h -o lib/gt.o
	ar rcs lib/libgt.a lib/gt.o
	rm lib/gt.o

clean:
	rm -rf bin lib
