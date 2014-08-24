all: main.o iFoo.o iFoo.h
	g++ -Wall -o main iFoo.o main.o

main.o: main.cpp
	g++ -Wall -c -o main.o main.cpp

iFoo.o: iFoo.cpp iFoo.h
	g++ -Wall -c -o iFoo.o iFoo.cpp
clean:
	rm -f *.o main
