
default:
	
getword.o: getword.c getword.h assert.h 
	gcc -c getwrod.c

wf.o: wf.c getword.h atom.h table.h mem.h except.h
	gcc -c wf.c

table.o: table.c table.h mem.h assert.h except.h
	gcc -c table.c



.PHONY: clean
clean:
	rm *.o; rm *.exe;

