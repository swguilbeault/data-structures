# Samuel Guilbeault (1088129)
# CIS*2520 (0101)
# Prof. Stefan C. Kremer
# 16 November 2020

CFLAGS = -std=c99 -Wall -pedantic
CC = gcc

all: buildidx key2val val2key actors bacon1

clean:
	rm *.o buildidx key2val val2key actors bacon1

cleanest:
	rm *.khs *.vhs
	make clean

buildidx: buildidx.o util.o hashfn.o
	$(CC) $(CFLAGS) -o buildidx buildidx.o util.o hashfn.o

buildidx.o: buildidx.c
	$(CC) $(CFLAGS) -c buildidx.c

key2val: key2val.o util.o hashfn.o
	$(CC) $(CFLAGS) -o key2val key2val.o util.o hashfn.o

key2val.o: key2val.c
	$(CC) $(CFLAGS) -c key2val.c

val2key: val2key.o util.o hashfn.o
	$(CC) $(CFLAGS) -o val2key val2key.o util.o hashfn.o

val2key.o: val2key.c
	$(CC) $(CFLAGS) -c val2key.c

actors: actors.o util.o hashfn.o
	$(CC) $(CFLAGS) -o actors actors.o util.o hashfn.o

actors.o: actors.c buildidx.c key2val.c val2key.c
	$(CC) $(CFLAGS) -c actors.c

bacon1: bacon1.o util.o hashfn.o
	$(CC) $(CFLAGS) -o bacon1 bacon1.o util.o hashfn.o

bacon1.o: bacon1.c buildidx.c key2val.c val2key.c
	$(CC) $(CFLAGS) -c bacon1.c

util.o: util.c util.h
	$(CC) $(CFLAGS) -c util.c

hashfn.o: hashfn.c
	$(CC) $(CFLAGS) -c hashfn.c

run:
	./buildidx name.basics.kv 10000

# test: makefile hash.o gradeA5_removeElement.c
# 	$(CC) $(CFLAGS) -o test gradeA5_removeElement.c hash.o
