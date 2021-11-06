all: init cygnus

init:
	mkdir -p bin lib

cygnus: include/main.cpp grammar_tree
	g++ include/main.cpp -o bin/cygnus -static
grammar_tree: include/core/grammar_tree.h
	g++ -fPIC -shared -c include/core/grammar_tree.h -o lib/libgt.so
	g++ include/core/grammar_tree.h -o lib/gt.o
	ar rcs lib/libgt.a lib/gt.o
	rm lib/gt.o

check:
	g++ -E include/* -Wall > /dev/null

clean:
	rm -rf bin lib
