test : test.o
	cc -o test test.o -lm -lrt
	./test

test.o : test.c fiber.h
	cc -Os -c test.c

clean :
	rm -f test.o test
