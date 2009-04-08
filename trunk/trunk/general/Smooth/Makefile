all:
	gcc -Wall -c -o Smooth.o Smooth.c
	gcc -Wall -c -o smooth_test.o smooth_test.c
	gcc -Wall -o smooth_test smooth_test.o Smooth.o

clean:
	rm -f *.o smooth_test 
