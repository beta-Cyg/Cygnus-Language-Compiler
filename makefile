all: cygnus

cygnus: include/main.cpp
	g++ include/main.cpp -o bin/cygnus

clean:
	rm -rf *.o *.a *.so *.exe
