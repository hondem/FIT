CC=gcc
CCPP=g++
CFLAGS=-std=c99 -pedantic -Wall -Wextra
CPPFLAGS=-std=c++11 -pedantic -Wall

all: tail tail2 wordcount wordcount-dynamic

tail: tail.c tail.h
	$(CC) $(CFLAGS) tail.c -o tail

tail2: tail2.cc tail2.h
	$(CCPP) $(CPPFLAGS) tail2.cc -o tail2

libhtab: htab_*.c
	$(CC) $(CFLAGS) -c htab_hash_function.c
	$(CC) $(CFLAGS) -c htab_free_listitem.c
	$(CC) $(CFLAGS) -c htab_init.c
	$(CC) $(CFLAGS) -c htab_bucket_count.c
	$(CC) $(CFLAGS) -c htab_clear.c
	$(CC) $(CFLAGS) -c htab_find.c
	$(CC) $(CFLAGS) -c htab_foreach.c
	$(CC) $(CFLAGS) -c htab_free.c
	$(CC) $(CFLAGS) -c htab_lookup_add.c
	$(CC) $(CFLAGS) -c htab_move.c
	$(CC) $(CFLAGS) -c htab_remove.c
	$(CC) $(CFLAGS) -c htab_size.c

	$(CC) $(CFLAGS) -fPIC -c htab_bucket_count.c -o htab_bucket_count-dynamic.o
	$(CC) $(CFLAGS) -fPIC -c htab_free_listitem.c -o htab_free_listitem-dynamic.o
	$(CC) $(CFLAGS) -fPIC -c htab_clear.c -o htab_clear-dynamic.o
	$(CC) $(CFLAGS) -fPIC -c htab_find.c -o htab_find-dynamic.o
	$(CC) $(CFLAGS) -fPIC -c htab_foreach.c -o htab_foreach-dynamic.o
	$(CC) $(CFLAGS) -fPIC -c htab_free.c -o htab_free-dynamic.o
	$(CC) $(CFLAGS) -fPIC -c htab_hash_function.c -o htab_hash-function-dynamic.o
	$(CC) $(CFLAGS) -fPIC -c htab_init.c -o htab_init-dynamic.o
	$(CC) $(CFLAGS) -fPIC -c htab_lookup_add.c -o htab_lookup_add-dynamic.o
	$(CC) $(CFLAGS) -fPIC -c htab_move.c -o htab_move-dynamic.o
	$(CC) $(CFLAGS) -fPIC -c htab_remove.c -o htab_remove-dynamic.o
	$(CC) $(CFLAGS) -fPIC -c htab_size.c -o htab_size-dynamic.o

	ar rcs libhtab.a *.o
	$(CC) -shared -fPIC -o libhtab.so *-dynamic.o

wordcount.o: wordcount.c
	$(CC) $(CFLAGS) -c wordcount.c -o wordcount.o

wordcount: wordcount.o libhtab
	$(CC) $(CFLAGS) -o wordcount wordcount.o libhtab.a

wordcount-dynamic: wordcount.o libhtab.so
	$(CC) $(CFLAGS) wordcount.o -o wordcount-dynamic -L. -lhtab

clean:
	rm -r tail tail2
	rm -r *.o

zip: *.c *.h Makefile
	zip xdemel01.zip *.c *.cc *.h Makefile