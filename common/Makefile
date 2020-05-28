# Makefile for common subsection of sudoku project
#
# Team Rocket, May 27, 2020

LIB = common.a
OBJS = board.o helpers.o

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb

MAKE = make

$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

board.o: board.h
helpers.o: helpers.h

.PHONY: clean

clean:
	rm -f *~ *.o *.dSYM
	rm -f $(LIB)