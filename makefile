OS := $(shell uname -s)
IS_APPLE := $(shell echo $(OS)|grep -i darwin)

ifdef IS_APPLE
test : test.o
	cc -o test test.o -lm
	./test
test.o : test.c fiber.h
	cc -Os -c test.c -Wno-deprecated-declarations
else
test : test.o
	cc -o test test.o -lm -lrt
	./test
test.o : test.c fiber.h
	cc -Os -c test.c
endif

clean :
	rm -f test.o test
