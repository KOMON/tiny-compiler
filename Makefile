tiny: tiny.c cradle.c prep.c tests.c
	gcc -Wall -pedantic tiny.c cradle.c prep.c tests.c -o tiny 

clean:
	rm *~


