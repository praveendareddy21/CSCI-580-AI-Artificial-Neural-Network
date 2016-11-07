main: ann.o main.o
	g++ -g main.o ann.o -o main

main.o: main.cpp ann.h
	g++ -g -c main.cpp

ann.o: ann.cpp ann.h
	g++ -g -c ann.cpp

clean:
	rm -f *.o main
