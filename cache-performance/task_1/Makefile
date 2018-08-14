 OPT = -O1 				

default: cachetest2

cachetest2: cachetest2.o 
	gcc $(OPT) -o cachetest2 cachetest2.o

cachetest2.o: cachetest2.c
	gcc $(OPT) -c cachetest2.c


clean:
	rm -f *.o
	rm -f cachetest2

