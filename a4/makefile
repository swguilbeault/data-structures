# Samuel Guilbeault (1088129)
# CIS*2520 (0101)
# Prof. Stefan C. Kremer
# 25 October 2020

CFLAGS = -std=c99 -Wall -pedantic
CC = gcc

all: tree.o

clean:
	rm *.o

tree.o: tree.c tree.h
	$(CC) $(CFLAGS) -c tree.c
