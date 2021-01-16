# Samuel Guilbeault (1088129)
# CIS*2520 (0101)
# Prof. Stefan C. Kremer
# 21 November 2020

CFLAGS = -std=c99 -Wall -pedantic
CC = gcc

all: ttt1.o ttt2.o show_node count_nodes alphatoe

clean:
	rm *.o show_node count_nodes alphatoe

ttt1.o: ttt1.c ttt.h
	$(CC) $(CFLAGS) -c ttt1.c

ttt2.o: ttt2.c ttt.h
	$(CC) $(CFLAGS) -c ttt2.c

show_node.o: show_node.c ttt.h
	$(CC) $(CFLAGS) -c show_node.c

alphatoe.o: alphatoe.c ttt.h
	$(CC) $(CFLAGS) -c alphatoe.c

count_nodes.o: count_nodes.c ttt.h
	$(CC) $(CFLAGS) -c count_nodes.c

show_node: show_node.o ttt1.o ttt2.o
	$(CC) $(CFLAGS) -o show_node show_node.o ttt1.o ttt2.o

count_nodes: count_nodes.o ttt1.o ttt2.o
	$(CC) $(CFLAGS) -o count_nodes count_nodes.o ttt1.o ttt2.o

alphatoe: alphatoe.o ttt1.o ttt2.o
	$(CC) $(CFLAGS) -o alphatoe alphatoe.o ttt1.o ttt2.o
