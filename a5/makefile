# Samuel Guilbeault (1088129)
# CIS*2520 (0101)
# Prof. Stefan C. Kremer
# 1 November 2020

CFLAGS = -std=c99 -Wall -pedantic
CC = gcc

all: hash.o

clean:
	rm *.o

hash.o: hash.c hash.h
	$(CC) $(CFLAGS) -c hash.c
