CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -Wextra

tail: tail.c tail.h
	$(CC) $(CFLAGS) -c tail.c
	$(CC) $(CFLAGS) tail.c -o tail

clean:
	rm -r tail tail.o