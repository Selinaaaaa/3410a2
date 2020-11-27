CC=gcc
CFLAGS=-g -std=c11 -Wall -Werror -O0
TARGET=program
.PHONY: clean
all: $(TARGET)

pagerank: pagerank.c pagerank.h
	$(CC) $(CFLAGS) $^ -o $@ -lpthread -lm

test: test.c
	$(CC) $(CFLAGS) $^ -o $@ -lpthread -lcmocka

clean:
	rm -f *.o
	rm -f pagerank
	rm -f test
