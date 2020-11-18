CC = gcc
CFLAGS = -std=c99 -Wall -pedantic

all : buildidx key2val val2key util.o hashfn.o

hashfn.o: hashfn.c util.h hashfn.h
	$(CC) $(CFLAGS) -c hashfn.c -o hashfn.o

util.o: util.c util.h hashfn.h
	$(CC) $(CFLAGS) -c util.c -o util.o

buildidx.o: buildidx.c util.h hashfn.h
	$(CC) $(CFLAGS) -c buildidx.c -o buildidx.o
buildidx: buildidx.o util.o hashfn.o
	$(CC) $(CFLAGS) buildidx.o util.o hashfn.o -o buildidx

key2val.o: key2val.c util.h hashfn.h
	$(CC) $(CFLAGS) -c key2val.c -o key2val.o
key2val: key2val.o util.o hashfn.o
	$(CC) $(CFLAGS) util.o hashfn.o key2val.o -o key2val

val2key.o: val2key.c util.h hashfn.h
	$(CC) $(CFLAGS) -c val2key.c -o val2key.o
val2key: val2key.o util.o hashfn.o
	$(CC) $(CFLAGS) util.o hashfn.o val2key.o -o val2key


clean:
	rm -i *.o buildidx key2val val2key