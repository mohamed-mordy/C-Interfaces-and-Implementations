objects = arith.o test.o

default: $(objects)
	gcc -o test $(objects)
	
test.o: test.c arith.h
	gcc -c test.c

arith.o: arith.c arith.h
	gcc -c arith.c

.PHONY: clean
clean:
	rm *.o; rm *.exe;
