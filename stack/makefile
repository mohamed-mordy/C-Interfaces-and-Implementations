objects = stack.o mem.o assert.o calc.o except.o

default: $(objects)
	gcc -o calc $(objects)

stack.o: stack.c stack.h assert.h mem.h
	gcc -c stack.c
calc.o: calc.c stack.h
	gcc -c calc.c

.PHONY: clean
clean:
	rm *.o; rm *.exe;
