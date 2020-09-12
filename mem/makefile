default:
	

mem.o: mem.c mem.h assert.h except.h
	gcc -c mem.c

memchk.o: memchk.c mem.h assert.h except.h
	gcc -c memchk.c

.PHONY: clean
clean:
	rm *.o; rm *.exe;
