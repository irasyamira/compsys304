 OPT = -O1 				

default: matrix3

matrix3: matrix3.o 
	gcc $(OPT) -o matrix3 matrix3.o

matrix3.o: matrix3.c
	gcc $(OPT) -c matrix3.c


clean:
	rm -f *.o
	rm -f matrix3

