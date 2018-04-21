CC=gcc
CCPP=g++
CFLAGS=-std=c99 -pedantic -Wall -Wextra
CPPFLAGS=-std=c++11 -pedantic -Wall

all: tail tail2

tail: tail.c tail.h
	$(CC) $(CFLAGS) tail.c -o tail

tail2: tail2.cc tail2.h
	$(CCPP) $(CPPFLAGS) tail2.cc -o tail2

clean:
	rm -r tail tail2