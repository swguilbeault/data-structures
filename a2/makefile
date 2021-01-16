# Samuel Guilbeault (1088129)
# CIS*2520 (0101)
# Prof. Stefan C. Kremer
# 30 September 2020

CFLAGS = -std=c99 -Wall -pedantic
CC = gcc

all: array.o

clean:
	rm *.o

array.o: array.c array.h
	$(CC) $(CFLAGS) -c array.c
