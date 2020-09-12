default: clean
	
except.o: except.c except.h assert.h
	gcc -c except.c

assert.o: assert.c assert.h except.h
	gcc -c assert.c

.PHONY: clean
clean:
	rm *.o; rm *.exe

