# Samuel Guilbeault (1088129)
# CIS*2520 (0101)
# Prof. Stefan C. Kremer
# 15 October 2020

CFLAGS = -std=c99 -Wall -pedantic
CC = gcc

all: list.o

clean:
	rm *.o

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c
