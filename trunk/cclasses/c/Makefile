all: main.o iFoo.o iFoo.h
	gcc -Wall -o main iFoo.o main.o

main.o: main.c
	gcc -Wall -c -o main.o main.c

iFoo.o: iFoo.c iFoo.h
	gcc -Wall -c -o iFoo.o iFoo.c
clean:
	rm -f *.o main
