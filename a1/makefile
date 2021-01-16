# Samuel Guilbeault (1088129)
# CIS*2520 (0101)
# Prof. Stefan C. Kremer
# 22 September 2020

CFLAGS = -std=c99 -Wall -pedantic
CC = gcc

all: test_getbytes test_getbits test_bits2ull test_bits2ll test_spff test_dpff

clean:
	rm *.o test_getbytes test_getbits test_bits2ull test_bits2ll test_spff test_dpff

test_getbytes: test_getbytes.o bandb.o
	$(CC) $(CFLAGS) -o test_getbytes test_getbytes.o bandb.o

test_getbytes.o: test_getbytes.c bandb.h
	$(CC) $(CFLAGS) -c test_getbytes.c

test_getbits: test_getbits.o bandb.o
	$(CC) $(CFLAGS) -o test_getbits test_getbits.o bandb.o

test_getbits.o: test_getbits.c bandb.h
	$(CC) $(CFLAGS) -c test_getbits.c

test_bits2ull: test_bits2ull.o bandb.o
	$(CC) $(CFLAGS) -o test_bits2ull test_bits2ull.o bandb.o

test_bits2ull.o: test_bits2ull.c bandb.h
	$(CC) $(CFLAGS) -c test_bits2ull.c

test_bits2ll: test_bits2ll.o bandb.o
	$(CC) $(CFLAGS) -o test_bits2ll test_bits2ll.o bandb.o

test_bits2ll.o: test_bits2ll.c bandb.h
	$(CC) $(CFLAGS) -c test_bits2ll.c

test_spff: test_spff.o bandb.o
	$(CC) $(CFLAGS) -o test_spff test_spff.o bandb.o

test_spff.o: test_spff.c bandb.h
	$(CC) $(CFLAGS) -c test_spff.c

test_dpff: test_dpff.o bandb.o
	$(CC) $(CFLAGS) -o test_dpff test_dpff.o bandb.o

test_dpff.o: test_dpff.c bandb.h
	$(CC) $(CFLAGS) -c test_dpff.c

bandb.o: bandb.c bandb.h
	$(CC) $(CFLAGS) -c bandb.c
