CC=gcc
CFLAGS= -O2 -std=c99 -Wall -pedantic

all: primes steg-decode

primes: primes.c eratosthenes.c bit_array.h error.c
	$(CC) $(CFLAGS) primes.c error.c eratosthenes.c -lm -o primes
	$(CC) $(CFLAGS) -DUSE_INLINE primes.c error.c eratosthenes.c -lm -o primes-i

steg-decode: steg-decode.c error.c eratosthenes.c bit_array.h ppm.c
	$(CC) $(CFLAGS) steg-decode.c ppm.c eratosthenes.c error.c -lm -o steg-decode

clean:
	rm -r primes primes-i steg-decode xdemel01.zip

zip: *.h *.c Makefile
	zip xdemel01.zip *.h *.c Makefile -q